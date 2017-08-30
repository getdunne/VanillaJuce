#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"

class Synth;

class SynthSound : public SynthesiserSound
{
private:
    Synth& synth;

public:
    SynthSound(Synth& ownerSynth);
    
    // our sound applies to all notes, all channels
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }

    // pointer to currently-used parameters bundle
    SynthParameters* pParams;

    // call to notify owner Synth, that parameters have changed
    void parameterChanged();
};
