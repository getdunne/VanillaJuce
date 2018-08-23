#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <stdint.h>

#define MAXFRAMES 2048
#define CHANNELS 2
#define DATASIZE sizeof(float)
#define BUFLEN (MAXFRAMES * CHANNELS * DATASIZE)
#define DEFAULT_PORT 27016
#define MAXMIDIMSGS 100

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

    class Listener
    {
    public:
        virtual void connectStatusChanged(bool connected) = 0;
    };

    void addListener(Listener* listener) { listeners.add(listener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

    bool processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages);

protected:
    StreamingSocket socket;
    ListenerList<Listener> listeners;

    bool disconnectPending;

    char databuf[sizeof(SampleDataHeader) + MAXMIDIMSGS*sizeof(MIDIMessageInfoStruct) + BUFLEN];
    bool firstPacket;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DSP_Client)
};
