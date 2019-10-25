/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include "SidebarRotaryLookAndFeel.h"
//#include "SidebarVertSliderLookAndFeel.h"

//==============================================================================
Static_AudioProcessorEditor::Static_AudioProcessorEditor (Static_AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	// Add slider1 params
	// slider1.setSliderStyle(Slider::LinearBarVertical);
	dial1.setSliderStyle(Slider::Rotary);
	// slider1.setRange(0.0, 127.0, 1.0);
	dial1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	dial1.setLookAndFeel(&sidebarRotaryLookAndFeel);
	addAndMakeVisible(&dial1);

	dial2.setSliderStyle(Slider::Rotary);
	dial2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	dial2.setLookAndFeel(&sidebarRotaryLookAndFeel);
	addAndMakeVisible(&dial2);

	dial3.setSliderStyle(Slider::Rotary);
	dial3.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	dial3.setLookAndFeel(&sidebarRotaryLookAndFeel);
	addAndMakeVisible(&dial3);

	dial4.setSliderStyle(Slider::Rotary);
	dial4.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	dial4.setLookAndFeel(&sidebarRotaryLookAndFeel);
	addAndMakeVisible(&dial4);

	dial5.setSliderStyle(Slider::Rotary);
	dial5.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	dial5.setLookAndFeel(&sidebarRotaryLookAndFeel);
	addAndMakeVisible(&dial5);

	dial6.setSliderStyle(Slider::Rotary);
	dial6.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	dial6.setLookAndFeel(&sidebarRotaryLookAndFeel);
	addAndMakeVisible(&dial6);

	slider1.setSliderStyle(Slider::LinearVertical);
	slider1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	slider1.setLookAndFeel(&sidebarVertSliderLookAndFeel);
	addAndMakeVisible(&slider1);

	slider2.setSliderStyle(Slider::LinearVertical);
	slider2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	slider2.setLookAndFeel(&sidebarVertSliderLookAndFeel);
	addAndMakeVisible(&slider2);

	slider3.setSliderStyle(Slider::LinearVertical);
	slider3.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	slider3.setLookAndFeel(&sidebarVertSliderLookAndFeel);
	addAndMakeVisible(&slider3);

	slider4.setSliderStyle(Slider::LinearVertical);
	slider4.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	slider4.setLookAndFeel(&sidebarVertSliderLookAndFeel);
	addAndMakeVisible(&slider4);

	// set main dial position
	mainDial.setSliderStyle(Slider::Rotary);
	mainDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	mainDial.setLookAndFeel(&mainDialLookAndFeel);
	addAndMakeVisible(&mainDial);

	setSize(929, totalHeight);
}

Static_AudioProcessorEditor::~Static_AudioProcessorEditor()
{
	dial1.setLookAndFeel(nullptr);
	dial2.setLookAndFeel(nullptr);
	dial3.setLookAndFeel(nullptr);
	dial4.setLookAndFeel(nullptr);
	dial5.setLookAndFeel(nullptr);
	dial6.setLookAndFeel(nullptr);
	slider1.setLookAndFeel(nullptr);
	slider2.setLookAndFeel(nullptr);
	slider3.setLookAndFeel(nullptr);
	slider4.setLookAndFeel(nullptr);
	mainDial.setLookAndFeel(nullptr);
}

//==============================================================================
void Static_AudioProcessorEditor::paint (Graphics& g)
{
	auto area = getLocalBounds();
	const auto sideWidth = area.getWidth() - imageWidth;
	const auto middleSideWidth = imageWidth + (sideWidth / 2);
	Image background = ImageCache::getFromMemory(BinaryData::blot_jpg, BinaryData::blot_jpgSize);

	g.drawImageAt(background, 0, 0);

	Rectangle<int> toggleArea(Point<int> (imageWidth,0), Point<int>(getLocalBounds().getWidth(), getLocalBounds().getHeight()));
	g.setColour(tanColour);
	g.fillRect(toggleArea);

	// statically set ADSR envelope
	auto widthStart = middleSideWidth - 80;
	auto widthEnd = middleSideWidth + 80;
	auto heightStart = area.getHeight() - 100;
	auto heightEnd = area.getHeight() - 20;
	Rectangle<int> envelopeArea(Point<int>(widthStart, heightStart), Point<int>(widthEnd, heightEnd));
	g.setColour(brownColour);
	g.fillRect(envelopeArea);

	Path adsrPath;
	// Start and end are pulled out a bit
	adsrPath.startNewSubPath(Point<float>(widthStart-5, heightEnd-10));
	adsrPath.lineTo(Point<float>(widthStart, heightEnd - 10)); // Line before attack
	adsrPath.lineTo(Point<float>(widthStart+40, heightStart + 10));	// Attack line
	adsrPath.lineTo(Point<float>(widthStart + 60, heightStart + 40));	// Delay line
	adsrPath.lineTo(Point<float>(widthStart + 140, heightStart + 40));	// Sustain line
	adsrPath.lineTo(Point<float>(widthStart + 160, heightEnd - 10));	// Release line
	adsrPath.lineTo(Point<float>(widthEnd+5, heightEnd - 10)); // Line after release
	// adsrPath.closeSubPath();
	g.setColour(tanColour);
	g.strokePath(adsrPath, PathStrokeType(5.0f, PathStrokeType::JointStyle::curved));
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

	// set main dial position
	mainDial.setBounds(115, 115, 200, 200);
}
