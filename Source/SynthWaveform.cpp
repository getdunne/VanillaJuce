#include "SynthWaveform.h"

const char* const SynthWaveform::wfNames[] = {
    "Sine", "Triangle", "Square", "Sawtooth"
};

void SynthWaveform::setFromName(String wfName)
{
    for (int i = 0; i < kNumberOfWaveformTypes; i++)
    {
        if (wfName == wfNames[i])
        {
            index = (WaveformTypeIndex)i;
            return;
        }
    }

    // Were we given an invalid waveform name?
    jassertfalse;
}

String SynthWaveform::name()
{
    return wfNames[index];
}

void SynthWaveform::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfWaveformTypes; i++)
        cb.addItem(wfNames[i], i + 1);
}

void SynthWaveform::fromComboBox(ComboBox& cb)
{
    index = (WaveformTypeIndex)(cb.getSelectedItemIndex());
}

void SynthWaveform::toComboBox(ComboBox& cb)
{
    cb.setSelectedItemIndex((int)index);
}
