#include "GuiEgTab.h"

GuiEgTab::GuiEgTab (SynthSound* pSynthSound, float scale)
    : pSound(pSynthSound)
    , scaleFactor(scale)
    , attackLabel("attack", TRANS("Attack Time (sec)"))
    , decayLabel("decay", TRANS("Decay Time (sec)"))
    , sustainLabel("sustain", TRANS("Sustain Level (%)"))
    , releaseLabel("release", TRANS("Release Time (sec)"))
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setJustificationType (Justification::centredRight);
        label.setEditable (false, false, false);
        label.setColour (TextEditor::textColourId, Colours::black);
        label.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    };

    initLabel(attackLabel);
    initLabel(decayLabel);
    initLabel(sustainLabel);
    initLabel(releaseLabel);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle (Slider::LinearHorizontal);
        slider.setTextBoxStyle (Slider::TextBoxRight, false, int(scaleFactor * 80), int(scaleFactor * 20));
        slider.addListener (this);
    };

    initSlider(attackSlider); attackSlider.setRange (0, 10, 0);
    initSlider(decaySlider); decaySlider.setRange (0, 10, 0);
    initSlider(sustainSlider); sustainSlider.setRange (0, 100, 1);
    initSlider(releaseSlider); releaseSlider.setRange (0, 10, 0);

    notify();
}

void GuiEgTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiEgTab::resized()
{
    const int startTop = int(scaleFactor * 20);
    const int labelLeft = int(scaleFactor * 16);
    const int controlLeft = int(scaleFactor * 144);
    const int labelWidth = int(scaleFactor * 120);
    const int sliderWidth = int(scaleFactor * 344);
    const int controlHeight = int(scaleFactor * 24);
    const int gapHeight = int(scaleFactor * 8);

    int top = startTop;
    attackLabel.setBounds (labelLeft, top, labelWidth, controlHeight);
    attackSlider.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    decayLabel.setBounds (labelLeft, top, labelWidth, controlHeight);
    decaySlider.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    sustainLabel.setBounds (labelLeft, top, labelWidth, controlHeight);
    sustainSlider.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    releaseLabel.setBounds (labelLeft, top, labelWidth, controlHeight);
    releaseSlider.setBounds (controlLeft, top, sliderWidth, controlHeight);
}

void GuiEgTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
    double value = sliderThatWasMoved->getValue();
    SynthParameters* pParams = pSound->pParams;
    if (sliderThatWasMoved == &attackSlider) pParams->ampEgAttackTimeSeconds = value;
    else if (sliderThatWasMoved == &decaySlider) pParams->ampEgDecayTimeSeconds = value;
    else if (sliderThatWasMoved == &sustainSlider) pParams->ampEgSustainLevel = 0.01 * value;
    else if (sliderThatWasMoved == &releaseSlider) pParams->ampEgReleaseTimeSeconds = value;
    pSound->parameterChanged();
}

void GuiEgTab::notify()
{
    SynthParameters* pParams = pSound->pParams;
    attackSlider.setValue(pParams->ampEgAttackTimeSeconds);
    decaySlider.setValue(pParams->ampEgDecayTimeSeconds);
    sustainSlider.setValue(100.0 * pParams->ampEgSustainLevel);
    releaseSlider.setValue(pParams->ampEgReleaseTimeSeconds);
}
