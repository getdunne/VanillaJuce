#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GuiTabs.h"

class MyLookAndFeel : public LookAndFeel_V4
{
private:
    float scaleFactor;

public:
    MyLookAndFeel(float scale) : scaleFactor(scale) {}

    void setScaleFactor(float scale) { scaleFactor = scale; }

    virtual Font getLabelFont(Label&) override
    {
        return Font(scaleFactor * 15.0f, Font::plain).withTypefaceStyle("Regular");
    }
};

class VanillaJuceAudioProcessorEditor
    : public AudioProcessorEditor
    , public ChangeListener
{
public:
    VanillaJuceAudioProcessorEditor (VanillaJuceAudioProcessor&, float scale=1.0f);
    ~VanillaJuceAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

    virtual void changeListenerCallback(ChangeBroadcaster* source);

private:
    VanillaJuceAudioProcessor& processor;
    MyLookAndFeel lookAndFeel;
    GuiTabs guiTabs;

    const int defaultWidth = 600;
    const int defaultHeight = 340;
    const float defaultHeightWidthRatio() { return (float)defaultHeight / defaultWidth; }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VanillaJuceAudioProcessorEditor)
};
