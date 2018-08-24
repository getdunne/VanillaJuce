#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "DSP_Client.h"

class GuiMainTab : public Component, public Slider::Listener
{
public:
    GuiMainTab (SynthSound* pSynthSound, DSP_Client& dspc);
    ~GuiMainTab();

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    void notify();

private:
    SynthSound* pSound;
    DSP_Client& dspClient;

    Label masterLevelLabel, pbUpLabel, pbDownLabel;
    Slider masterLevelSlider, pbUpSlider, pbDownSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiMainTab)
};
