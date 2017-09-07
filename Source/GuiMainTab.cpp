#include "GuiMainTab.h"

//==============================================================================
GuiMainTab::GuiMainTab (SynthSound* pSynthSound, float scale)
    : pSound(pSynthSound)
    , scaleFactor(scale)
    , masterLevelLabel("master level", TRANS("Master Volume"))
    , pbUpLabel("PB up", TRANS("P.Bend up (semi)"))
    , pbDownLabel("PB down", TRANS("P.Bend down (semi)"))
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setJustificationType(Justification::centredRight);
        label.setEditable(false, false, false);
        label.setColour(TextEditor::textColourId, Colours::black);
        label.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    };

    initLabel(masterLevelLabel);
    initLabel(pbUpLabel);
    initLabel(pbDownLabel);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextBoxRight, false, int(scaleFactor * 80), int(scaleFactor * 20));
        slider.addListener(this);
    };

    initSlider(masterLevelSlider); masterLevelSlider.setRange(0, 10, 0);
    initSlider(pbUpSlider); pbUpSlider.setRange(0, 12, 1);
    initSlider(pbDownSlider); pbDownSlider.setRange(0, 12, 1);

    notify();
}

void GuiMainTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiMainTab::resized()
{
    const int startTop = int(scaleFactor * 20);
    const int labelLeft = int(scaleFactor * 16);
    const int controlLeft = int(scaleFactor * 144);
    const int labelWidth = int(scaleFactor * 120);
    const int sliderWidth = int(scaleFactor * 344);
    const int controlHeight = int(scaleFactor * 24);
    const int gapHeight = int(scaleFactor * 8);

    int top = startTop;
    masterLevelLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    masterLevelSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + 5 * gapHeight;
    pbUpLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    pbUpSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    pbDownLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    pbDownSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
}

void GuiMainTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
    double value = sliderThatWasMoved->getValue();
    SynthParameters* pParams = pSound->pParams;
    if (sliderThatWasMoved == &masterLevelSlider)
    {
        pParams->masterLevel = 0.1 * value;
    }
    else if (sliderThatWasMoved == &pbUpSlider)
    {
        pParams->pitchBendUpSemitones = int(value);
    }
    else if (sliderThatWasMoved == &pbDownSlider)
    {
        pParams->pitchBendDownSemitones = int(value);
    }
    pSound->parameterChanged();
}

void GuiMainTab::notify()
{
    SynthParameters* pParams = pSound->pParams;
    masterLevelSlider.setValue(10.0 * pParams->masterLevel);
    pbUpSlider.setValue(pParams->pitchBendUpSemitones);
    pbDownSlider.setValue(pParams->pitchBendDownSemitones);
}
