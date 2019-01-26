/* Copyright (c) 2017-2018 Shane D. Dunne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "SynthVoice.h"
#include <cmath>

void SynthVoice::setPitchBend(int pitchWheelPos)
{
    if (pitchWheelPos > 8192)
    {
        // shifting up
        pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
    }
    else
    {
        // shifting down
        pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
    }
}

float SynthVoice::pitchBendCents()
{
    if (pitchBend >= 0.0f)
    {
        // shifting up
        return pitchBend * pParams->pitchBendUpSemitones * 100;
    }
    else
    {
        // shifting down
        return pitchBend * pParams->pitchBendDownSemitones * 100;
    }
}

static double noteFreqHz(int midiNoteNumber, double centsOffset)
{
    double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    hertz *= std::pow(2.0, centsOffset / 1200);
    return hertz;
}

SynthVoice::SynthVoice()
    : SynthesiserVoice()
    , pParams(0)
    , noteVelocity(0.0f)
    , pitchBend(0.0f)
    , osc1Level(0.0f)
    , osc2Level(0.0f)
    , tailOff(false)
{
}

// Set up voice according to current sound parameters and pitch bend
void SynthVoice::setup (bool pitchBendOnly)
{
    double sampleRateHz = getSampleRate();
    int midiNote = getCurrentlyPlayingNote();

    float masterLevel = float(noteVelocity * pParams->masterLevel);
    double pbCents = pitchBendCents();

    noteHz = float(noteFreqHz(midiNote + pParams->osc1PitchOffsetSemitones, pParams->osc1DetuneOffsetCents + pbCents));
    double cyclesPerSecond = noteHz;
    double cyclesPerSample = cyclesPerSecond / sampleRateHz;
    osc1.setFrequency(cyclesPerSample);
    if (!pitchBendOnly)
    {
        osc1.setWaveform(pParams->osc1Waveform);
        osc1Level.reset(sampleRateHz, ampEG.isRunning() ? 0.1 : 0.0);
        osc1Level.setValue(float(pParams->oscBlend * masterLevel));
    }

    cyclesPerSecond = noteFreqHz(midiNote + pParams->osc2PitchOffsetSemitones, pParams->osc2DetuneOffsetCents + pbCents);
    cyclesPerSample = cyclesPerSecond / sampleRateHz;
    osc2.setFrequency(cyclesPerSample);
    if (!pitchBendOnly)
    {
        osc2.setWaveform(pParams->osc2Waveform);
        osc2Level.reset(sampleRateHz, ampEG.isRunning() ? 0.1 : 0.0);
        osc2Level.setValue(float((1.0 - pParams->oscBlend) * masterLevel));
    }

    if (!pitchBendOnly)
    {
        ampEG.attackSeconds = pParams->ampEgAttackTimeSeconds;
        ampEG.decaySeconds = pParams->ampEgDecayTimeSeconds;
        ampEG.sustainLevel = pParams->ampEgSustainLevel;
        ampEG.releaseSeconds = pParams->ampEgReleaseTimeSeconds;
        filterEG.attackSeconds = pParams->filterEgAttackTimeSeconds;
        filterEG.decaySeconds = pParams->filterEgDecayTimeSeconds;
        filterEG.sustainLevel = pParams->filterEgSustainLevel;
        filterEG.releaseSeconds = pParams->filterEgReleaseTimeSeconds;
    }

    filterCutoff = pParams->filterCutoff / 261.6f;  // normalize to middle C
    filterEgMultiple = pParams->filterEgAmount;
    filter.setFilter(float(getSampleRate()), pParams->filterType, pParams->filterCutoff, pParams->filterResonance, 1.0f);
}

void SynthVoice::soundParameterChanged()
{
    if (pParams == 0) return;
    setup(false);
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    ignoreUnused(midiNoteNumber);    // accessible as SynthesiserVoice::getCurrentlyPlayingNote();
    tailOff = false;
    noteVelocity = velocity;

    pParams = dynamic_cast<SynthSound*>(sound)->pParams;
    double sampleRateHz = getSampleRate();
    setPitchBend(currentPitchWheelPosition);

    setup(false);
    ampEG.start(sampleRateHz);
    filterEG.start(sampleRateHz);
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    ignoreUnused(velocity);

    if (allowTailOff & !tailOff)
    {
        tailOff = true;
        ampEG.release();
        filterEG.release();
    }
    else
    {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved(int newValue)
{
    setPitchBend(newValue);
    setup(true);
}

void SynthVoice::controllerMoved(int controllerNumber, int newValue)
{
    // nothing yet
    ignoreUnused(controllerNumber);
    ignoreUnused(newValue);
}

void SynthVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    while (--numSamples >= 0)
    {
        if (!ampEG.isRunning())
        {
            clearCurrentNote();
            break;
        }
        float aeg = ampEG.getSample();
        float osc = osc1.getSample() * osc1Level.getNextValue() + osc2.getSample() * osc2Level.getNextValue();
        float sample = aeg * osc;
        float feg = filterEG.getSample();
        float cutoffHz = noteHz * (filterCutoff + feg * filterEgMultiple);
        float fSampleRate = float(getSampleRate());
        float fMaxCutoff = 0.49f * fSampleRate;
        if (cutoffHz > fMaxCutoff) cutoffHz = fMaxCutoff;
        filter.setCutoffFreq(cutoffHz);
        outputBuffer.addSample(0, startSample, filter.processAudioSample(sample, 0));
        outputBuffer.addSample(1, startSample, filter.processAudioSample(sample, 1));
        ++startSample;
    }
}
