

Install apt get:

sudo apt-get update
sudo apt install
sudo apt update

Install the following libraries:
sudo apt-get -y install freeglut3-dev libasound2-dev libfreetype6-dev libjack-dev libx11-dev libxcomposite-dev libxcursor-dev libxinerama-dev mesa-common-dev


Install the following libraries:
sudo apt-get install libxrandr-dev libwebkit-dev

Install GCC and G++:
sudo apt-get install gcc-4.7 g++-4.7

Install :
webkit2gtk-4.0
gtk+-x11-3.0

Edit the Makefile in two places:

First here:

	ifndef CONFIG
		CONFIG=Release
	endif

And then change TARGET_ARCH here:

	ifeq ($(TARGET_ARCH),)
	# TK: leads to segfault if the processor is older than the one the program was compiled with
	# I got this info from forum user Musical
	TARGET_ARCH := -march=armv6
	endif

Then in /mios_studio/JuceLibraryCode/modules/juce_gui_basics/ juce_gui_basics.h I added this #define:

	// This is an auto-generated file to redirect any included
	// module headers to the correct external folder.

	#include "../../../../juce/modules/juce_gui_basics/juce_gui_basics.h"

	#define JUCE_USE_XINERAMA 0

And last, in /mios_studio/JuceLibraryCode/AppConfig.h I added the last two #defines.

	//==============================================================================
	#define JUCE_MODULE_AVAILABLE_juce_audio_basics          1
	#define JUCE_MODULE_AVAILABLE_juce_audio_devices         1
	#define JUCE_MODULE_AVAILABLE_juce_audio_formats         1
	#define JUCE_MODULE_AVAILABLE_juce_audio_processors      1
	#define JUCE_MODULE_AVAILABLE_juce_audio_utils           1
	#define JUCE_MODULE_AVAILABLE_juce_core                  1
	#define JUCE_MODULE_AVAILABLE_juce_data_structures       1
	#define JUCE_MODULE_AVAILABLE_juce_events                1
	#define JUCE_MODULE_AVAILABLE_juce_graphics              1
	#define JUCE_MODULE_AVAILABLE_juce_gui_basics            1
	#define JUCE_MODULE_AVAILABLE_juce_gui_extra             1
	#define JUCE_USE_XSHM 0
	#define JUCE_USE_XINERAMA 0

	//==============================================================================