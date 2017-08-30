#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

VanillaJuceAudioProcessor::VanillaJuceAudioProcessor()
    : currentProgram(0)
{
    initializePrograms();

    for (int i = 0; i < maxNumberOfVoices; ++i)
        synth.addVoice(new SynthVoice());

    pSound = new SynthSound(synth);
    pSound->pParams = &programBank[currentProgram];
    synth.addSound(pSound);
}

VanillaJuceAudioProcessor::~VanillaJuceAudioProcessor()
{
}

void VanillaJuceAudioProcessor::initializePrograms()
{
    for (int i = 0; i < kNumberOfPrograms; i++)
        programBank[i].setDefaultValues();
}

const String VanillaJuceAudioProcessor::getName() const
{
    return String(JucePlugin_Name);
}

bool VanillaJuceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VanillaJuceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double VanillaJuceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VanillaJuceAudioProcessor::getNumPrograms()
{
    return kNumberOfPrograms;
}

int VanillaJuceAudioProcessor::getCurrentProgram()
{
    return currentProgram;
}

void VanillaJuceAudioProcessor::setCurrentProgram (int index)
{
    currentProgram = index;
    pSound->pParams = &programBank[currentProgram];
    sendChangeMessage();
}

const String VanillaJuceAudioProcessor::getProgramName (int index)
{
    return String(programBank[index].programName);
}

void VanillaJuceAudioProcessor::changeProgramName (int index, const String& newName)
{
    newName.copyToUTF8(programBank[index].programName, kMaxProgramNameLength);
    sendChangeMessage();
}

void VanillaJuceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);

    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void VanillaJuceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void VanillaJuceAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

bool VanillaJuceAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* VanillaJuceAudioProcessor::createEditor()
{
    return new VanillaJuceAudioProcessorEditor(*this);
}

void VanillaJuceAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml = XmlElement("VanillaJuce");
    xml.setAttribute(String("currentProgram"), currentProgram);
    XmlElement* xprogs = new XmlElement("programs");
    for (int i = 0; i < kNumberOfPrograms; i++)
        xprogs->addChildElement(programBank[i].getXml());
    xml.addChildElement(xprogs);
    copyXmlToBinary(xml, destData);
}

void VanillaJuceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    XmlElement* xprogs = xml->getFirstChildElement();
    if (xprogs->hasTagName(String("programs")))
    {
        int i = 0;
        forEachXmlChildElement(*xprogs, xpr)
        {
            programBank[i].setDefaultValues();
            programBank[i].putXml(xpr);
            i++;
        }
    }
    setCurrentProgram(xml->getIntAttribute(String("currentProgram"), 0));
}

void VanillaJuceAudioProcessor::getCurrentProgramStateInformation(MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml = programBank[currentProgram].getXml();
    copyXmlToBinary(*xml, destData);
}

void VanillaJuceAudioProcessor::setCurrentProgramStateInformation(const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    programBank[currentProgram].putXml(xml);
    sendChangeMessage();
}

// This creates new instances of the plugin.
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VanillaJuceAudioProcessor();
}
