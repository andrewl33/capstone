/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
Static_AudioProcessorEditor::Static_AudioProcessorEditor (Static_AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	// Add slider1 params
	// slider1.setSliderStyle(Slider::LinearBarVertical);
	dial1.setSliderStyle(Slider::Rotary);
	// slider1.setRange(0.0, 127.0, 1.0);
	dial1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&dial1);

	dial2.setSliderStyle(Slider::Rotary);
	dial2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&dial2);

	dial3.setSliderStyle(Slider::Rotary);
	dial3.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&dial3);

	dial4.setSliderStyle(Slider::Rotary);
	dial4.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&dial4);

	dial5.setSliderStyle(Slider::Rotary);
	dial5.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&dial5);

	dial6.setSliderStyle(Slider::Rotary);
	dial6.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&dial6);

	slider1.setSliderStyle(Slider::LinearVertical);
	slider1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&slider1);

	slider2.setSliderStyle(Slider::LinearVertical);
	slider2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&slider2);

	slider3.setSliderStyle(Slider::LinearVertical);
	slider3.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&slider3);

	slider4.setSliderStyle(Slider::LinearVertical);
	slider4.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&slider4);

	setSize(929, totalHeight);
}

Static_AudioProcessorEditor::~Static_AudioProcessorEditor()
{
}

//==============================================================================
void Static_AudioProcessorEditor::paint (Graphics& g)
{
	Image background = ImageCache::getFromMemory(BinaryData::blot_jpg, BinaryData::blot_jpgSize);
	
	g.drawImageAt(background, 0, 0);

	Rectangle<int> area(Point<int> (imageWidth,0), Point<int>(getLocalBounds().getWidth(), getLocalBounds().getHeight()));
	g.setColour(tanColour);
	g.fillRect(area);
}

void Static_AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto border = 4;
	
	auto area = getLocalBounds();
	const auto sideWidth = area.getWidth() - imageWidth;
	const auto middleSideWidth = imageWidth + (sideWidth / 2);
	const auto dialSize = totalHeight / 6;
	const auto vertSliderW = middleSideWidth / 4;
	const auto vertSliderTop = totalHeight / 2;
	
	// set dial positions
	dial1.setBounds(middleSideWidth - dialSize - 3, 0, dialSize, dialSize);
	dial2.setBounds(middleSideWidth + 3, 0, dialSize, dialSize);
	dial3.setBounds(middleSideWidth - dialSize - 3, dialSize*.9, dialSize, dialSize);
	dial4.setBounds(middleSideWidth + 3, dialSize * .9, dialSize, dialSize);
	dial5.setBounds(middleSideWidth - dialSize - 3, 1.8 * dialSize, dialSize, dialSize);
	dial6.setBounds(middleSideWidth + 3, dialSize * 1.8, dialSize, dialSize);

	// set slider positions
	slider1.setBounds(middleSideWidth - (sideWidth / 3), vertSliderTop, 20, vertSliderTop / 2);
	slider2.setBounds(middleSideWidth - (sideWidth / 6), vertSliderTop, 20, vertSliderTop / 2);
	slider3.setBounds(middleSideWidth + (sideWidth / 6) - 20, vertSliderTop, 20, vertSliderTop / 2);
	slider4.setBounds(middleSideWidth + (sideWidth / 3)- 20, vertSliderTop, 20, vertSliderTop / 2);
}
