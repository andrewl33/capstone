/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SidebarRotaryLookAndFeel.h"
#include "SidebarVertSliderLookAndFeel.h"

//==============================================================================
/**
*/
class Static_AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Static_AudioProcessorEditor (Static_AudioProcessor&);
    ~Static_AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Static_AudioProcessor& processor;
	Slider dial1;
	Slider dial2;
	Slider dial3;
	Slider dial4;
	Slider dial5;
	Slider dial6;

	// vertical sliders
	Slider slider1;
	Slider slider2;
	Slider slider3;
	Slider slider4;

	const Colour tanColour = Colour((uint8)234, (uint8)213, (uint8)201, (uint8)255);
	const Colour brownColour = Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255);
	const int imageWidth = 736;
	const int totalHeight = 479;
	SidebarRotaryLookAndFeel sidebarRotaryLookAndFeel;
	SidebarVertSliderLookAndFeel sidebarVertSliderLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Static_AudioProcessorEditor)
};
