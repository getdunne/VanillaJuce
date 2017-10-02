#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "GuiMainTab.h"
#include "GuiOscTab.h"
#include "GuiEgTab.h"

class GuiTabs  : public Component
{
public:
    GuiTabs (SynthSound* pSynthSound, float scale);
    void setScaleFactor(float scale);

    void paint (Graphics& g) override;
    void resized() override;

    void notify();

private:
    ScopedPointer<TabbedComponent> tabbedComponent;
    GuiMainTab mainTab;
    GuiOscTab oscTab;
    GuiEgTab ampEgTab;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiTabs)
};
