# VanillaJuce

**VanillaJuce** is a simple example of a complete VST2.4 + AUv2 synthesizer built with JUCE 5.1.

In this context, "complete" doesn't mean that this is a particularly great synthesizer; rather, it means that all of the major plugin requirements are covered, i.e.:
- VST 2.4 compatible plugin builds under Microsoft Visual Studio 2017 (Community version is sufficient)
- Audio Unit v2 compatible plugin builds under Apple XCode 8.3.3
- Plugin has a simple GUI editor, using JUCE controls only (no custom graphics)
- Very basic 16-voice synthesizer with 2 oscillators and ADSR amplitude envelope
- Dynamic editing of sound parameters is supported
- Saving and recalling sound programs (via plugin host) is supported

As a synthesizer, **VanillaJuce** is nothing special; it's not meant to be. Its oscillators are about as simple as possible, and as a result they don't sound very nice, mainly due to *aliasing* which is particularly noticeable when playing higher-pitched notes. Its envelope generators (which nicely illustrate the use of JUCE's *LinearSmoothedValue* template class) provide just enough dynamics that **VanillaJuce** can charitably be called a "synthesizer" rather than an "organ".

Critically, **VanillaJuce** has *no filters*, and thus some might argue that it's "not a real synthesizer". I chose to leave out filters and filter envelope generators (EGs) for four reasons:
1. These things get us into the realm of digital signal processing (DSP), which could greatly complicate what I intended as a simple code example to help the beginning JUCE user get started.
2. Pragmatically, there's not much point in adding filtering without first addressing aliasing in the oscillators.
2. The code already illustrates how to create EGs; adding filter EGs wouldn't teach anything new.

There are already enough books and internet resources on DSP and synthesizer design, but I found getting started with JUCE to be a major hurdle. The relevant code examples at www.juce.com were either too large ("kitchen sink demos") or more frequently, too small (not "complete" in the sense I describe above), so I after figuring out what I needed the hard way, I decided to provide **VanillaJuce** as an open-source *(GPL v3)* code example.

Shane Dunne,
August, 2017
