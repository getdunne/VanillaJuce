#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiEgTab  : public Component,
                  public SliderListener
{
public:
    GuiEgTab (SynthSound* pSynthSound);
    ~GuiEgTab();

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

	void notify();

private:
	SynthSound* pSound;

    ScopedPointer<Label> attackLabel;
    ScopedPointer<Slider> attackSlider;
    ScopedPointer<Label> decayLabel;
    ScopedPointer<Slider> decaySlider;
    ScopedPointer<Label> sustainLabel;
    ScopedPointer<Slider> sustainSlider;
    ScopedPointer<Label> releaseLabel;
    ScopedPointer<Slider> releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiEgTab)
};
