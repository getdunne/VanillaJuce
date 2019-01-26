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
#include "SynthParameters.h"

void SynthParameters::setDefaultValues()
{
    programName = "Default";
    masterLevel = 0.15f;
    oscBlend= 0.5f;
    pitchBendUpSemitones = 2;
    pitchBendDownSemitones = 2;
    osc1Waveform.setToDefault();
    osc1PitchOffsetSemitones = 0;
    osc1DetuneOffsetCents = -10.0f;
    osc2Waveform.setToDefault();
    osc2PitchOffsetSemitones = 0;
    osc2DetuneOffsetCents = +10.0f;
    ampEgAttackTimeSeconds = 0.1f;
    ampEgDecayTimeSeconds = 0.1f;
    ampEgSustainLevel = 0.8f;
    ampEgReleaseTimeSeconds = 0.5f;
    filterEgAttackTimeSeconds = 1.0f;
    filterEgDecayTimeSeconds = 1.0f;
    filterEgSustainLevel = 0.0f;
    filterEgReleaseTimeSeconds = 1.0f;
    filterType = SVFLowpass;
    filterCutoff = 250.0f;
    filterResonance = 0.5f;
    filterEgAmount = 10.0f;
}

XmlElement* SynthParameters::getXml()
{
    XmlElement* xml = new XmlElement("program");

    xml->setAttribute("name", programName);

    xml->setAttribute("masterLevel", masterLevel);
    xml->setAttribute("oscBlend", oscBlend);
    xml->setAttribute("pitchBendUpSemitones", pitchBendUpSemitones);
    xml->setAttribute("pitchBendDownSemitones", pitchBendDownSemitones);

    xml->setAttribute("osc1Waveform", osc1Waveform.name());
    xml->setAttribute("osc1PitchOffsetSemitones", osc1PitchOffsetSemitones);
    xml->setAttribute("osc1DetuneOffsetCents", osc1DetuneOffsetCents);

    xml->setAttribute("osc2Waveform", osc2Waveform.name());
    xml->setAttribute("osc2PitchOffsetSemitones", osc2PitchOffsetSemitones);
    xml->setAttribute("osc2DetuneOffsetCents", osc2DetuneOffsetCents);

    xml->setAttribute("ampEgAttackTimeSeconds", ampEgAttackTimeSeconds);
    xml->setAttribute("ampEgDecayTimeSeconds", ampEgDecayTimeSeconds);
    xml->setAttribute("ampEgSustainLevel", ampEgSustainLevel);
    xml->setAttribute("ampEgReleaseTimeSeconds", ampEgReleaseTimeSeconds);

    xml->setAttribute("filterEgAttackTimeSeconds", filterEgAttackTimeSeconds);
    xml->setAttribute("filterEgDecayTimeSeconds", filterEgDecayTimeSeconds);
    xml->setAttribute("filterEgSustainLevel", filterEgSustainLevel);
    xml->setAttribute("filterEgReleaseTimeSeconds", filterEgReleaseTimeSeconds);

    xml->setAttribute("filterType", filterType);
    xml->setAttribute("filterCutoff", filterCutoff);
    xml->setAttribute("filterResonance", filterResonance);
    xml->setAttribute("filterEgAmount", filterEgAmount);

    return xml;
}

void SynthParameters::putXml(XmlElement* xml)
{
    programName = xml->getStringAttribute("name");

    masterLevel = (float)(xml->getDoubleAttribute("masterLevel", masterLevel));
    oscBlend = (float)(xml->getDoubleAttribute("oscBlend", oscBlend));
    pitchBendUpSemitones = xml->getIntAttribute("pitchBendUpSemitones", pitchBendUpSemitones);
    pitchBendDownSemitones = xml->getIntAttribute("pitchBendDownSemitones", pitchBendDownSemitones);

    osc1Waveform.setFromName(xml->getStringAttribute("osc1Waveform", osc1Waveform.name()));
    osc1PitchOffsetSemitones = xml->getIntAttribute("osc1PitchOffsetSemitones", osc1PitchOffsetSemitones);
    osc1DetuneOffsetCents = (float)(xml->getDoubleAttribute("osc1DetuneOffsetCents", osc1DetuneOffsetCents));

    osc2Waveform.setFromName(xml->getStringAttribute("osc2Waveform", osc2Waveform.name()));
    osc2PitchOffsetSemitones = xml->getIntAttribute("osc2PitchOffsetSemitones", osc2PitchOffsetSemitones);
    osc2DetuneOffsetCents = (float)(xml->getDoubleAttribute("osc2DetuneOffsetCents", osc2DetuneOffsetCents));

    ampEgAttackTimeSeconds = (float)(xml->getDoubleAttribute("ampEgAttackTimeSeconds", ampEgAttackTimeSeconds));
    ampEgDecayTimeSeconds = (float)(xml->getDoubleAttribute("ampEgDecayTimeSeconds", ampEgDecayTimeSeconds));
    ampEgSustainLevel = (float)(xml->getDoubleAttribute("ampEgSustainLevel", ampEgSustainLevel));
    ampEgReleaseTimeSeconds = (float)(xml->getDoubleAttribute("ampEgReleaseTimeSeconds", ampEgReleaseTimeSeconds));

    filterEgAttackTimeSeconds = (float)(xml->getDoubleAttribute("filterEgAttackTimeSeconds", filterEgAttackTimeSeconds));
    filterEgDecayTimeSeconds = (float)(xml->getDoubleAttribute("filterEgDecayTimeSeconds", filterEgDecayTimeSeconds));
    filterEgSustainLevel = (float)(xml->getDoubleAttribute("filterEgSustainLevel", filterEgSustainLevel));
    filterEgReleaseTimeSeconds = (float)(xml->getDoubleAttribute("filterEgReleaseTimeSeconds", filterEgReleaseTimeSeconds));

    filterType = (SVFType)(xml->getIntAttribute("filterType", filterType));
    filterCutoff = (float)(xml->getDoubleAttribute("filterCutoff", filterCutoff));
    filterResonance = (float)(xml->getDoubleAttribute("filterResonance", filterResonance));
    filterEgAmount = (float)(xml->getDoubleAttribute("filterEgAmount", filterEgAmount));
}
