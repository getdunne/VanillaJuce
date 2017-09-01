#pragma once
#include "SynthParameters.h"

class SynthOscillator
{
private:
    SynthWaveform waveform;
    double phase;            // [0.0, 1.0]
    double phaseDelta;        // cycles per sample (fraction)

public:
    SynthOscillator() : phase(0), phaseDelta(0) {}
    
    void setWaveform(SynthWaveform wf) { waveform = wf; }
    void setFrequency(double cyclesPerSample) { phaseDelta = cyclesPerSample; }

    float getSample ();
};
