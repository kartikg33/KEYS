/*
  ==============================================================================

    Key.h
    Created: 25 Jan 2018 8:41:13pm
    Author:  Kartik Gohil

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Key    : public Component
{
public:
    Key();
    ~Key();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Key)
};
