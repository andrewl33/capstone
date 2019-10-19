/*
  ==============================================================================

    SidebarRotaryLookAndFeel.cpp
    Created: 19 Oct 2019 1:33:11pm
    Author:  Andrew

  ==============================================================================
*/

#include "SidebarRotaryLookAndFeel.h"

void SidebarRotaryLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider&)
{
	auto radius = jmin(width / 2, height / 2) - 4.0f;
	auto centreX = x + width * 0.5f;
	auto centreY = y + height * 0.5f;
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

	// fill
	g.setColour(Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255));
	g.fillEllipse(rx, ry, rw, rw);

	Path p;
	auto pointerLength = radius * 1.0f;
	auto pointerThickness = 3.0f;
	p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
	p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

	// pointer
	g.setColour(Colour((uint8)234, (uint8)213, (uint8)201, (uint8)255));
	g.fillPath(p);
}