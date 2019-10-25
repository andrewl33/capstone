/*
  ==============================================================================

    MainDialLookAndFeel.h
    Created: 24 Oct 2019 2:58:48pm
    Author:  Andrew

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class MainDialLookAndFeel : public LookAndFeel_V4
{
public:
	MainDialLookAndFeel() {};
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider&) override;
};