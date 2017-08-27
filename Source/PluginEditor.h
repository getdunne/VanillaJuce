#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GuiTabs.h"

class VanillaJuceAudioProcessorEditor
	: public AudioProcessorEditor
	, public ChangeListener
{
public:
    VanillaJuceAudioProcessorEditor (VanillaJuceAudioProcessor&);
    ~VanillaJuceAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

	virtual void changeListenerCallback(ChangeBroadcaster* source);

private:
    VanillaJuceAudioProcessor& processor;
	GuiTabs guiTabs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VanillaJuceAudioProcessorEditor)
};
