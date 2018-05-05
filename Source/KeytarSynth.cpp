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
    sldrVolume->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff209399));
    sldrVolume->addListener (this);

    addAndMakeVisible (btnMIDISettings = new TextButton ("btnMIDISettings"));
    btnMIDISettings->setButtonText (TRANS("MIDI Settings"));
    btnMIDISettings->setConnectedEdges (Button::ConnectedOnBottom);
    btnMIDISettings->addListener (this);
    btnMIDISettings->setColour (TextButton::buttonColourId, Colour (0xff209399));
    btnMIDISettings->setColour (TextButton::textColourOffId, Colours::white);
    btnMIDISettings->setColour (TextButton::textColourOnId, Colours::white);

    addAndMakeVisible (cmbInstrumentRight = new ComboBox ("Instrument"));
    cmbInstrumentRight->setEditableText (false);
    cmbInstrumentRight->setJustificationType (Justification::centredLeft);
    cmbInstrumentRight->setTextWhenNothingSelected (TRANS("Select Instrument for Right Hand"));
    cmbInstrumentRight->setTextWhenNoChoicesAvailable (TRANS("No Instruments"));
    cmbInstrumentRight->addListener (this);

    addAndMakeVisible (sldrVolumeLeft = new Slider ("Volume"));
    sldrVolumeLeft->setRange (0.1, 10, 0.1);
    sldrVolumeLeft->setSliderStyle (Slider::Rotary);
    sldrVolumeLeft->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    sldrVolumeLeft->setColour (Slider::backgroundColourId, Colour (0xffbe2a30));
    sldrVolumeLeft->setColour (Slider::thumbColourId, Colour (0xffff7900));
    sldrVolumeLeft->setColour (Slider::trackColourId, Colour (0xffff7900));
    sldrVolumeLeft->setColour (Slider::rotarySliderFillColourId, Colour (0xffff7900));
    sldrVolumeLeft->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffa32626));
    sldrVolumeLeft->addListener (this);

    addAndMakeVisible (sldrVolumeRight = new Slider ("Volume"));
    sldrVolumeRight->setRange (0.1, 10, 0.1);
    sldrVolumeRight->setSliderStyle (Slider::Rotary);
    sldrVolumeRight->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    sldrVolumeRight->setColour (Slider::backgroundColourId, Colour (0xffbe2a30));
    sldrVolumeRight->setColour (Slider::thumbColourId, Colour (0xffff7900));
    sldrVolumeRight->setColour (Slider::trackColourId, Colour (0xffff7900));
    sldrVolumeRight->setColour (Slider::rotarySliderFillColourId, Colour (0xffff7900));
    sldrVolumeRight->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffa32626));
    sldrVolumeRight->addListener (this);

    addAndMakeVisible (cmbInstrumentLeft = new ComboBox ("Instrument"));
    cmbInstrumentLeft->setEditableText (false);
    cmbInstrumentLeft->setJustificationType (Justification::centredLeft);
    cmbInstrumentLeft->setTextWhenNothingSelected (TRANS("Select Instrument for Left Hand"));
    cmbInstrumentLeft->setTextWhenNoChoicesAvailable (TRANS("No Instruments"));
    cmbInstrumentLeft->addListener (this);


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
    cmbInstrumentRight = nullptr;
    sldrVolumeLeft = nullptr;
    sldrVolumeRight = nullptr;
    cmbInstrumentLeft = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void KeytarSynth::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff081114));

    {
        int x = 6, y = 0, width = 152, height = 52;
        String text (TRANS("KEYS"));
        Colour fillColour = Colour (0xff209399);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font ("Helvetica Neue", 49.60f, Font::plain).withTypefaceStyle ("UltraLight").withExtraKerningFactor (0.128f));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 8, y = 60, width = 144, height = 20;
        String text (TRANS("by Kartik Gohil"));
        Colour fillColour = Colour (0xffa32626);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font ("Helvetica Neue", 14.20f, Font::plain).withTypefaceStyle ("UltraLight").withExtraKerningFactor (0.054f));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 576, y = 592, width = 136, height = 40;
        String text (TRANS("Main Volume"));
        Colour fillColour = Colours::aqua;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font ("Helvetica Neue", 23.30f, Font::plain).withTypefaceStyle ("UltraLight").withExtraKerningFactor (0.053f));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 416, y = 528, width = 80, height = 40;
        String text (TRANS("Left"));
        Colour fillColour = Colour (0xffff7900);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font ("Helvetica Neue", 23.30f, Font::plain).withTypefaceStyle ("UltraLight").withExtraKerningFactor (0.053f));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 792, y = 528, width = 72, height = 40;
        String text (TRANS("Right"));
        Colour fillColour = Colour (0xffff7900);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font ("Helvetica Neue", 23.30f, Font::plain).withTypefaceStyle ("UltraLight").withExtraKerningFactor (0.053f));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 8, y = 44, width = 144, height = 20;
        String text (TRANS("v1.0"));
        Colour fillColour = Colour (0xff209399);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font ("Helvetica Neue", 14.20f, Font::plain).withTypefaceStyle ("UltraLight").withExtraKerningFactor (0.054f));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
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

    sldrVolume->setBounds (540, 520, 200, 200);
    btnMIDISettings->setBounds (1176, 8, 100, 100);
    cmbInstrumentRight->setBounds (742, 640, 530, 64);
    sldrVolumeLeft->setBounds (380, 480, 150, 150);
    sldrVolumeRight->setBounds (750, 480, 150, 150);
    cmbInstrumentLeft->setBounds (8, 640, 530, 64);
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
    else if (sliderThatWasMoved == sldrVolumeLeft)
    {
        //[UserSliderCode_sldrVolumeLeft] -- add your slider handling code here..
        //[/UserSliderCode_sldrVolumeLeft]
    }
    else if (sliderThatWasMoved == sldrVolumeRight)
    {
        //[UserSliderCode_sldrVolumeRight] -- add your slider handling code here..
        //[/UserSliderCode_sldrVolumeRight]
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

    if (comboBoxThatHasChanged == cmbInstrumentRight)
    {
        //[UserComboBoxCode_cmbInstrumentRight] -- add your combo box handling code here..
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
        //[/UserComboBoxCode_cmbInstrumentRight]
    }
    else if (comboBoxThatHasChanged == cmbInstrumentLeft)
    {
        //[UserComboBoxCode_cmbInstrumentLeft] -- add your combo box handling code here..
        //[/UserComboBoxCode_cmbInstrumentLeft]
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
  <BACKGROUND backgroundColour="ff081114">
    <TEXT pos="6 0 152 52" fill="solid: ff209399" hasStroke="0" text="KEYS"
          fontname="Helvetica Neue" fontsize="49.600000000000001421" kerning="0.12800000000000000266"
          bold="0" italic="0" justification="33" typefaceStyle="UltraLight"/>
    <TEXT pos="8 60 144 20" fill="solid: ffa32626" hasStroke="0" text="by Kartik Gohil"
          fontname="Helvetica Neue" fontsize="14.199999999999999289" kerning="0.053999999999999999389"
          bold="0" italic="0" justification="33" typefaceStyle="UltraLight"/>
    <TEXT pos="576 592 136 40" fill="solid: ff00ffff" hasStroke="0" text="Main Volume"
          fontname="Helvetica Neue" fontsize="23.300000000000000711" kerning="0.052999999999999998501"
          bold="0" italic="0" justification="36" typefaceStyle="UltraLight"/>
    <TEXT pos="416 528 80 40" fill="solid: ffff7900" hasStroke="0" text="Left"
          fontname="Helvetica Neue" fontsize="23.300000000000000711" kerning="0.052999999999999998501"
          bold="0" italic="0" justification="36" typefaceStyle="UltraLight"/>
    <TEXT pos="792 528 72 40" fill="solid: ffff7900" hasStroke="0" text="Right"
          fontname="Helvetica Neue" fontsize="23.300000000000000711" kerning="0.052999999999999998501"
          bold="0" italic="0" justification="36" typefaceStyle="UltraLight"/>
    <TEXT pos="8 44 144 20" fill="solid: ff209399" hasStroke="0" text="v1.0"
          fontname="Helvetica Neue" fontsize="14.199999999999999289" kerning="0.053999999999999999389"
          bold="0" italic="0" justification="33" typefaceStyle="UltraLight"/>
  </BACKGROUND>
  <SLIDER name="Volume" id="f301e62471c2d990" memberName="sldrVolume" virtualName=""
          explicitFocusOrder="0" pos="540 520 200 200" bkgcol="ffbe2a30"
          thumbcol="ff00ffff" trackcol="ff00ffff" rotarysliderfill="ff00ffff"
          rotaryslideroutline="ff209399" min="0.10000000000000000555" max="10"
          int="0.10000000000000000555" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TEXTBUTTON name="btnMIDISettings" id="531f0b272053244d" memberName="btnMIDISettings"
              virtualName="" explicitFocusOrder="0" pos="1176 8 100 100" bgColOff="ff209399"
              textCol="ffffffff" textColOn="ffffffff" buttonText="MIDI Settings"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="Instrument" id="6e6e0e0f0d27412c" memberName="cmbInstrumentRight"
            virtualName="" explicitFocusOrder="0" pos="742 640 530 64" editable="0"
            layout="33" items="" textWhenNonSelected="Select Instrument for Right Hand"
            textWhenNoItems="No Instruments"/>
  <SLIDER name="Volume" id="39dc6b38110ed912" memberName="sldrVolumeLeft"
          virtualName="" explicitFocusOrder="0" pos="380 480 150 150" bkgcol="ffbe2a30"
          thumbcol="ffff7900" trackcol="ffff7900" rotarysliderfill="ffff7900"
          rotaryslideroutline="ffa32626" min="0.10000000000000000555" max="10"
          int="0.10000000000000000555" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Volume" id="68022b7c05ec9ac" memberName="sldrVolumeRight"
          virtualName="" explicitFocusOrder="0" pos="750 480 150 150" bkgcol="ffbe2a30"
          thumbcol="ffff7900" trackcol="ffff7900" rotarysliderfill="ffff7900"
          rotaryslideroutline="ffa32626" min="0.10000000000000000555" max="10"
          int="0.10000000000000000555" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <COMBOBOX name="Instrument" id="bc9e01f58f27788" memberName="cmbInstrumentLeft"
            virtualName="" explicitFocusOrder="0" pos="8 640 530 64" editable="0"
            layout="33" items="" textWhenNonSelected="Select Instrument for Left Hand"
            textWhenNoItems="No Instruments"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
