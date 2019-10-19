/*
  ==============================================================================

    SidebarVertSliderLookAndFeel.cpp
    Created: 19 Oct 2019 1:57:47pm
    Author:  Andrew

  ==============================================================================
*/

#include "SidebarVertSliderLookAndFeel.h"

void SidebarVertSliderLookAndFeel::drawLinearSlider(Graphics& g,
	int 	x,
	int 	y,
	int 	width,
	int 	height,
	float 	sliderPos,
	float 	minSliderPos,
	float 	maxSliderPos,
	const Slider::SliderStyle,
	Slider&
) 
{
	g.setColour(brownColour);


	g.drawLine((float)x+(width/2), (float)y, (float)x + (width / 2), (float)maxSliderPos, 4.0);


	g.setColour(brownColour);
	Rectangle< float > rectangle ((width / 2)-5, sliderPos, 10, 5);

	g.drawRoundedRectangle(rectangle, 0.5, 4);
	g.setColour(tanColour);
	g.fillRect(rectangle);
}