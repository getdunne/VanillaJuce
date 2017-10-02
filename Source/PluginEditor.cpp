#include "PluginProcessor.h"
#include "PluginEditor.h"

VanillaJuceAudioProcessorEditor::VanillaJuceAudioProcessorEditor (VanillaJuceAudioProcessor& p, float scale)
    : AudioProcessorEditor (&p)
    , processor (p)
    , lookAndFeel(scale)
    , guiTabs(p.getSound(), scale)
{
    setSize (int(scale * 600), int(scale * 400));
    addAndMakeVisible(&guiTabs);
    guiTabs.setLookAndFeel(&lookAndFeel);
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