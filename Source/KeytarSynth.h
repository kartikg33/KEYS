/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.2.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiKeys.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class KeytarSynth  : public Component,
                     public AudioSource,
                     public Slider::Listener
{
public:
    //==============================================================================
    KeytarSynth ();
    ~KeytarSynth();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setup();
	void prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	// This is used to dispatch an incoming message to the message thread
	struct IncomingMessageCallback : public CallbackMessage
	{
		IncomingMessageCallback(MidiKeys* k, const MidiMessage& m)
			: keys(k), message(m) {}

		void messageCallback() override
		{
			if (keys != nullptr)
				keys->addMessageToList(message);
		}
		Component::SafePointer<MidiKeys> keys;
		MidiMessage message;
	};
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MidiKeys keys; // manager object for keyboard midi device
	AudioFormatManager audioFormatManager; // manager object that finds an appropriate way to decode various audio files.  Used with SampleSound objects.
	File* file; // used to read audio files
	Synthesiser synth; 

	// controls
	double volume = 0.5; // set to half volume

	// graphics 
	ScopedPointer<float> waveform_L = nullptr; // circular buffers of audio samples
	ScopedPointer<float> waveform_R = nullptr; // circular buffers of audio samples
	int waveform_length = 0;
	int waveform_pointer = 0; // circular buffer pointer
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> slider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeytarSynth)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
