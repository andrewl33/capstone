/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Static_AudioProcessorEditor::Static_AudioProcessorEditor (Static_AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (929, 479);

	// Add slider1 params
	slider1.setSliderStyle(Slider::LinearBarVertical);
	slider1.setRange(0.0, 127.0, 1.0);
	slider1.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	slider1.setPopupDisplayEnabled(true, false, this);
	slider1.setValue(1.0);

	addAndMakeVisible(&slider1);
}

Static_AudioProcessorEditor::~Static_AudioProcessorEditor()
{
}

//==============================================================================
void Static_AudioProcessorEditor::paint (Graphics& g)
{
	auto tanColour = Colour((uint8)234, (uint8)213, (uint8)201, (uint8)255);
	auto brownColour = Colour((uint8)94, (uint8)74, (uint8)62, (uint8)255);
	Image background = ImageCache::getFromMemory(BinaryData::blot_jpg, BinaryData::blot_jpgSize);
	
	g.drawImageAt(background, 0, 0);

	Rectangle<int> area(Point<int> (736,0), Point<int>(getLocalBounds().getWidth(), getLocalBounds().getHeight()));
	g.setColour(tanColour);
	g.fillRect(area);
}

void Static_AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	slider1.setBounds(getWidth()-60, 20 , 20, getHeight() - 60);
}
