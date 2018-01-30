/*
  ==============================================================================

    MidiKeys.cpp
    Created: 30 Jan 2018 10:38:34am
    Author:  Kartik Gohil

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiKeys.h"
#include "MainComponent.cpp"

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
	: lastInputIndex(0), isAddingFromMidiInput(false)
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

	// find the first enabled device and use that by default
	for (int i = 0; i < midiInputs.size(); ++i)
	{
		if (deviceManager.isMidiInputEnabled(midiInputs[i]))
		{
			setMidiInput(i);
			break;
		}
	}

	// if no enabled devices were found just use the first one in the list
	if (midiInputList.getSelectedId() == 0)
		setMidiInput(0);


	// MIDI Outputs
	addAndMakeVisible(midiOutputListLabel);
	midiOutputListLabel.setText("MIDI Output:", dontSendNotification);
	midiOutputListLabel.attachToComponent(&midiOutputList, true);

	addAndMakeVisible(midiOutputList);
	midiOutputList.setTextWhenNoChoicesAvailable("No MIDI Output Enabled");
	midiOutputList.addItemList(MidiOutput::getDevices(), 1);
	midiOutputList.addListener(this);

	addAndMakeVisible(keyboardComponent);
	keyboardState.addListener(this);

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
	midiOutputList.setBounds(area.removeFromTop(36).removeFromRight(getWidth() - 150).reduced(8));
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
void MidiKeys::setMidiOutput(int index)
{
	currentMidiOutput = nullptr;

	if (MidiOutput::getDevices()[index].isNotEmpty())
	{
		currentMidiOutput = MidiOutput::openDevice(index);
		jassert(currentMidiOutput);
	}
}

void MidiKeys::comboBoxChanged(ComboBox* box) 
{
	if (box == &midiInputList)    setMidiInput(midiInputList.getSelectedItemIndex());
	if (box == &midiOutputList)   setMidiOutput(midiOutputList.getSelectedItemIndex());
}

// These methods handle callbacks from the midi device + on-screen keyboard..
void MidiKeys::handleIncomingMidiMessage(MidiInput*, const MidiMessage& message) 
{
	const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
	keyboardState.processNextMidiEvent(message);
	postMessageToList(message);
}

void MidiKeys::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) 
{
	if (!isAddingFromMidiInput)
	{
		MidiMessage m(MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity));
		m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
		postMessageToList(m);
	}
}

void MidiKeys::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) 
{
	if (!isAddingFromMidiInput)
	{
		MidiMessage m(MidiMessage::noteOff(midiChannel, midiNoteNumber, velocity));
		m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
		postMessageToList(m);
	}
}

void MidiKeys::postMessageToList(const MidiMessage& message)
{
	if (currentMidiOutput != nullptr)
		currentMidiOutput->sendMessageNow(message);

	(new IncomingMessageCallback(this, message))->post();
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