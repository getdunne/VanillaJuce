/* Copyright (c) 2017-2018 Shane D. Dunne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "GuiMainTab.h"

//==============================================================================
GuiMainTab::GuiMainTab (SynthSound* pSynthSound)
    : pSound(pSynthSound)
    , masterLevelLabel("master level", TRANS("Master Volume"))
    , pbUpLabel("PB up", TRANS("P.Bend up (semi)"))
    , pbDownLabel("PB down", TRANS("P.Bend down (semi)"))
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
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
        slider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
        slider.addListener(this);
    };

    initSlider(masterLevelSlider); masterLevelSlider.setRange(0, 10, 0);
    initSlider(pbUpSlider); pbUpSlider.setRange(0, 12, 1);
    initSlider(pbDownSlider); pbDownSlider.setRange(0, 12, 1);

    notify();
}

GuiMainTab::~GuiMainTab()
{
}

//==============================================================================
void GuiMainTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiMainTab::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int sliderWidth = 420;
    const int controlHeight = 24;
    const int gapHeight = 8;

    int top = 20;
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
    float value = (float)(sliderThatWasMoved->getValue());
    SynthParameters* pParams = pSound->pParams;
    if (sliderThatWasMoved == &masterLevelSlider)
    {
        pParams->masterLevel = 0.1f * value;
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
