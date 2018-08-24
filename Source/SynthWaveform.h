#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthWaveform
{
private:
    enum WaveformTypeIndex {
        kSine, kTriangle, kSquare, kSawtooth,
        kNumberOfWaveformTypes
    } index;
    
    friend class SynthOscillator;
    friend class SynthParameters;

public:
    // default constructor
    SynthWaveform() : index(kSine) {}

    // set to default state after construction
    void setToDefault() { index = kSine; }

    // serialize: get human-readable name of this waveform
    String name();

    // deserialize: set index based on given name
    void setFromName(String wfName);

#ifndef DSP_NET_ONLY
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    int fromComboBox(ComboBox& cb);
    void toComboBox(ComboBox& cb);
#endif

private:
    // waveform names: ordered list of string literals
    static const char* const wfNames[];
};
