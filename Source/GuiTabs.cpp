#include "GuiTabs.h"

GuiTabs::GuiTabs (SynthSound* pSynthSound)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (32);
    tabbedComponent->addTab(TRANS("Main"), Colours::lightgrey, pMainTab = new GuiMainTab(pSynthSound), true);
    tabbedComponent->addTab(TRANS("Osc"), Colours::lightgrey, pOscTab = new GuiOscTab(pSynthSound), true);
    tabbedComponent->addTab(TRANS("AmpEG"), Colours::lightgrey, pAmpEgTab = new GuiEgTab(pSynthSound), true);
    tabbedComponent->setCurrentTabIndex(0);
}

GuiTabs::~GuiTabs()
{
}

//==============================================================================
void GuiTabs::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiTabs::resized()
{
    tabbedComponent->setBounds (0, 0, getWidth(), getWidth());
}

void GuiTabs::notify()
{
    pMainTab->notify();
    pOscTab->notify();
    pAmpEgTab->notify();
}
