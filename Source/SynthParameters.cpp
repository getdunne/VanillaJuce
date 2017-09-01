#include "SynthParameters.h"

void SynthParameters::setDefaultValues()
{
    programName = "Default";
    masterLevel = 0.15;
    oscBlend= 0.5;
    pitchBendUpSemitones = 2;
    pitchBendDownSemitones = 2;
    osc1Waveform.setToDefault();
    osc1PitchOffsetSemitones = 0;
    osc1DetuneOffsetCents = -10.0;
    osc2Waveform.setToDefault();
    osc2PitchOffsetSemitones = 0;
    osc2DetuneOffsetCents = +10.0;
    ampEgAttackTimeSeconds = 0.1;
    ampEgDecayTimeSeconds = 0.1;
    ampEgSustainLevel = 0.8;
    ampEgReleaseTimeSeconds = 0.5;
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

    return xml;
}

void SynthParameters::putXml(XmlElement* xml)
{
    programName = xml->getStringAttribute("name");

    masterLevel = xml->getDoubleAttribute("masterLevel");
    oscBlend = xml->getDoubleAttribute("oscBlend");
    pitchBendUpSemitones = xml->getIntAttribute("pitchBendUpSemitones");
    pitchBendDownSemitones = xml->getIntAttribute("pitchBendDownSemitones");

    osc1Waveform.setFromName(xml->getStringAttribute("osc1Waveform"));
    osc1PitchOffsetSemitones = xml->getIntAttribute("osc1PitchOffsetSemitones");
    osc1DetuneOffsetCents = xml->getDoubleAttribute("osc1DetuneOffsetCents");

    osc2Waveform.setFromName(xml->getStringAttribute("osc2Waveform"));
    osc2PitchOffsetSemitones = xml->getIntAttribute("osc2PitchOffsetSemitones");
    osc2DetuneOffsetCents = xml->getDoubleAttribute("osc2DetuneOffsetCents");

    ampEgAttackTimeSeconds = xml->getDoubleAttribute("ampEgAttackTimeSeconds");
    ampEgDecayTimeSeconds = xml->getDoubleAttribute("ampEgDecayTimeSeconds");
    ampEgSustainLevel = xml->getDoubleAttribute("ampEgSustainLevel");
    ampEgReleaseTimeSeconds = xml->getDoubleAttribute("ampEgReleaseTimeSeconds");
}
