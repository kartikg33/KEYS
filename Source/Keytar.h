/*
  ==============================================================================

    Keytar.h
    Created: 25 Jan 2018 9:06:10pm
    Author:  Kartik Gohil

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Keytar : public Synthesiser {
    
public:
    Keytar();
    ~Keytar();
    
    void setup();
    
private:
    // manager object that finds an appropriate way to decode various audio files.  Used with SampleSound objects.
    AudioFormatManager audioFormatManager;
};