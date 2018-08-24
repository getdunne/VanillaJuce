# VanillaJuce

**VanillaJuce** is a simple example of a complete VST2.4 + AUv2 synthesizer built with JUCE 5.3.

When I say **VanillaJuce** is "complete", I don't mean that this is a particularly great synthesizer; in fact, it's not that great at all. What I mean is simply that all of the major plugin requirements are covered, i.e.:
- VST 2.4 compatible plugin builds under Microsoft Visual Studio 2017 (Community version is sufficient)
- Audio Unit v2 compatible plugin builds under Apple XCode (tested with v8.2.1)
- Plugin has a simple GUI editor, using JUCE controls only (no custom graphics)
- Very basic 16-voice synthesizer with 2 oscillators and ADSR amplitude envelope
- Dynamic editing of sound parameters is supported
- Saving and recalling sound programs (via plugin host) is supported

The basic **VanillaJuce** doesn't support *parameter automation*. Have a look at the *params-old* branch to see how this can be added using the (deprecated) *AudioParameter* classes. (I'm working on a second implementation using the newer *AudioProcessorValueTreeState* class.)

You can find *lots of detailed documentation* about **VanillaJuce** at http://getdunne.net/wiki/doku.php?id=vanillajuce.

### The "network" branch, licensing, and statement of author's intent
The *network* branch includes a small number of additions to the basic **VanillaJuce** code, to allow remote execution of the DSP aspect on another machine running **VanillaJuceNet**, a simplified version of this program which you can find at https://github.com/getdunne/VanillaJuceNet.

According to the JUCE terms of use, this code is automatically subject to the terms of the **GNU General Public License, version 3** ("GPL3"), a copy of which is provided herewith. However, it is my intent that the handful of additions to the original **VanillaJuce** project included in the "network" branch might be usable by anyone, for any purpose, specifically including use within a closed-source commercial application. It is my sincere hope that Roli, Ltd. will at some point grant an exception to the provisions of the GPL3 in this case. Unless and until that occurs, **this code remains subject to the GPL3**.

Shane Dunne,
August, 2018
