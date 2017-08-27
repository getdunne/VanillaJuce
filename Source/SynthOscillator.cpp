#include "SynthOscillator.h"
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"	// only for double_Pi constant

SynthOscillator::SynthOscillator()
	: waveForm(kSawtooth)
    , phase(0)
    , phaseDelta(0)
{
}

void SynthOscillator::setFrequency(double cyclesPerSample)
{
	phaseDelta = cyclesPerSample;
}

float SynthOscillator::getSample()
{
	float sample = 0.0f;
	switch (waveForm)
	{
	case kSine:
		sample = (float)(std::sin(phase * 2.0 * double_Pi));
		break;
	case kSquare:
		sample = (phase <= 0.5) ? 1.0f : -1.0f;
		break;
	case kTriangle:
		sample = (float)(2.0 * (0.5 - std::fabs(phase - 0.5)) - 1.0);
		break;
	case kSawtooth:
		sample = (float)(2.0 * phase - 1.0);
		break;
	}

	phase += phaseDelta;
	while (phase > 1.0) phase -= 1.0;

	return sample;
}
