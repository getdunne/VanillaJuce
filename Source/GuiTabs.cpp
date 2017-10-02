#include "GuiTabs.h"

GuiTabs::GuiTabs (SynthSound* pSynthSound, float scale)
    : mainTab(pSynthSound, scale)
    , oscTab(pSynthSound, scale)
    , ampEgTab(pSynthSound, scale)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (32);
    tabbedComponent->addTab(TRANS("Main"), Colours::lightgrey, &mainTab, false);
    tabbedComponent->addTab(TRANS("Osc"), Colours::lightgrey, &oscTab, false);
    tabbedComponent->addTab(TRANS("AmpEG"), Colours::lightgrey, &ampEgTab, false);
    tabbedComponent->setCurrentTabIndex(0);
}

void GuiTabs::setScaleFactor(float scale)
{
    mainTab.setScaleFactor(scale);
    oscTab.setScaleFactor(scale);
    ampEgTab.setScaleFactor(scale);
}

void GuiTabs::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiTabs::resized()
{
    tabbedComponent->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
}

void GuiTabs::notify()
{
    mainTab.notify();
    oscTab.notify();
    ampEgTab.notify();
}
