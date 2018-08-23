#include "DSP_Client.h"

// Testing
//#define TESTMODE

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
#ifdef TESTMODE
    return true;
#else
    firstPacket = true;
    bool connected = socket.connect(ipAddress, portNumber);
    listeners.call([connected](Listener& l) { l.connectStatusChanged(connected); });
    return connected;
#endif
}

void DSP_Client::disconnect()
{
    disconnectPending = true;
}

bool DSP_Client::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
#ifdef TESTMODE
    int channels = buffer.getNumChannels();
    int frameCount = buffer.getNumSamples();
    float** wptrs = buffer.getArrayOfWritePointers();
    memset(wptrs[0], 0, frameCount * DATASIZE);
    memset(wptrs[1], 0, frameCount * DATASIZE);
    wptrs[0][0] = 1.0f;
    wptrs[1][0] = 1.0f;
    return true;
#else
    if (!socket.isConnected())
    {
        listeners.call([](Listener& l) { l.connectStatusChanged(false); });
        return false;
    }
    else if (disconnectPending)
    {
#ifndef TESTMODE
        if (socket.isConnected()) socket.close();
        disconnectPending = false;
        listeners.call([](Listener& l) { l.connectStatusChanged(false); });
#endif
        return true;
    }
    int frameCount = buffer.getNumSamples();

    SendDataHeader* pHdr = (SendDataHeader*)databuf;
    int byteCount = sizeof(SendDataHeader);
    memset(pHdr, 0, sizeof(SendDataHeader));
    pHdr->frameCount = (uint16_t)frameCount;

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

    /* sending effect data would look like this:
    SampleDataHeader* sdhdr = (SampleDataHeader*)pMidi;
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
#endif
}