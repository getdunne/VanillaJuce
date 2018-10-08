/* Copyright (c) 2017-2018 Shane D. Dunne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "GuiNetTab.h"

GuiNetTab::GuiNetTab (DSP_Client& dsp_client)
    : dspClient(dsp_client)
    , addressLabel("address", TRANS("Address"))
    , portLabel("portnum", TRANS("Port#"))
    , infoLabel("info", TRANS("By default, DSP will be run locally."
        " To run remotely, enter the IP address and port number for the remote DSP service"
        " and click the Connect button."))
{
    auto initLabel = [this](Label& label, Justification justification)
    {
        addAndMakeVisible(label);
        label.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
        label.setJustificationType(justification);
        label.setEditable(false, false, false);
        label.setColour(TextEditor::textColourId, Colours::black);
        label.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    };

    initLabel(infoLabel, Justification::left);
    initLabel(message, Justification::horizontallyCentred);
    initLabel(addressLabel, Justification::right);
    initLabel(portLabel, Justification::right);

    addAndMakeVisible(addressEditor);
    addressEditor.setText("127.0.0.1");
    addAndMakeVisible(portEditor);
    portEditor.setText("27016");

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
    auto editArea = bounds.removeFromTop(30);
    addressLabel.setBounds(editArea.removeFromLeft(100));
    addressEditor.setBounds(editArea.removeFromLeft(200));
    portLabel.setBounds(editArea.removeFromLeft(100));
    portEditor.setBounds(editArea);

    bounds.removeFromTop(10);
    connectButton.setBounds(bounds.removeFromTop(30));

    bounds.removeFromTop(10);
    message.setBounds(bounds.removeFromTop(40));
}

void GuiNetTab::buttonClicked(Button*)
{
    if (dspClient.isConnected())
    {
        dspClient.disconnect();
    }
    else
    {
        String address = addressEditor.getText();
        int portNumber = portEditor.getText().getIntValue();
        if (!dspClient.connect(address, portNumber))
        {
            message.setText("Unable to connect: check address and port number", NotificationType::dontSendNotification);
        }
        else
        {
            message.setText("", NotificationType::dontSendNotification);
        }
    }
}

void GuiNetTab::connectStatusChanged(bool connected)
{
    const MessageManagerLock mmLock;
    connectButton.setButtonText(connected ? "Disconnect" : "Connect");
}

void GuiNetTab::notify()
{
}
