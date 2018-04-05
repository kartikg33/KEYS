/*
  ==============================================================================

    MidiKeys.cpp
    Created: 30 Jan 2018 10:38:34am
    Author:  Kartik Gohil
	Brief:	 This class manages external MIDI devices and handles MIDI messages

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiKeys.h"

//==============================================================================


MidiLogListBoxModel::MidiLogListBoxModel(const Array<MidiMessage>& list)
	: midiMessageList(list)
{
}

int MidiLogListBoxModel::getNumRows() { return midiMessageList.size(); }

void MidiLogListBoxModel::paintListBoxItem(int row, Graphics& g, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
		g.fillAll(Colours::blue.withAlpha(0.2f));

	if (isPositiveAndBelow(row, midiMessageList.size()))
	{
		//g.setColour(getUIColourIfAvailable(LookAndFeel_V4::ColourScheme::UIColour::defaultText, Colours::black));

		const MidiMessage& message = midiMessageList.getReference(row);
		double time = message.getTimeStamp();

		g.drawText(String::formatted("%02d:%02d:%02d",
			((int)(time / 3600.0)) % 24,
			((int)(time / 60.0)) % 60,
			((int)time) % 60)
			+ "  -  " + message.getDescription(),
			Rectangle<int>(width, height).reduced(4, 0),
			Justification::centredLeft, true);
	}
}

//==============================================================================

MidiKeys::MidiKeys()
	:  lastInputIndex(0)
	, keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard)
	, midiLogListBoxModel(midiMessageList)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	setOpaque(true);

	// MIDI Inputs
	addAndMakeVisible(midiInputListLabel);
	midiInputListLabel.setText("MIDI Input:", dontSendNotification);
	midiInputListLabel.attachToComponent(&midiInputList, true);

	addAndMakeVisible(midiInputList);
	midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
	const StringArray midiInputs(MidiInput::getDevices());
	midiInputList.addItemList(midiInputs, 1);
	midiInputList.addListener(this);

	// find the first  Arduino device and use that by default
	for (int i = 0; i < midiInputs.size(); ++i)
	{
		if (midiInputs[i].contains("Arduino"))
		{
			setMidiInput(i);
			break;
		}
	}

	// if no enabled devices were found just use the first one in the list
	if (midiInputList.getSelectedId() == 0)
		setMidiInput(0);


	// show keyboard
	addAndMakeVisible(keyboardComponent);
	keyboardState.addListener(this);

	// show midi messages box
	addAndMakeVisible(messageListBox);
	messageListBox.setModel(&midiLogListBoxModel);
}

MidiKeys::~MidiKeys()
{
	keyboardState.removeListener(this);
	deviceManager.removeMidiInputCallback(MidiInput::getDevices()[midiInputList.getSelectedItemIndex()], this);
	midiInputList.removeListener(this);
}

void MidiKeys::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("MidiKeys", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text

}

void MidiKeys::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
	Rectangle<int> area(getLocalBounds());
	midiInputList.setBounds(area.removeFromTop(36).removeFromRight(getWidth() - 150).reduced(8));
	keyboardComponent.setBounds(area.removeFromTop(80).reduced(8));
	messageListBox.setBounds(area.reduced(8));
}


//==============================================================================
/** Starts listening to a MIDI input device, enabling it if necessary. */
void MidiKeys::setMidiInput(int index)
{
	const StringArray list(MidiInput::getDevices());

	deviceManager.removeMidiInputCallback(list[lastInputIndex], this);

	const String newInput(list[index]);

	if (!deviceManager.isMidiInputEnabled(newInput))
		deviceManager.setMidiInputEnabled(newInput, true);

	deviceManager.addMidiInputCallback(newInput, this);
	midiInputList.setSelectedId(index + 1, dontSendNotification);

	lastInputIndex = index;
}

//==============================================================================

void MidiKeys::comboBoxChanged(ComboBox* box) 
{
	if (box == &midiInputList)    setMidiInput(midiInputList.getSelectedItemIndex());
}

// These methods handle callbacks from the midi device + on-screen keyboard..
void MidiKeys::handleIncomingMidiMessage(MidiInput*, const MidiMessage& message) 
{
	keyboardState.processNextMidiEvent(message); // show pressed key on keyboard
	addMessageToQueue(message); // add midi message to collector
}

void MidiKeys::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) 
{
	// do nothing when keyboard key pressed
	(void)midiChannel; // unused parameter
	(void)midiNoteNumber; // unused parameter
	(void)velocity; // unused parameter
}

void MidiKeys::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) 
{
	// do nothing when keyboard key pressed
	(void)midiChannel; // unused parameter
	(void)midiNoteNumber; // unused parameter
	(void)velocity; // unused parameter
}

void MidiKeys::addMessageToList(const MidiMessage& message)
{
	midiMessageList.add(message);
	triggerAsyncUpdate();
}

void MidiKeys::handleAsyncUpdate() 
{
	messageListBox.updateContent();
	messageListBox.scrollToEnsureRowIsOnscreen(midiMessageList.size() - 1);
	messageListBox.repaint();
}