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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "KeytarSynth.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#define MAX_VOICES 16
//[/MiscUserDefs]

//==============================================================================
KeytarSynth::KeytarSynth ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	file = nullptr;
    //[/Constructor_pre]

    addAndMakeVisible (sldrVolume = new Slider ("Volume"));
    sldrVolume->setRange (0.1, 10, 0.1);
    sldrVolume->setSliderStyle (Slider::Rotary);
    sldrVolume->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    sldrVolume->setColour (Slider::backgroundColourId, Colour (0xffbe2a30));
    sldrVolume->setColour (Slider::thumbColourId, Colours::aqua);
    sldrVolume->setColour (Slider::trackColourId, Colours::aqua);
    sldrVolume->setColour (Slider::rotarySliderFillColourId, Colours::aqua);
    sldrVolume->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
    sldrVolume->addListener (this);

    addAndMakeVisible (btnMIDISettings = new TextButton ("btnMIDISettings"));
    btnMIDISettings->setButtonText (TRANS("MIDI Settings"));
    btnMIDISettings->setConnectedEdges (Button::ConnectedOnBottom);
    btnMIDISettings->addListener (this);
    btnMIDISettings->setColour (TextButton::buttonColourId, Colour (0xff2c3b3c));
    btnMIDISettings->setColour (TextButton::textColourOffId, Colours::aquamarine);
    btnMIDISettings->setColour (TextButton::textColourOnId, Colours::aqua);

    addAndMakeVisible (cmbInstrument = new ComboBox ("Instrument"));
    cmbInstrument->setEditableText (false);
    cmbInstrument->setJustificationType (Justification::centredLeft);
    cmbInstrument->setTextWhenNothingSelected (TRANS("Select Instrument"));
    cmbInstrument->setTextWhenNoChoicesAvailable (TRANS("No Instruments"));
    cmbInstrument->addListener (this);


    //[UserPreSize]

    //[/UserPreSize]

    setSize (1280, 720);


    //[Constructor] You can add your own custom stuff here..
	sldrVolume->setValue(1, dontSendNotification); // set default value to gain of 1

	// init list of instruments
	cmbInstrument->clear();
	DirectoryIterator iter(File(File::getCurrentWorkingDirectory().getChildFile("../../Samples")), false, "*.wav" ); // look for wav files in Samples directory
	int item_index = 1;
	while (iter.next())
	{
		cmbInstrument->addItem(iter.getFile().getFileNameWithoutExtension(), item_index);
		item_index++;
	}
	if(cmbInstrument->getNumItems() > 0)
		cmbInstrument->setSelectedItemIndex(0); // select 1st instrument by default
    //[/Constructor]
}

