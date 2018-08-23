#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "GuiMainTab.h"
#include "GuiOscTab.h"
#include "GuiEgTab.h"
#include "GuiNetTab.h"

class GuiTabs  : public Component
{
public:
    GuiTabs (SynthSound* pSynthSound, DSP_Client& dspClient);
    ~GuiTabs();

    void paint (Graphics& g) override;
    void resized() override;

    void notify();

private:
    ScopedPointer<TabbedComponent> tabbedComponent;
    GuiNetTab* pNetTab;
    GuiMainTab* pMainTab;
    GuiOscTab* pOscTab;
    GuiEgTab* pAmpEgTab;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiTabs)
};
