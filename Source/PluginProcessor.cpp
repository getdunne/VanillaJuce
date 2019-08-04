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
}

void VanillaJuceAudioProcessor::initializePrograms()
{
    for (int i = 0; i < kNumberOfPrograms; i++)
        programBank[i].setDefaultValues();
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
    sendChangeMessage();
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
    std::unique_ptr<XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
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
    XmlElement* xml = programBank[currentProgram].getXml();
    copyXmlToBinary(*xml, destData);
}

void VanillaJuceAudioProcessor::setCurrentProgramStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    programBank[currentProgram].putXml(xml.get());
    sendChangeMessage();
}

// This creates new instances of the plugin.
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VanillaJuceAudioProcessor();
}
