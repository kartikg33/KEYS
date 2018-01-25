/*
  ==============================================================================

    Keytar.cpp
    Created: 25 Jan 2018 9:06:10pm
    Author:  Kartik Gohil

  ==============================================================================
*/

#include "Keytar.h"
#define MAX_VOICES 16

Keytar::Keytar() 
{
    
}

Keytar::~Keytar()
{
    
}

void Keytar::setup() 
{
    
    // add voices to our sampler
    for (int i = 0; i < MAX_VOICES; i++) {
        addVoice(new SamplerVoice());
    }

    // set up our AudioFormatManager class as detailed in the API docs
    // we can now use WAV and AIFF files!
    audioFormatManager.registerBasicFormats();

    // now that we have our manager, lets read a simple file so we can pass it to our SamplerSound object.
    File* file = new File("file.wav");
    ScopedPointer<AudioFormatReader> reader = audioFormatManager.createReaderFor(*file);

    // allow our sound to be played on all notes
    BigInteger allNotes;
    allNotes.setRange(0, 128, true);

    // finally, add our sound
    addSound(new SamplerSound("default", *reader, allNotes, 60, 0, 10, 10.0));
    
}