KeytarSynth::~KeytarSynth()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	waveform_L = nullptr;
	waveform_R = nullptr;
	if(file != nullptr)
		delete file;
	file = nullptr;
    //[/Destructor_pre]

    sldrVolume = nullptr;
    btnMIDISettings = nullptr;
    cmbInstrument = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void KeytarSynth::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff282529));

    {
        int x = 4, y = -4, width = 108, height = 52;
        String text (TRANS("KEYS"));
        Colour fillColour = Colours::aqua;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (49.60f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 8, y = 44, width = 112, height = 20;
        String text (TRANS("Kartik Gohil"));
        Colour fillColour = Colours::cadetblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 672, y = 0, width = 152, height = 24;
        String text (TRANS("Vol"));
        Colour fillColour = Colours::aqua;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (20.20f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
	const int centreY = getHeight() / 2;

	Path wavePathL;
	Path wavePathR;
	wavePathL.startNewSubPath(0, (float)centreY);
	wavePathR.startNewSubPath(0, (float)centreY);

	// only paint waveforms if arrays exist
	if (waveform_L != nullptr && waveform_R != nullptr) {
		float incr = (getWidth() / float(waveform_length - 1));
		float i = 0.0f;
		for (int x = 0; x < waveform_length; x++) {
			wavePathL.lineTo(i, (float)centreY + (waveform_L[x] * ((float)centreY / 2.0f)));
			wavePathR.lineTo(i, (float)centreY + (waveform_R[x] * ((float)centreY / 2.0f)));
			i += incr;
		}
	}

	g.setColour(Colours::steelblue);
	g.setOpacity(0.5f);
	g.strokePath(wavePathR, PathStrokeType(3.0f));

	g.setColour(Colours::red);
	g.setOpacity(0.5f);
	g.strokePath(wavePathL, PathStrokeType(3.0f));
    //[/UserPaint]
}

void KeytarSynth::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    sldrVolume->setBounds (671, 16, 152, 112);
    btnMIDISettings->setBounds (8, 424, 136, 48);
    cmbInstrument->setBounds (480, 440, 302, 24);
    //[UserResized] Add your own custom resize handling here..
	keys.centreWithSize(getWidth(), getHeight());
    //[/UserResized]
}

void KeytarSynth::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sldrVolume)
    {
        //[UserSliderCode_sldrVolume] -- add your slider handling code here..
		volume = (double)(sldrVolume->getValue()); // set to value of volume slider
        //[/UserSliderCode_sldrVolume]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void KeytarSynth::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnMIDISettings)
    {
        //[UserButtonCode_btnMIDISettings] -- add your button handler code here..
		// add MIDI keys ui to main component
		keys.setTopLeftPosition(0, 0);
		addAndMakeVisible(keys);
        //[/UserButtonCode_btnMIDISettings]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void KeytarSynth::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cmbInstrument)
    {
        //[UserComboBoxCode_cmbInstrument] -- add your combo box handling code here..
		// load selected instrument
		if (file != nullptr)
			delete file;
		file = new File(File::getCurrentWorkingDirectory().getChildFile("../../Samples/" + cmbInstrument->getItemText(cmbInstrument->getSelectedItemIndex()) + ".wav"));

		ScopedPointer<AudioFormatReader> reader = audioFormatManager.createReaderFor(*file);

		// allow our sound to be played on all notes
		BigInteger allNotes;
		allNotes.setRange(0, 128, true);

		// finally, add our sound. The reader will be deleted once synth is done with it
		synth.clearSounds();

		synth.addSound(new SamplerSound("demo sound",
			*reader,
			allNotes,
			60,   // root midi note (note C3 = 60)
			0,  // attack time
			10,  // release time
			10.0  // maximum sample length
		));
        //[/UserComboBoxCode_cmbInstrument]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void KeytarSynth::setup()
{
	if (cmbInstrument->getNumItems() > 0 && cmbInstrument->getSelectedItemIndex() > -1)
	{
		// add voices to our sampler
		for (int i = 0; i < MAX_VOICES; i++) {
			synth.addVoice(new SamplerVoice());
		}

		// set up our AudioFormatManager class as detailed in the API docs
		// we can now use WAV and AIFF files!
		audioFormatManager.registerBasicFormats();

		// load selected instrument
		if (file != nullptr)
			delete file;
		file = new File(File::getCurrentWorkingDirectory().getChildFile("../../Samples/" + cmbInstrument->getItemText(cmbInstrument->getSelectedItemIndex()) + ".wav"));

		ScopedPointer<AudioFormatReader> reader = audioFormatManager.createReaderFor(*file);

		// allow our sound to be played on all notes
		BigInteger allNotes;
		allNotes.setRange(0, 128, true);

		// finally, add our sound. The reader will be deleted once synth is done with it
		synth.clearSounds();

		synth.addSound(new SamplerSound("demo sound",
			*reader,
			allNotes,
			60,   // root midi note (note C3 = 60)
			0,  // attack time
			10,  // release time
			10.0  // maximum sample length
		));
	}

}

void KeytarSynth::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	keys.setCurrentPlaybackSampleRate(sampleRate);
	synth.setCurrentPlaybackSampleRate(sampleRate);

	// set up waveform arrays for graphics
	waveform_length = samplesPerBlockExpected; // samples per block * number of blocks to display // TODO: use sampleRate to come up with a nice number

	if (waveform_L != nullptr && waveform_R != nullptr)
	{
		waveform_L = nullptr;
		waveform_R = nullptr;
	}
	waveform_L = new float[waveform_length];
	waveform_R = new float[waveform_length];
}

void KeytarSynth::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	// the synth always adds its output to the audio buffer, so we have to clear it
	// first..
	bufferToFill.clearActiveBufferRegion();

	// fill a midi buffer with incoming messages from the midi input.
	MidiBuffer incomingMidi;
	keys.getNextBlock(incomingMidi, bufferToFill.numSamples);

	// and now get the synth to process the midi events and generate its output.
	synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
	bufferToFill.buffer->applyGain(volume);

	// save a copy of the buffer waveform for printing
	if (waveform_L != nullptr && waveform_R != nullptr)
	{
		for (int sample = 0; sample < bufferToFill.numSamples; sample+= 10) // take every 10th sample as we don't need that level of detail (printed resolution is 4410Hz)
		{
			waveform_pointer++; // add buffer sample to next element in array
			if (waveform_pointer >= waveform_length)
				waveform_pointer = 0;
			waveform_L[waveform_pointer] = bufferToFill.buffer->getSample(0, sample);
			waveform_R[waveform_pointer] = bufferToFill.buffer->getSample(1, sample);
		}
		// do not update waveform pointer as it will be incremented in the next loop
	}

	// print midi messages to screen
	ScopedPointer<MidiBuffer::Iterator> i = new MidiBuffer::Iterator(incomingMidi);
	MidiMessage message;
	int message_position;
	while (i->getNextEvent(message, message_position))
	{
		(new IncomingMessageCallback(&keys, message))->post();
	}
	i = nullptr;
}

void KeytarSynth::releaseResources()
{
	waveform_L = nullptr;
	waveform_R = nullptr;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="KeytarSynth" componentName=""
                 parentClasses="public Component, public AudioSource" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="1280" initialHeight="720">
  <BACKGROUND backgroundColour="ff282529">
    <TEXT pos="4 -4 108 52" fill="solid: ff00ffff" hasStroke="0" text="KEYS"
          fontname="Default font" fontsize="49.600000000000001421" kerning="0"
          bold="0" italic="0" justification="33"/>
    <TEXT pos="8 44 112 20" fill="solid: ff5f9ea0" hasStroke="0" text="Kartik Gohil"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="33"/>
    <TEXT pos="672 0 152 24" fill="solid: ff00ffff" hasStroke="0" text="Vol"
          fontname="Default font" fontsize="20.199999999999999289" kerning="0"
          bold="0" italic="0" justification="36"/>
  </BACKGROUND>
  <SLIDER name="Volume" id="f301e62471c2d990" memberName="sldrVolume" virtualName=""
          explicitFocusOrder="0" pos="671 16 152 112" bkgcol="ffbe2a30"
          thumbcol="ff00ffff" trackcol="ff00ffff" rotarysliderfill="ff00ffff"
          rotaryslideroutline="ff5f9ea0" min="0.10000000000000000555" max="10"
          int="0.10000000000000000555" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TEXTBUTTON name="btnMIDISettings" id="531f0b272053244d" memberName="btnMIDISettings"
              virtualName="" explicitFocusOrder="0" pos="8 424 136 48" bgColOff="ff2c3b3c"
              textCol="ff7fffd4" textColOn="ff00ffff" buttonText="MIDI Settings"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="Instrument" id="6e6e0e0f0d27412c" memberName="cmbInstrument"
            virtualName="" explicitFocusOrder="0" pos="480 440 302 24" editable="0"
            layout="33" items="" textWhenNonSelected="Select Instrument"
            textWhenNoItems="No Instruments"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
