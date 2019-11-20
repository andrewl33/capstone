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
class MainComponent   : public AudioAppComponent , public Timer, public OpenGLRenderer
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
	void timerCallback() override;
    
    void handleRetina();
    //==============================================================================
    void newOpenGLContextCreated() override;
    void openGLContextClosing() override;
    void renderOpenGL() override;
private:
    //==============================================================================
    OpenGLContext openGLContext;
    // GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
    // GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
    
	Random r;
	int blobCount = 200; // Has to be divisible by 2
	std::vector<std::pair<std::vector<float>, std::vector<float>>> blobState; // now, before<x loc, y loc, size, size> 
	std::vector<std::vector<float>> curState; // x offset, x loc, y loc, size x, size y
    
    // time modifiers
	int translateTimeHz = 180; // hz it takes for blobs to travel from one state to next
	int updatePerSecond = 60;
	int pauseTimeHz = 1 * 60;
	int transitionCounter = 0;
    
    // ball sizes
    float adjDims = 1;
    float padding = .08;
    float width, height;
    float difference;
    float circleMaxDim = .15;
    float circleMinDim = .005;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
