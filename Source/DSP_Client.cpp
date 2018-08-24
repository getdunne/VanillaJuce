#include "DSP_Client.h"

DSP_Client::DSP_Client()
    : disconnectPending(false)
{
}

DSP_Client::~DSP_Client()
{
    disconnect();
}

bool DSP_Client::connect(String ipAddress, int portNumber)
{
    if (socket.isConnected()) return true;

    firstPacket = true;
    bool connected = socket.connect(ipAddress, portNumber);
    if (connected)
    {
        listeners.call([connected](Listener& l) { l.connectStatusChanged(connected); });
    }

    return connected;
}

void DSP_Client::disconnect()
{
    disconnectPending = true;
}

void DSP_Client::queueParameterUpdate(int paramIndex, float newValue)
{
    if (!socket.isConnected()) return;

    //DBG("Queueing param " + String(paramIndex) + " <= " + String(newValue));
    ParamMessageStruct pms;
    pms.effectIndex = 0;
    pms.paramIndex = paramIndex;
    pms.paramValue = newValue;

    std::lock_guard<std::mutex> lock(paramQueueMutex);
    paramUpdateQueue.push(pms);
}

bool DSP_Client::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (!socket.isConnected())
    {
        // handle unexpected disconnect from server side
        listeners.call([](Listener& l) { l.connectStatusChanged(false); });
        return false;
    }
    else if (disconnectPending)
    {
        // complete pending disconnect from client side
        if (socket.isConnected()) socket.close();
        disconnectPending = false;
        listeners.call([](Listener& l) { l.connectStatusChanged(false); });
        while (!paramUpdateQueue.empty()) paramUpdateQueue.pop();
        return true;
    }

    // prepare SendDataHeader
    int frameCount = buffer.getNumSamples();
    SendDataHeader* pHdr = (SendDataHeader*)databuf;
    int byteCount = sizeof(SendDataHeader);
    memset(pHdr, 0, sizeof(SendDataHeader));
    pHdr->frameCount = (uint16_t)frameCount;

    // prepare MIDI
    MIDIMessageInfoStruct* pMidi = (MIDIMessageInfoStruct*)(databuf + sizeof(SendDataHeader));
    MidiBuffer::Iterator it(midiMessages);
    MidiMessage midiMsg;
    int samplePos;
    while (it.getNextEvent(midiMsg, samplePos))
    {
        if (midiMsg.getRawDataSize() > 3) continue;
        const uint8* mrd = midiMsg.getRawData();

        pMidi->status = mrd[0] & 0xF0;
        pMidi->channel = mrd[0] & 0x0F;
        pMidi->data1 = mrd[1];
        pMidi->data2 = mrd[2];
        pMidi->startFrame = samplePos;

        pMidi++;
        pHdr->midiCount++;
        byteCount += sizeof(MIDIMessageInfoStruct);
    }
    midiMessages.clear(0, frameCount);

    // prepare parameter changes
    paramQueueMutex.lock();
    ParamMessageStruct* pPms = (ParamMessageStruct*)(databuf + byteCount);
    while (!paramUpdateQueue.empty())
    {
        *pPms++ = paramUpdateQueue.front();
        paramUpdateQueue.pop();
        byteCount += sizeof(ParamMessageStruct);
        pHdr->paramCount++;
    }
    paramQueueMutex.unlock();

    /* sending effect data would look like this:
    SampleDataHeader* sdhdr = (SampleDataHeader*)(databuf + byteCount);
    sdhdr->mainByteCount = frameCount * CHANNELS * DATASIZE;
    sdhdr->corrByteCount = 0xFFFF;
    byteCount += sizeof(SampleDataHeader);

    const float** rptrs = buffer.getArrayOfReadPointers();
    uint8* pData = (uint8*)(sendbuf + byteCount);
    memcpy(pData, rptrs[0], pHdr->frameCount * DATASIZE);
    byteCount += frameCount * DATASIZE;
    pData += frameCount * DATASIZE;
    memcpy(pData, rptrs[1], frameCount * DATASIZE);
    byteCount += frameCount * DATASIZE;
    */

    if (socket.write(databuf, byteCount) != byteCount) goto comm_error;

    if (firstPacket)
    {
        firstPacket = false;
    }
    else
    {
        int bytesExpected = sizeof(SampleDataHeader) + frameCount * DATASIZE * CHANNELS;
        int bytesReceived = socket.read(databuf, bytesExpected, true);
        if (bytesReceived != bytesExpected) goto comm_error;

        float* pLeft = (float*)(databuf + sizeof(SampleDataHeader));
        float* pRight = pLeft + frameCount;
        buffer.addFrom(0, 0, pLeft, frameCount);
        buffer.addFrom(1, 0, pRight, frameCount);
    }

    return true;

comm_error:
    disconnect();
    return false;
}