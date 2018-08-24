#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

VanillaJuceAudioProcessor::VanillaJuceAudioProcessor()
    : currentProgram(0)
{
    initializePrograms();

    for (int i = 0; i < kNumberOfVoices; ++i)
        synth.addVoice(new SynthVoice());

    pSound = new SynthSound(synth);
    pSound->pParams = &programBank[currentProgram];
    synth.addSound(pSound);

    dspClient.addListener(this);
}

void VanillaJuceAudioProcessor::initializePrograms()
{
    for (int i = 0; i < kNumberOfPrograms; i++)
        programBank[i].setDefaultValues();
}

void VanillaJuceAudioProcessor::queueAllSynthParams()
{
    if (!dspClient.isConnected()) return;

    dspClient.queueParameterUpdate(0, 1.0f);    // set update lock
    for (int paramIndex = 1;
        paramIndex < SynthParameters::ParameterIndex::kNumberOfParameterIndices;
        paramIndex++)
    {
        dspClient.queueParameterUpdate(paramIndex, pSound->pParams->getParam(paramIndex));
    }
    dspClient.queueParameterUpdate(0, 0.0f);    // clear update lock
}

void VanillaJuceAudioProcessor::connectStatusChanged(bool connected)
{
    if (connected) queueAllSynthParams();
}

const String VanillaJuceAudioProcessor::getName() const
{
    return JucePlugin_Name;
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
    sendChangeMessage();    // update GUI
    queueAllSynthParams();  // update remote DSP if connected
}

const String VanillaJuceAudioProcessor::getProgramName (int index)
{
    return programBank[index].programName;
}

void VanillaJuceAudioProcessor::changeProgramName (int index, const String& newName)
{
    programBank[index].programName = newName;
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
    if (dspClient.isConnected())
        dspClient.processBlock(buffer, midiMessages);
    else
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
    xml.setAttribute("currentProgram", currentProgram);
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
    if (xprogs->hasTagName("programs"))
    {
        int i = 0;
        forEachXmlChildElement(*xprogs, xpr)
        {
            programBank[i].setDefaultValues();
            programBank[i].putXml(xpr);
            i++;
        }
    }
    setCurrentProgram(xml->getIntAttribute("currentProgram", 0));
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

    sendChangeMessage();    // update GUI
    queueAllSynthParams();  // update remote DSP if connected
}

// This creates new instances of the plugin.
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VanillaJuceAudioProcessor();
}
