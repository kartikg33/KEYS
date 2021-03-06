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

#include "UI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
UI::UI ()
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

    setSize (800, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

UI::~UI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 12, y = 12, width = 108, height = 52;
        String text (TRANS("KEYS"));
        Colour fillColour = Colour (0xff4ca0df);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (49.60f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 16, y = 60, width = 108, height = 20;
        String text (TRANS("Kartik Gohil"));
        Colour fillColour = Colour (0xffb1d9f7);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 60, y = 500, width = 108, height = 30;
        String text (TRANS("Volume"));
        Colour fillColour = Colour (0xffc6c38a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (20.20f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    slider->setBounds (46, 412, 136, 96);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void UI::sliderValueChanged (Slider* sliderThatWasMoved)
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
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UI" componentName="" parentClasses="public Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="800"
                 initialHeight="600">
  <BACKGROUND backgroundColour="ff323e44">
    <TEXT pos="12 12 108 52" fill="solid: ff4ca0df" hasStroke="0" text="KEYS"
          fontname="Default font" fontsize="49.600000000000001421" kerning="0"
          bold="0" italic="0" justification="33"/>
    <TEXT pos="16 60 108 20" fill="solid: ffb1d9f7" hasStroke="0" text="Kartik Gohil"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="33"/>
    <TEXT pos="60 500 108 30" fill="solid: ffc6c38a" hasStroke="0" text="Volume"
          fontname="Default font" fontsize="20.199999999999999289" kerning="0"
          bold="0" italic="0" justification="36"/>
  </BACKGROUND>
  <SLIDER name="sldr_Volume" id="f301e62471c2d990" memberName="slider"
          virtualName="" explicitFocusOrder="0" pos="46 412 136 96" bkgcol="ffbe2a30"
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
