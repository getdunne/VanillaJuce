#include "GuiOscTab.h"

GuiOscTab::GuiOscTab (SynthSound* pSynthSound, float scale)
    : pSound(pSynthSound)
    , scaleFactor(scale)
    , wfLabel1("waveform label1", TRANS("Osc1 Waveform"))
    , semiLabel1("semitone offset label1", TRANS("Pitch (semitones)"))
    , detuneLabel1("detune label1", TRANS("Detune (cents)"))
    , wfLabel2("waveform label2", TRANS("Osc2 Waveform"))
    , semiLabel2("semitone offset label1", TRANS("Pitch (semitones)"))
    , detuneLabel2("detune label1", TRANS("Detune (cents)"))
    , oscBlendLabel("osc blend label", TRANS("Blend"))
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setJustificationType(Justification::centredRight);
        label.setEditable(false, false, false);
        label.setColour(TextEditor::textColourId, Colours::black);
        label.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    };

    initLabel(wfLabel1);
    initLabel(semiLabel1);
    initLabel(detuneLabel1);
    initLabel(wfLabel2);
    initLabel(semiLabel2);
    initLabel(detuneLabel2);
    initLabel(oscBlendLabel);
    oscBlendLabel.setJustificationType(Justification::centred);

    auto initCombo = [this](ComboBox& combo)
    {
        addAndMakeVisible(combo);
        combo.setEditableText(false);
        combo.setJustificationType(Justification::centredLeft);
        combo.setTextWhenNothingSelected("");
        combo.setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
        combo.addListener(this);
    };

    initCombo(waveformCB1); 
    SynthWaveform::setupComboBox(waveformCB1);
    waveformCB1.addListener(this);
    initCombo(waveformCB2);
    SynthWaveform::setupComboBox(waveformCB2);
    waveformCB2.addListener(this);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextBoxRight, false, int(scaleFactor * 80), int(scaleFactor * 20));
        slider.addListener(this);
    };

    initSlider(semiSlider1); semiSlider1.setRange(-24, 24, 1);
    initSlider(detuneSlider1); detuneSlider1.setRange(-50, 50, 0);
    initSlider(semiSlider2); semiSlider2.setRange(-24, 24, 1);
    initSlider(detuneSlider2); detuneSlider2.setRange(-50, 50, 0);

    addAndMakeVisible(oscBlendSlider);
    oscBlendSlider.setRange(0, 100, 0);
    oscBlendSlider.setSliderStyle(Slider::LinearVertical);
    oscBlendSlider.setTextBoxStyle(Slider::TextBoxAbove, false, int(scaleFactor * 80), int(scaleFactor * 20));
    oscBlendSlider.addListener(this);

    notify();
}

void GuiOscTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiOscTab::resized()
{
    const int startTop = int(scaleFactor * 20);
    const int labelLeft = int(scaleFactor * 16);
    const int controlLeft = int(scaleFactor * 144);
    const int labelWidth = int(scaleFactor * 120);
    const int cboxWidth = int(scaleFactor * 150);
    const int sliderWidth = int(scaleFactor * 344);
    const int controlHeight = int(scaleFactor * 24);
    const int gapHeight = int(scaleFactor * 8);
    const int blendSliderLeft = int(scaleFactor * 510);
    const int blendSliderWidth = int(scaleFactor * 60);
    const int blendSliderHeight = int(scaleFactor * 240);

    int top = startTop;
    wfLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    waveformCB1.setBounds (controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    semiLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    semiSlider1.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    detuneLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    detuneSlider1.setBounds (controlLeft, top, sliderWidth, controlHeight);

    top += controlHeight + 5 * gapHeight;
    wfLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    waveformCB2.setBounds(controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    semiLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    semiSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    detuneLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    detuneSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);

    top = startTop;
    oscBlendSlider.setBounds(blendSliderLeft, top, blendSliderWidth, blendSliderHeight);
    top += blendSliderHeight + gapHeight;
    oscBlendLabel.setBounds(blendSliderLeft + blendSliderWidth/2 - labelWidth/2, top, labelWidth, controlHeight);
}

void GuiOscTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    SynthParameters* pParams = pSound->pParams;
    if (comboBoxThatHasChanged == &waveformCB1)
    {
        pParams->osc1Waveform.fromComboBox(*comboBoxThatHasChanged);
    }
    else if (comboBoxThatHasChanged == &waveformCB2)
    {
        pParams->osc2Waveform.fromComboBox(*comboBoxThatHasChanged);
    }
    pSound->parameterChanged();
}

void GuiOscTab::sliderValueChanged (Slider* sliderThatWasMoved)
{
    double value = sliderThatWasMoved->getValue();
    SynthParameters* pParams = pSound->pParams;
    if (sliderThatWasMoved == &semiSlider1)
    {
        pParams->osc1PitchOffsetSemitones = int(value);
    }
    else if (sliderThatWasMoved == &semiSlider2)
    {
        pParams->osc2PitchOffsetSemitones = int(value);
    }
    else if (sliderThatWasMoved == &detuneSlider1)
    {
        pParams->osc1DetuneOffsetCents = value;
    }
    else if (sliderThatWasMoved == &detuneSlider2)
    {
        pParams->osc2DetuneOffsetCents = value;
    }
    else if (sliderThatWasMoved == &oscBlendSlider)
    {
        pParams->oscBlend = 0.01 * value;
    }
    pSound->parameterChanged();
}

void GuiOscTab::notify()
{
    SynthParameters* pParams = pSound->pParams;

    pParams->osc1Waveform.toComboBox(waveformCB1);
    semiSlider1.setValue(pParams->osc1PitchOffsetSemitones);
    detuneSlider1.setValue(pParams->osc1DetuneOffsetCents);

    pParams->osc2Waveform.toComboBox(waveformCB2);
    semiSlider2.setValue(pParams->osc2PitchOffsetSemitones);
    detuneSlider2.setValue(pParams->osc2DetuneOffsetCents);

    oscBlendSlider.setValue(100.0 * pParams->oscBlend);
}
