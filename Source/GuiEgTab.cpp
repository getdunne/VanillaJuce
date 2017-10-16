#include "GuiEgTab.h"

GuiEgTab::GuiEgTab (SynthSound* pSynthSound)
    : pSound(pSynthSound)
    , attackLabel("attack", TRANS("Attack Time (sec)"))
    , decayLabel("decay", TRANS("Decay Time (sec)"))
    , sustainLabel("sustain", TRANS("Sustain Level (%)"))
    , releaseLabel("release", TRANS("Release Time (sec)"))
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
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
        slider.setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
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
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int sliderWidth = 420;
    const int controlHeight = 24;
    const int gapHeight = 8;

    int top = 20;
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
    float value = (float)(sliderThatWasMoved->getValue());
    SynthParameters* pParams = pSound->pParams;
    if (sliderThatWasMoved == &attackSlider) pParams->ampEgAttackTimeSeconds = value;
    else if (sliderThatWasMoved == &decaySlider) pParams->ampEgDecayTimeSeconds = value;
    else if (sliderThatWasMoved == &sustainSlider) pParams->ampEgSustainLevel = 0.01f * value;
    else if (sliderThatWasMoved == &releaseSlider) pParams->ampEgReleaseTimeSeconds = value;
    pSound->parameterChanged();
}

void GuiEgTab::notify()
{
    SynthParameters* pParams = pSound->pParams;
    attackSlider.setValue(pParams->ampEgAttackTimeSeconds);
    decaySlider.setValue(pParams->ampEgDecayTimeSeconds);
    sustainSlider.setValue(100.0f * pParams->ampEgSustainLevel);
    releaseSlider.setValue(pParams->ampEgReleaseTimeSeconds);
}
