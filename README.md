# VanillaJuce

**VanillaJuce** is a simple example of a "complete" synthesizer plug-in built with JUCE 5.1.

When I say "complete", I don't mean that this is a particularly great synthesizer; in fact, it's not that great at all. What I mean is simply that all of the major plug-in requirements are covered, i.e.:
- VST 2.4 compatible plug-in builds under Microsoft Visual Studio 2017 (Community version is sufficient)
- Audio Unit v2 compatible plug-in builds under Apple XCode (tested with v8.2.1)
- Plug-in has a simple GUI editor (using JUCE built-in controls only, no custom graphics)
- Very basic 16-voice synthesizer with 2 oscillators and ADSR amplitude envelope
- Dynamic editing of sound parameters is supported
- Saving and recalling sound programs (via plug-in host) is supported

The basic **VanillaJuce** doesn't support *parameter automation*. See https://github.com/getdunne/juce-AudioParameterTest.)

You can find *lots of detailed documentation* about **VanillaJuce** at http://getdunne.net/wiki/doku.php?id=vanillajuce.

## Code licensing terms
This code is licensed under the terms of the MIT License (see the file *LICENSE* in this repo). To compile it, you will need a copy of the [JUCE framework](https://juce.com), and the resulting *combined work* will be subject to JUCE's own licensing terms, and under certain circumstances may become subject to the [GNU General Public License, version 3 (GPL3)](https://www.gnu.org/licenses/gpl-3.0.en.html).

I am grateful to Julian Storer of Roli, Inc. for clarifying, via the [JUCE Forum](https://forum.juce.com/t/open-source-without-gpl/29721), that this code will continue to be freely usable under the terms of the MIT license, because
1. The MIT license is "GPL3 compatible" according to the Free Software Foundation.
2. Clause 5(c) of the GPL3 specifically states that it does not invalidate less restrictive usage permissions explicitly granted by a copyright holder.
3. The JUCE license does not affect copyright status of MIT-licensed code in combined works.

In light of these considerations, and for maximum clarity, I have added my copyright notice and the full text of the MIT license to every one of the source files in this repo.

Shane Dunne, October 2018
