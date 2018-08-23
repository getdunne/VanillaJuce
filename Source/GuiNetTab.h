#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "DSP_Client.h"

class GuiNetTab :   public Component
                ,   public Button::Listener
                ,   public DSP_Client::Listener
{
public:
    GuiNetTab (DSP_Client& dsp_client);

    // Component
    void paint (Graphics& g) override;
    void resized() override;

    // Button::Listener
    void buttonClicked(Button*) override;

    // DSP_Client::Listener
    void connectStatusChanged(bool connected) override;

    // GuiNetTab
    void notify();

private:
    DSP_Client& dspClient;
    Label addressLabel, portLabel, infoLabel;
    TextEditor addressEditor, portEditor;
    TextButton connectButton;
    Label message;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiNetTab)
};
