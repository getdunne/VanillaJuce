#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthWaveform.h"

class SynthParameters
{
public:
    enum ParameterIndex {
        kUpdateLock = 0,
        kMasterLevel,
        kOscBlend,
        kPitchBendUpSemitones,
        kPitchBendDownSemitones,
        kOsc1WaveformIndex,
        kOsc1PitchOffsetSemitones,
        kOsc1DetuneOffsetCents,
        kOsc2WaveformIndex,
        kOsc2PitchOffsetSemitones,
        kOsc2DetuneOffsetCents,
        kAmpEgAttackTimeSeconds,
        kAmpEgDecayTimeSeconds,
        kAmpEgSustainLevel,
        kAmpEgReleaseTimeSeconds,

        kNumberOfParameterIndices
    };

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
    SynthParameters() : updateLocked(false) { setDefaultValues(); }

    // Set default values
    void setDefaultValues();

    // Update a parameter based on its ParameterIndex. Returns true if the change
    // should be propagated to the synthesis engine.
    bool updateParam(ParameterIndex paramIndex, float newValue);

    // Get a parameter value based on its index
    float getParam(int paramIndex);

    // Save and Restore from XML
    XmlElement* getXml();
    void putXml(XmlElement* xml);

protected:
    bool updateLocked;
};
