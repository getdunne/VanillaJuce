# VanillaJuce

**VanillaJuce** is a simple example of a complete VST2.4 + AUv2 synthesizer built with JUCE 5.1.

When I say **VanillaJuce** is "complete", I don't mean that this is a particularly great synthesizer; in fact, it's not that great at all. What I mean is simply that all of the major plugin requirements are covered, i.e.:
- VST 2.4 compatible plugin builds under Microsoft Visual Studio 2017 (Community version is sufficient)
- Audio Unit v2 compatible plugin builds under Apple XCode (tested with v8.2.1)
- Plugin has a simple GUI editor, using JUCE controls only (no custom graphics)
- Very basic 16-voice synthesizer with 2 oscillators and ADSR amplitude envelope
- Dynamic editing of sound parameters is supported
- Saving and recalling sound programs (via plugin host) is supported

The basic **VanillaJuce** doesn't support *parameter automation*. Have a look at the *params-old* branch to see how this can be added using the (deprecated) *AudioParameter* classes. (I'm working on a second implementation using the newer *AudioProcessorValueTreeState* class.)

You can find *lots of detailed documentation* about **VanillaJuce** at http://getdunne.net/wiki/doku.php?id=vanillajuce.

## Code licensing terms
This code is licensed under the terms of the MIT License (below, and also in the file *LICENSE* in this repo). To compile it, you will need a copy of the [JUCE framework](https://juce.com), and the resulting *combined work* will be subject to JUCE's own licensing terms.

It is my explicit INTENT, as the author of this code, that everyone should have the right to use all or part of it in any JUCE-based program, and in the event that any such program should become subject to the GPL3 license (in accordance with the JUCE license terms), that this right should not be abridged. However, I doubt that this statement of intent would carry any weight under the law, so at this point I can only say: USE AT YOUR OWN RISK.

> The MIT License (MIT)
> 
> Copyright (c) 2017-2018 Shane D. Dunne
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
> 
> The above copyright notice and this permission notice shall be included in
> all copies or substantial portions of the Software.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
> THE SOFTWARE.

