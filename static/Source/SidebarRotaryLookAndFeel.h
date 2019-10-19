/*
  ==============================================================================

    SidebarRotaryLookAndFeel.h
    Created: 19 Oct 2019 1:33:11pm
    Author:  Andrew

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class SidebarRotaryLookAndFeel : public LookAndFeel_V4
{
public:
	SidebarRotaryLookAndFeel() {};
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider&) override;
};