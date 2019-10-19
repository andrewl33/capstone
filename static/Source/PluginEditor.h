/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

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
	Slider slider1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Static_AudioProcessorEditor)
};
