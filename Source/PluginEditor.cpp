#include "PluginProcessor.h"
#include "PluginEditor.h"

VanillaJuceAudioProcessorEditor::VanillaJuceAudioProcessorEditor (VanillaJuceAudioProcessor& p)
    : AudioProcessorEditor (&p)
	, processor (p)
	, guiTabs(p.getSound())
{
    setSize (600, 400);
	addAndMakeVisible(&guiTabs);
	p.addChangeListener(this);
}

VanillaJuceAudioProcessorEditor::~VanillaJuceAudioProcessorEditor()
{
	processor.removeChangeListener(this);
}

void VanillaJuceAudioProcessorEditor::paint (Graphics& g)
{
	ignoreUnused(g);
}

void VanillaJuceAudioProcessorEditor::resized()
{
	guiTabs.setBounds(0, 0, proportionOfWidth(1.0000f), proportionOfHeight(1.0000f));
}

void VanillaJuceAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source)
{
	ignoreUnused(source);
	guiTabs.notify();
}