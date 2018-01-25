/*
  ==============================================================================

    Keytar.h
    Created: 25 Jan 2018 8:40:58pm
    Author:  Kartik Gohil

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Keytar    : public Component
{
public:
    Keytar();
    ~Keytar();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Keytar)
};
