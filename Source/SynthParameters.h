#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthWaveform.h"

class SynthParameters
{
public:
    String programName;

    // main
    double masterLevel;
    double oscBlend;                        // [0.0, 1.0] relative osc1 level
    int pitchBendUpSemitones;
    int pitchBendDownSemitones;
    
    // osc 1
    SynthWaveform osc1Waveform;
    int osc1PitchOffsetSemitones;
    double osc1DetuneOffsetCents;
    
    // osc 2
    SynthWaveform osc2Waveform;
    int osc2PitchOffsetSemitones;
    double osc2DetuneOffsetCents;
    
    // amp EG
    double ampEgAttackTimeSeconds;
    double ampEgDecayTimeSeconds;
    double ampEgSustainLevel;               // [0.0, 1.0]
    double ampEgReleaseTimeSeconds;

public:
    // Set default values
    void setDefaultValues();

    // Save and Restore from XML
    XmlElement* getXml();
    void putXml(XmlElement* xml);
};
