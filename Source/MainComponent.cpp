/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "KeytarSynth.h"
#include "MidiKeys.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent		: public AudioAppComponent
								, private Timer
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize (1280, 720); // raspberry pi 7'' touchscreen

        // specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
        
		// add keytar synth ui to main component
		keytar.setTopLeftPosition(0, 0);
        addAndMakeVisible(keytar); 
		
		// load synth
		keytar.setup();

		// use a timer to keep repainting this component
		startTimerHz(1000); // will be painted 100 times a second 
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()
		keytar.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
		// clear the buffer to remove any noise
        bufferToFill.clearActiveBufferRegion();   

		// fill the audio buffer with the keytar output
		keytar.getNextAudioBlock(bufferToFill);
		
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
		keytar.releaseResources();
	}

    //==============================================================================
    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        // You can add your drawing code here!
		keytar.paint(g);
    }

	void timerCallback() override
	{
		repaint();
	}

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
		keytar.centreWithSize(getWidth(), getHeight());
		keytar.resized();
    }


private:
    //==============================================================================

    // Your private member variables go here...
    KeytarSynth keytar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }
