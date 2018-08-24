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

    masterLevel = (float)(xml->getDoubleAttribute("masterLevel"));
    oscBlend = (float)(xml->getDoubleAttribute("oscBlend"));
    pitchBendUpSemitones = xml->getIntAttribute("pitchBendUpSemitones");
    pitchBendDownSemitones = xml->getIntAttribute("pitchBendDownSemitones");

    osc1Waveform.setFromName(xml->getStringAttribute("osc1Waveform"));
    osc1PitchOffsetSemitones = xml->getIntAttribute("osc1PitchOffsetSemitones");
    osc1DetuneOffsetCents = (float)(xml->getDoubleAttribute("osc1DetuneOffsetCents"));

    osc2Waveform.setFromName(xml->getStringAttribute("osc2Waveform"));
    osc2PitchOffsetSemitones = xml->getIntAttribute("osc2PitchOffsetSemitones");
    osc2DetuneOffsetCents = (float)(xml->getDoubleAttribute("osc2DetuneOffsetCents"));

    ampEgAttackTimeSeconds = (float)(xml->getDoubleAttribute("ampEgAttackTimeSeconds"));
    ampEgDecayTimeSeconds = (float)(xml->getDoubleAttribute("ampEgDecayTimeSeconds"));
    ampEgSustainLevel = (float)(xml->getDoubleAttribute("ampEgSustainLevel"));
    ampEgReleaseTimeSeconds = (float)(xml->getDoubleAttribute("ampEgReleaseTimeSeconds"));
}

bool SynthParameters::updateParam(ParameterIndex paramIndex, float newValue)
{
    switch (paramIndex)
    {
        case kUpdateLock:
            updateLocked = (newValue != 0.0f);
            break;
        case kMasterLevel:
            masterLevel = newValue;
            break;
        case kOscBlend:
            oscBlend = newValue;
            break;
        case kPitchBendUpSemitones:
            pitchBendUpSemitones = int(newValue);
            break;
        case kPitchBendDownSemitones:
            pitchBendDownSemitones = int(newValue);
            break;
        case kOsc1WaveformIndex:
            osc1Waveform.index = (SynthWaveform::WaveformTypeIndex)(int(newValue));
            break;
        case kOsc1PitchOffsetSemitones:
            osc1PitchOffsetSemitones = int(newValue);
            break;
        case kOsc1DetuneOffsetCents:
            osc1DetuneOffsetCents = int(newValue);
            break;
        case kOsc2WaveformIndex:
            osc2Waveform.index = (SynthWaveform::WaveformTypeIndex)(int(newValue));
            break;
        case kOsc2PitchOffsetSemitones:
            osc2PitchOffsetSemitones = newValue;
            break;
        case kOsc2DetuneOffsetCents:
            osc2DetuneOffsetCents = newValue;
            break;
        case kAmpEgAttackTimeSeconds:
            ampEgAttackTimeSeconds = newValue;
            break;
        case kAmpEgDecayTimeSeconds:
            ampEgDecayTimeSeconds = newValue;
            break;
        case kAmpEgSustainLevel:
            ampEgSustainLevel = newValue;
            break;
        case kAmpEgReleaseTimeSeconds:
            ampEgReleaseTimeSeconds = newValue;
            break;
    }
    return !updateLocked;
}