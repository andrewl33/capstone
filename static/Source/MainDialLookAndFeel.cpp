/*
  ==============================================================================

    MainDialLookAndFeel.cpp
    Created: 24 Oct 2019 2:58:48pm
    Author:  Andrew

  ==============================================================================
*/

#include "MainDialLookAndFeel.h"

void MainDialLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider&) 
{
	auto radius = jmin(width / 2, height / 2) - 4.0f;
	auto centreX = x + width * 0.5f;
	auto centreY = y + height * 0.5f;
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	
	// set a static image background
	Image background = ImageCache::getFromMemory(BinaryData::staticdial_png, BinaryData::staticdial_pngSize);
	g.drawImageTransformed(background,AffineTransform::rotation(angle-rotaryStartAngle, centreX, centreY), 0);

	// outline
	g.setColour(Colours::whitesmoke);
	g.drawEllipse(rx, ry, rw, rw, 10.0f);

	Path pointer;
	Path progress;
	auto pointerLength = radius * 1.0f;
	auto pointerThickness = 5.0f;
	pointer.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength - 1);
	progress.addCentredArc(centreX, centreY, radius, radius, 0, rotaryStartAngle, angle, true);
	pointer.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
	

	// pointer
	g.setColour(Colour((uint8)234, (uint8)213, (uint8)201, (uint8)255));
	g.strokePath(pointer, PathStrokeType(10.0f, PathStrokeType::JointStyle::curved));
	g.strokePath(progress, PathStrokeType(10.0f, PathStrokeType::JointStyle::curved));
}