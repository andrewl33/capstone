/*
  ==============================================================================

    SidebarVertSliderLookAndFeel.h
    Created: 19 Oct 2019 1:57:47pm
    Author:  Andrew

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class SidebarVertSliderLookAndFeel : public LookAndFeel_V4
{
public: 
	SidebarVertSliderLookAndFeel() {};
	void drawLinearSlider(Graphics&,
		int 	x,
		int 	y,
		int 	width,
		int 	height,
		float 	sliderPos,
		float 	minSliderPos,
		float 	maxSliderPos,
		const Slider::SliderStyle,
		Slider&
	) override;
private:
	const Colour tanColour = Colour((uint8)234, (uint8)213, (uint8)201, (uint8)255);
	const Colour brownColour = Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255);
};