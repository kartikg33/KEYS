/*
  ==============================================================================

    MidiKeys.h
    Created: 30 Jan 2018 10:38:34am
    Author:  Kartik Gohil
	Brief:	 This class manages external MIDI devices and handles MIDI messages

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/

/** Simple list box that just displays a StringArray. */
class MidiLogListBoxModel : public ListBoxModel
{
public:
	MidiLogListBoxModel(const Array<MidiMessage>& list);

	int getNumRows() override;

	void paintListBoxItem(int row, Graphics& g, int width, int height, bool rowIsSelected) override;

private:
	const Array<MidiMessage>& midiMessageList;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiLogListBoxModel)
};

//==============================================================================

class MidiKeys	: public Component
				, private ComboBox::Listener
				, private MidiInputCallback
				, private MidiKeyboardStateListener
				, private AsyncUpdater
{
public:
    MidiKeys();
    ~MidiKeys();

	MidiBuffer midiMessages;
	void addMessageToList(const MidiMessage& message); // debug function to see incoming messages

    void paint (Graphics&) override;
    void resized() override;

private:
	AudioDeviceManager deviceManager;
	ComboBox midiInputList;
	Label midiInputListLabel;
	int lastInputIndex; // used to store previous midi input 

	MidiKeyboardState keyboardState;
	MidiKeyboardComponent keyboardComponent;

	ListBox messageListBox;
	Array<MidiMessage> midiMessageList;
	MidiLogListBoxModel midiLogListBoxModel;
	unsigned long midiMessagesSampleNum;
	

	// prototypes
	void setMidiInput(int index);
	void comboBoxChanged(ComboBox* box) override;
	void handleIncomingMidiMessage(MidiInput*, const MidiMessage& message) override;
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void postMessageToBuffer(const MidiMessage& message);
	void handleAsyncUpdate() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiKeys)
};
