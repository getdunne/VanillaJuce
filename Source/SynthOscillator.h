#pragma once
#include "SynthParameters.h"

class SynthOscillator
{
private:
	SynthOscillatorWaveform waveForm;
	double phase;			// [0.0, 1.0]
	double phaseDelta;		// cycles per sample (fraction)

public:
    SynthOscillator();
    
	void setWaveform(SynthOscillatorWaveform wf) { waveForm = wf; }
	void setFrequency(double cyclesPerSample);

	float getSample ();
};
