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

#ifndef DSP_NET_ONLY
void SynthWaveform::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfWaveformTypes; i++)
        cb.addItem(wfNames[i], i + 1);
}

int SynthWaveform::fromComboBox(ComboBox& cb)
{
    index = (WaveformTypeIndex)(cb.getSelectedItemIndex());
    return int(index);
}

void SynthWaveform::toComboBox(ComboBox& cb)
{
    cb.setSelectedItemIndex((int)index);
}
#endif
