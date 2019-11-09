/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

	void createNextState();
	void copyNextToCurState();
	void translate(float elapsed);
private:
    //==============================================================================
    // Your private member variables go here...
	Random r;
	int blobCount = 50; // Has to be divisible by 2
	std::vector<std::pair<std::vector<float>, std::vector<float>>> blobState; // now, before<x loc, y loc, size, size> 
	std::vector<std::vector<float>> curState; // x offset, x loc, y loc, size, size
	float translateTime = 4; // seconds it takes for blobs to travel from one state to next

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
