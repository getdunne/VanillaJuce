# VanillaJuce

**VanillaJuce** is a simple example of a complete VST2.4 + AUv2 synthesizer built with JUCE 5.1.

When I say **VanillaJuce** is "complete", I don't mean that this is a particularly great synthesizer; in fact, it's not that great at all. What I mean is simply that all of the major plugin requirements are covered, i.e.:
- VST 2.4 compatible plugin builds under Microsoft Visual Studio 2017 (Community version is sufficient)
- Audio Unit v2 compatible plugin builds under Apple XCode (tested with v8.2.1)
- Plugin has a simple GUI editor, using JUCE controls only (no custom graphics)
- Very basic 16-voice synthesizer with 2 oscillators and ADSR amplitude envelope
- Dynamic editing of sound parameters is supported
- Saving and recalling sound programs (via plugin host) is supported

You can find *lots of detailed documentation* about **VanillaJuce** at http://getdunne.net/wiki/doku.php?id=vanillajuce.

Shane Dunne,
August, 2017
