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
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthWaveform.h"

class SynthParameters
{
public:
    String programName;

    // main
    float masterLevel;
    float oscBlend;                        // [0.0, 1.0] relative osc1 level
    int pitchBendUpSemitones;
    int pitchBendDownSemitones;
    
    // osc 1
    SynthWaveform osc1Waveform;
    int osc1PitchOffsetSemitones;
    float osc1DetuneOffsetCents;
    
    // osc 2
    SynthWaveform osc2Waveform;
    int osc2PitchOffsetSemitones;
    float osc2DetuneOffsetCents;
    
    // amp EG
    float ampEgAttackTimeSeconds;
    float ampEgDecayTimeSeconds;
    float ampEgSustainLevel;               // [0.0, 1.0]
    float ampEgReleaseTimeSeconds;

public:
    // Set default values
    void setDefaultValues();

    // Save and Restore from XML
    XmlElement* getXml();
    void putXml(XmlElement* xml);
};
