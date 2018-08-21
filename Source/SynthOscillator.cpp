#include "SynthOscillator.h"
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"    // only for double_Pi constant

float SynthOscillator::getSample()
{
    float sample = 0.0f;
    switch (waveform.index)
    {
    case SynthWaveform::kSine:
        sample = (float)(std::sin(phase * 2.0 * double_Pi));
        break;
    case SynthWaveform::kSquare:
        sample = (phase <= 0.5) ? 1.0f : -1.0f;
        break;
    case SynthWaveform::kTriangle:
        sample = (float)(2.0 * (0.5 - std::fabs(phase - 0.5)) - 1.0);
        break;
    case SynthWaveform::kSawtooth:
        sample = (float)(2.0 * phase - 1.0);
    default:
        break;
    }

    phase += phaseDelta;
    while (phase > 1.0) phase -= 1.0;

    return sample;
}
