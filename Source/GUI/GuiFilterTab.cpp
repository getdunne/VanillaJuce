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
#include "GuiFilterTab.h"

GuiFilterTab::GuiFilterTab(SynthSound* pSynthSound)
    : GuiEgTab(pSynthSound)
    , typeLabel("type", TRANS("Type"))
    , cutoffLabel("cutoff", TRANS("Cutoff"))
    , resonanceLabel("resonance", TRANS("Resonance"))
    , egAmountLabel("egAmount", TRANS("EG Amount"))
{
    initLabel(cutoffLabel);
    initLabel(resonanceLabel);
    initLabel(egAmountLabel);
    initLabel(typeLabel);

    initSlider(cutoffSlider); cutoffSlider.setRange(0, 20000, 0);
    initSlider(resonanceSlider); resonanceSlider.setRange(0, 1, 0);
    initSlider(egAmountSlider); sustainSlider.setRange(0, 50, 0);

    addAndMakeVisible(typeCombo);
    typeCombo.setEditableText(false);
    typeCombo.setJustificationType(Justification::centredLeft);
    typeCombo.setTextWhenNothingSelected("");
    typeCombo.setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    int i = 0;
    typeCombo.addItem("Lowpass", ++i);
    typeCombo.addItem("Bandpass", ++i);
    typeCombo.addItem("Highpass", ++i);
    typeCombo.addListener(this);
}

void GuiFilterTab::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int sliderWidth = 420;
    const int cboxWidth = 150;
    const int controlHeight = 24;
    const int gapHeight = 8;

    int top = 20;
    attackLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    attackSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    decayLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    decaySlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    sustainLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    sustainSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    releaseLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    releaseSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);

    top += controlHeight + 3 * gapHeight;
    typeLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    typeCombo.setBounds(controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    cutoffLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    cutoffSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    resonanceLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    resonanceSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    egAmountLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    egAmountSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
}

void GuiFilterTab::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    SynthParameters* pParams = pSound->pParams;
    if (comboBoxThatHasChanged == &typeCombo)
    {
        pParams->filterType = (SVFType)typeCombo.getSelectedItemIndex();
    }
    pSound->parameterChanged();
}

void GuiFilterTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
    float value = (float)(sliderThatWasMoved->getValue());
    SynthParameters* pParams = pSound->pParams;
    if (sliderThatWasMoved == &attackSlider) pParams->filterEgAttackTimeSeconds = value;
    else if (sliderThatWasMoved == &decaySlider) pParams->filterEgDecayTimeSeconds = value;
    else if (sliderThatWasMoved == &sustainSlider) pParams->filterEgSustainLevel = 0.01f * value;
    else if (sliderThatWasMoved == &releaseSlider) pParams->filterEgReleaseTimeSeconds = value;
    else if (sliderThatWasMoved == &cutoffSlider) pParams->filterCutoff = value;
    else if (sliderThatWasMoved == &resonanceSlider) pParams->filterResonance = value;
    else if (sliderThatWasMoved == &egAmountSlider) pParams->filterEgAmount = value;
    pSound->parameterChanged();
}

void GuiFilterTab::notify()
{
    SynthParameters* pParams = pSound->pParams;
    typeCombo.setSelectedItemIndex(pParams->filterType);
    attackSlider.setValue(pParams->filterEgAttackTimeSeconds);
    decaySlider.setValue(pParams->filterEgDecayTimeSeconds);
    sustainSlider.setValue(100.0f * pParams->filterEgSustainLevel);
    releaseSlider.setValue(pParams->filterEgReleaseTimeSeconds);
    cutoffSlider.setValue(pParams->filterCutoff);
    resonanceSlider.setValue(pParams->filterResonance);
    egAmountSlider.setValue(pParams->filterEgAmount);
}
