#include "PluginProcessor.h"
#include "PluginEditor.h"

VanillaJuceAudioProcessorEditor::VanillaJuceAudioProcessorEditor (VanillaJuceAudioProcessor& p, float scale)
    : AudioProcessorEditor (&p)
    , processor (p)
    , lookAndFeel(scale)
    , guiTabs(p.getSound(), scale)
{
    guiTabs.setLookAndFeel(&lookAndFeel);
    setSize (int(scale * defaultWidth), int(scale * defaultHeight));
    setResizeLimits(defaultWidth, defaultHeight, 3 * defaultWidth, 3 * defaultHeight);
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
    // determine new scale factor based on width
    int width = getWidth();
    float scaleFactor = (float)width / defaultWidth;
    lookAndFeel.setScaleFactor(scaleFactor);
    guiTabs.setScaleFactor(scaleFactor);

    // adjust height in appropriate proportion to new width
    //int height = (int)(0.5f + scaleFactor * defaultHeightWidthRatio() * width);
    //setSize(width, height);
    guiTabs.setBounds(0, 0, getWidth(), getHeight());
}

void VanillaJuceAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source)
{
    ignoreUnused(source);
    guiTabs.notify();
}