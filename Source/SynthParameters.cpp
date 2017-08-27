#include "SynthParameters.h"

void SynthParameters::setDefaultValues()
{
	sprintf(programName, "Default");
	masterLevel = 0.15;
	oscBlend= 0.5;
	pitchBendUpSemitones = 2;
	pitchBendDownSemitones = 2;
	osc1Waveform = kSine;
	osc1PitchOffsetSemitones = 0;
	osc1DetuneOffsetCents = -10.0;
	osc2Waveform = kSine;
	osc2PitchOffsetSemitones = 0;
	osc2DetuneOffsetCents = +10.0;
	ampEgAttackTimeSeconds = 0.1;
	ampEgDecayTimeSeconds = 0.1;
	ampEgSustainLevel = 0.8;
	ampEgReleaseTimeSeconds = 0.5;
}

const char* WFname[] = { "Sine", "Triangle", "Square", "Sawtooth" };

static SynthOscillatorWaveform LookupWF(String wfname)
{
	int wfIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		if (!strcmp(wfname.toUTF8(), WFname[i]))
		{
			wfIndex = i;
			break;
		}
	}
	return (SynthOscillatorWaveform)wfIndex;
}

XmlElement* SynthParameters::getXml()
{
	XmlElement* xml = new XmlElement("program");

	xml->setAttribute(String("name"), String(programName));

	xml->setAttribute(String("masterLevel"), masterLevel);
	xml->setAttribute(String("oscBlend"), oscBlend);
	xml->setAttribute(String("pitchBendUpSemitones"), pitchBendUpSemitones);
	xml->setAttribute(String("pitchBendDownSemitones"), pitchBendDownSemitones);

	xml->setAttribute(String("osc1Waveform"), String(WFname[osc1Waveform]));
	xml->setAttribute(String("osc1PitchOffsetSemitones"), osc1PitchOffsetSemitones);
	xml->setAttribute(String("osc1DetuneOffsetCents"), osc1DetuneOffsetCents);

	xml->setAttribute(String("osc2Waveform"), String(WFname[osc2Waveform]));
	xml->setAttribute(String("osc2PitchOffsetSemitones"), osc2PitchOffsetSemitones);
	xml->setAttribute(String("osc2DetuneOffsetCents"), osc2DetuneOffsetCents);

	xml->setAttribute(String("ampEgAttackTimeSeconds"), ampEgAttackTimeSeconds);
	xml->setAttribute(String("ampEgDecayTimeSeconds"), ampEgDecayTimeSeconds);
	xml->setAttribute(String("ampEgSustainLevel"), ampEgSustainLevel);
	xml->setAttribute(String("ampEgReleaseTimeSeconds"), ampEgReleaseTimeSeconds);

	return xml;
}

void SynthParameters::putXml(XmlElement* xml)
{
	xml->getStringAttribute("name").copyToUTF8(programName, sizeof(programName));

	masterLevel = xml->getDoubleAttribute("masterLevel");
	oscBlend = xml->getDoubleAttribute("oscBlend");
	pitchBendUpSemitones = xml->getIntAttribute("pitchBendUpSemitones");
	pitchBendDownSemitones = xml->getIntAttribute("pitchBendDownSemitones");

	osc1Waveform = LookupWF(xml->getStringAttribute("osc1Waveform"));
	osc1PitchOffsetSemitones = xml->getIntAttribute("osc1PitchOffsetSemitones");
	osc1DetuneOffsetCents = xml->getDoubleAttribute("osc1DetuneOffsetCents");

	osc2Waveform = LookupWF(xml->getStringAttribute("osc2Waveform"));
	osc2PitchOffsetSemitones = xml->getIntAttribute("osc2PitchOffsetSemitones");
	osc2DetuneOffsetCents = xml->getDoubleAttribute("osc2DetuneOffsetCents");

	ampEgAttackTimeSeconds = xml->getDoubleAttribute("ampEgAttackTimeSeconds");
	ampEgDecayTimeSeconds = xml->getDoubleAttribute("ampEgDecayTimeSeconds");
	ampEgSustainLevel = xml->getDoubleAttribute("ampEgSustainLevel");
	ampEgReleaseTimeSeconds = xml->getDoubleAttribute("ampEgReleaseTimeSeconds");
}
