#include "GuiNetTab.h"

GuiNetTab::GuiNetTab (DSP_Client& dsp_client)
    : dspClient(dsp_client)
    , infoLabel("info", TRANS("By default, DSP will be run locally."
        " To run remotely, enter the IP address and port number for the remote DSP service"
        " and click the Connect button."))
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
        label.setJustificationType(Justification::left);
        label.setEditable(false, false, false);
        label.setColour(TextEditor::textColourId, Colours::black);
        label.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    };

    initLabel(infoLabel);

    addAndMakeVisible(connectButton);
    connectButton.setButtonText("Connect");
    connectButton.addListener(this);

    dspClient.addListener(this);
}

void GuiNetTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiNetTab::resized()
{
    auto bounds = getLocalBounds();
    bounds.reduce(20, 20);
    infoLabel.setBounds(bounds.removeFromTop(40));

    bounds.removeFromTop(10);
    connectButton.setBounds(bounds.removeFromTop(30));
}

void GuiNetTab::buttonClicked(Button*)
{
    if (dspClient.isConnected())
        dspClient.disconnect();
    else
        dspClient.connect("127.0.0.1", 27016);
}

void GuiNetTab::connectStatusChanged(bool connected)
{
    const MessageManagerLock mmLock;
    connectButton.setButtonText(connected ? "Connected: click to disconnect" : "Connect");
}

void GuiNetTab::notify()
{
}
