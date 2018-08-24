#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"
#include "SynthSound.h"
#include "Synth.h"
#include "DSP_Client.h"

class VanillaJuceAudioProcessor
    : public AudioProcessor
    , public ChangeBroadcaster
    , public DSP_Client::Listener
{
public:
    VanillaJuceAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void getCurrentProgramStateInformation(MemoryBlock& destData) override;
    void setCurrentProgramStateInformation(const void* data, int sizeInBytes) override;

    // DSP_Client::Listener
    void connectStatusChanged(bool connected) override;

public:
    SynthSound* getSound() { return pSound; }
    DSP_Client& getDspClient() { return dspClient; }

private:
    static const int kNumberOfPrograms = 128;
    static const int kNumberOfVoices = 16;

    Synth synth;
    SynthSound* pSound;
    SynthParameters programBank[kNumberOfPrograms];
    int currentProgram;

    DSP_Client dspClient;

private:
    void initializePrograms();
    void queueAllSynthParams();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VanillaJuceAudioProcessor)
};
