/* Copyright (c) 2017-2018 Shane D. Dunne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <stdint.h>
#include <queue>
#include <mutex>

#define MAXFRAMES 2048
#define CHANNELS 2
#define DATASIZE sizeof(float)
#define BUFLEN (MAXFRAMES * CHANNELS * DATASIZE)
#define DEFAULT_PORT 27016
#define MAXMIDIMSGS 100
#define MAXPARAMMSGS 100

#pragma pack(push, 1)

#define UINT16_BIT15_MASK       0x8000
#define UINT16_LOW15BITS_MASK   0x7FFF

typedef struct
{
    uint16_t    frameCount;
    uint16_t    midiCount;
    uint16_t    paramCount;
    uint16_t    padding;
    uint32_t    timeStamp;
} SendDataHeader;

typedef struct
{
    uint8_t     status;
    uint8_t     channel;
    uint8_t     data1;
    uint8_t     data2;
    uint32_t    startFrame;
} MIDIMessageInfoStruct;

typedef struct
{
    uint16_t    effectIndex;
    uint16_t    paramIndex;
    float       paramValue;
} ParamMessageStruct;

typedef struct
{
    uint16_t    mainByteCount;      // or total bytecount if uncompressed
    uint16_t    corrByteCount;      // 0 = lossy compression, 0xFFFF = uncompressed
} SampleDataHeader;

#pragma pack(pop)

class DSP_Client
{
public:
    DSP_Client();
    ~DSP_Client();

    bool connect(String ipAddress, int portNumber);
    bool isConnected() { return socket.isConnected(); }
    void disconnect();

    void queueParameterUpdate(int paramIndex, float newValue);

    bool processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages);

    class Listener
    {
    public:
        virtual void connectStatusChanged(bool connected) = 0;
        virtual ~Listener() = default;
    };

    void addListener(Listener* listener) { listeners.add(listener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

protected:
    StreamingSocket socket;
    ListenerList<Listener> listeners;

    bool disconnectPending;

    std::queue<ParamMessageStruct> paramUpdateQueue;
    std::mutex paramQueueMutex;

    char databuf[sizeof(SampleDataHeader)
                    + MAXMIDIMSGS*sizeof(MIDIMessageInfoStruct)
                    + MAXPARAMMSGS*sizeof(ParamMessageStruct)
                    + BUFLEN];
    bool firstPacket;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DSP_Client)
};
