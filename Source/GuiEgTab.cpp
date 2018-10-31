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
#include "GuiEgTab.h"

GuiEgTab::GuiEgTab (SynthSound* pSynthSound, DSP_Client& dspc)
    : pSound(pSynthSound)
    , dspClient(dspc)
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
    SynthParameters::ParameterIndex paramIndex = SynthParameters::ParameterIndex::kMasterLevel;

    if (sliderThatWasMoved == &attackSlider)
    {
        paramIndex = SynthParameters::ParameterIndex::kAmpEgAttackTimeSeconds;
    }
    else if (sliderThatWasMoved == &decaySlider)
    {
        paramIndex = SynthParameters::ParameterIndex::kAmpEgDecayTimeSeconds;
    }
    else if (sliderThatWasMoved == &sustainSlider)
    {
        paramIndex = SynthParameters::ParameterIndex::kAmpEgSustainLevel;
        value *= 0.01f;
    }
    else if (sliderThatWasMoved == &releaseSlider)
    {
        paramIndex = SynthParameters::ParameterIndex::kAmpEgReleaseTimeSeconds;
    }

    pSound->pParams->updateParam(paramIndex, value);
    dspClient.queueParameterUpdate(int(paramIndex), value);
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
