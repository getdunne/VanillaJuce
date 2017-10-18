#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthWaveform.h"

class SynthParameters
{
public:
    String programName;

    // main
    float masterLevel;
    float oscBlend;                        // [0.0, 1.0] relative osc1 level
    int pitchBendUpSemitones;
    int pitchBendDownSemitones;
    
    // osc 1
    SynthWaveform osc1Waveform;
    int osc1PitchOffsetSemitones;
    float osc1DetuneOffsetCents;
    
    // osc 2
    SynthWaveform osc2Waveform;
    int osc2PitchOffsetSemitones;
    float osc2DetuneOffsetCents;
    
    // amp EG
    float ampEgAttackTimeSeconds;
    float ampEgDecayTimeSeconds;
    float ampEgSustainLevel;               // [0.0, 1.0]
    float ampEgReleaseTimeSeconds;

public:
    // Set default values
    void setDefaultValues();

    // Save and Restore from XML
    XmlElement* getXml();
    void putXml(XmlElement* xml);
};
