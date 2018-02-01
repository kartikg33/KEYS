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
    //[/Constructor_pre]

    addAndMakeVisible (slider = new Slider ("sldr_Volume"));
    slider->setRange (0, 100, 1);
    slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    slider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider->setColour (Slider::backgroundColourId, Colour (0xffbe2a30));
    slider->setColour (Slider::thumbColourId, Colour (0xffc6c38a));
    slider->setColour (Slider::trackColourId, Colour (0xffc6c38a));
    slider->setColour (Slider::rotarySliderFillColourId, Colour (0xff4ca0df));
    slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff0a2732));
    slider->addListener (this);


    //[UserPreSize]
    slider->setValue(50, dontSendNotification);
    //[/UserPreSize]

    setSize (800, 480);


    //[Constructor] You can add your own custom stuff here..
	// add MIDI keys ui to main component	
	keys.setTopLeftPosition(0, 0);
	//addAndMakeVisible(keys);
    //[/Constructor]
}

KeytarSynth::~KeytarSynth()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    slider = nullptr;
	waveform_L = nullptr;
	waveform_R = nullptr;
	delete file;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void KeytarSynth::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));
	{
		int x = 12, y = 12, width = 108, height = 52;
		String text(TRANS("KEYS"));
		Colour fillColour = Colour(0xff4ca0df);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(49.60f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centredLeft, true);
	}

	{
		int x = 16, y = 60, width = 108, height = 20;
		String text(TRANS("Kartik Gohil"));
		Colour fillColour = Colour(0xffb1d9f7);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centredLeft, true);
	}

	{
		int x = 20, y = 396, width = 108, height = 30;
		String text(TRANS("Volume"));
		Colour fillColour = Colour(0xffc6c38a);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(20.20f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
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

			// debug text
			String text(waveform_L[x]);
			g.drawText(text, 16, 80, 108, 20,
				Justification::centredLeft, true);
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

    slider->setBounds (8, 304, 136, 96);
    //[UserResized] Add your own custom resize handling here..
	keys.centreWithSize(getWidth(), getHeight());
    //[/UserResized]
}

void KeytarSynth::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void KeytarSynth::setup()
{

	// add voices to our sampler
	for (int i = 0; i < MAX_VOICES; i++) {
		synth.addVoice(new SamplerVoice());
	}

	// set up our AudioFormatManager class as detailed in the API docs
	// we can now use WAV and AIFF files!
	audioFormatManager.registerBasicFormats();

	// now that we have our manager, lets read a simple file so we can pass it to our SamplerSound object.
	file = new File(File::getCurrentWorkingDirectory().getChildFile("../../Samples/Bass and Snares/sd1.wav"));
	ScopedPointer<AudioFormatReader> reader = audioFormatManager.createReaderFor(*file);
	
	// set up our AudioFormatReader to read in an audio sample
	WavAudioFormat wavFormat;
	//ScopedPointer<AudioFormatReader> audioReader(wavFormat.createReaderFor(new MemoryInputStream(BinaryData::cello_wav, BinaryData::cello_wavSize, false), true));
	
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

void KeytarSynth::prepareToPlay(int samplesPerBlockExpected, double sampleRate) 
{
	keys.setCurrentPlaybackSampleRate(sampleRate);
	synth.setCurrentPlaybackSampleRate(sampleRate);

	// set up waveform arrays for graphics
	waveform_length = 1000; // samples per block * number of blocks to display // TODO: use sampleRate to come up with a nice number	

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

	// save a copy of the buffer waveform for printing
	if (waveform_L != nullptr && waveform_R != nullptr)
	{
		int index = waveform_pointer;
		for (int sample = 0; sample < bufferToFill.numSamples; sample++)
		{
			index = waveform_pointer + sample; // add buffer samples to next block in array
			if (index >= waveform_length)
				index -= waveform_length;
			waveform_L[index] = bufferToFill.buffer->getSample(0, sample);
			waveform_R[index] = bufferToFill.buffer->getSample(1, sample);
		}

		waveform_pointer = index + 1; // increment pointer to next available element in array
		if (waveform_pointer >= waveform_length)
			waveform_pointer = 0;
	}

	// print midi messages to screen
	ScopedPointer<MidiBuffer::Iterator> i = new MidiBuffer::Iterator(incomingMidi);
	MidiMessage message;
	int message_position;
	while (i->getNextEvent(message, message_position))
	{
		keys.addMessageToList(message);
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
                 overlayOpacity="0.330" fixedSize="0" initialWidth="800" initialHeight="480">
  <BACKGROUND backgroundColour="ff323e44">
    <TEXT pos="12 12 108 52" fill="solid: ff4ca0df" hasStroke="0" text="KEYS"
          fontname="Default font" fontsize="49.600000000000001421" kerning="0"
          bold="0" italic="0" justification="33"/>
    <TEXT pos="16 60 108 20" fill="solid: ffb1d9f7" hasStroke="0" text="Kartik Gohil"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="33"/>
    <TEXT pos="20 396 108 30" fill="solid: ffc6c38a" hasStroke="0" text="Volume"
          fontname="Default font" fontsize="20.199999999999999289" kerning="0"
          bold="0" italic="0" justification="36"/>
  </BACKGROUND>
  <SLIDER name="sldr_Volume" id="f301e62471c2d990" memberName="slider"
          virtualName="" explicitFocusOrder="0" pos="8 304 136 96" bkgcol="ffbe2a30"
          thumbcol="ffc6c38a" trackcol="ffc6c38a" rotarysliderfill="ff4ca0df"
          rotaryslideroutline="ff0a2732" min="0" max="100" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
