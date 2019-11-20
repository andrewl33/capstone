/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <OpenGL/gl.h>

#define PI 3.14159265f
//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (752, 500);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

	r = Random();
	
    // Fills arrays of blobs
	for (auto i = 0; i < blobCount; ++i)
	{
		blobState.push_back(std::make_pair(std::vector<float>{0.0, 0.0, 0.0, 0.0}, std::vector<float>{0.0, 0.0, 0.0, 0.0}));
		curState.push_back(std::vector<float>{0.0,0.0,0.0,0.0});
	}

	createNextState();
	copyNextToCurState();
	translate(0);

	startTimer(1000 / updatePerSecond);
    
    // openGLContext.setComponentPaintingEnabled(true);
    openGLContext.setRenderer(this);
    openGLContext.setContinuousRepainting(true);
    openGLContext.attachTo(*this);
}

void MainComponent::timerCallback()
{
	if (transitionCounter++ > translateTimeHz + pauseTimeHz) {
		copyNextToCurState();
		createNextState();
		transitionCounter = 0;
	}
	else if (transitionCounter > translateTimeHz) {
		return;
	}
	translate((transitionCounter/(float)translateTimeHz));
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
    openGLContext.detach();
    openGLContext.deactivateCurrentContext();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
//	g.setColour(Colours::red);
//
//	for (int i = 0; i < blobState.size(); i++)
//	{
//		g.fillEllipse(curState[i][0], curState[i][1], curState[i][2], curState[i][3]);
//	}

}

/**
 createNextState creates a next state for a blob to travel to
 In terms of resizing, right now this function will obey resizing rules, however the current circles will not update to
 the correct size
 */
void MainComponent::createNextState()
{
	for (int i = 0; i < blobState.size(); i+=2)
	{
		auto x = r.nextFloat() * difference;
		auto y = r.nextFloat() * height;
		auto dim = (r.nextFloat() * (circleMaxDim - circleMinDim)) + circleMinDim;

		auto& left = blobState[i].second;
		auto& right = blobState[(int64)i + (int64)1].second;

        // set centers of circles
		left[0] = x + dim / 2;
		left[1] = y  - (height / 2);

        right[0] = -x - dim / 2;
		right[1] = y - (height / 2);
	
        // adjust for circle dimensions
        if (getHeight() > getWidth())
        {
            left[2] = dim;
            right[2] = dim;
            left[3] = dim * adjDims;
            right[3] = dim * adjDims;
        }
        else
        {
            left[2] = dim * adjDims;
            right[2] = dim * adjDims;
            left[3] = dim;
            right[3] = dim;
        }
	}	
}

/**
 copyNextToCurState is called when the transition period is over, and before a new state is made, the old state is copied into the old state
 */
void MainComponent::copyNextToCurState()
{
	for (int i = 0; i < blobState.size(); ++i) 
	{
		auto& oldState = blobState[i].first;
		auto& newState = blobState[i].second;

		for (int j = 0; j < oldState.size(); j++)
		{
			oldState[j] = newState[j];
		}
	}
}

/**
 Translate updates curState with information needed for OpenGL to draw each circle,
 based on a progress value, which is 0-1, where 1 is reached nextState
 */
void MainComponent::translate(float progress)
{
	for (int i = 0; i < blobState.size(); i++)
	{
		auto from = blobState[i].first;
		auto to = blobState[i].second;
        
		curState[i][0] = from[0] +  progress * (float)((double)to[0] - from[0]);
		
		curState[i][1] = from[1] +  progress * (float)((double)to[1] - from[1]);
        curState[i][2] = progress * (to[2] - from[2]) + from[2];
        curState[i][3] = progress * (to[3] - from[3]) + from[3];
	}
}

void MainComponent::resized()
{
    // Updates next state to correct circle sizes
    adjDims = getHeight() / (float)getWidth();
    
    if (getHeight() - getWidth() < 2)
    {
        height = 1.f / adjDims - padding;
        width = 1.f - padding;
    }
    else
    {
        width = 1 /adjDims - padding;
        height = adjDims - padding;
        adjDims = 1 / adjDims;
    }
    difference = width - padding / 2;
}

void MainComponent::newOpenGLContextCreated() {}
void MainComponent::openGLContextClosing()
{

};


void MainComponent::renderOpenGL()
{
    // Clears background
    OpenGLHelpers::clear (Colours::black);

//    glEnable (GL_BLEND);
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Draw each blob
    for (int i = 0; i < curState.size(); i++)
    {
        glPushMatrix(); // Saves center point
        glTranslatef(curState[i][0], curState[i][1], 0.f);  // Translate to (xPos, yPos)
        glBegin(GL_TRIANGLE_FAN);
           glColor3f(0.0f, 0.0f, 1.0f);
           glVertex2f(0.0f, 0.0f);       // Center of circle
           GLfloat angle;
        auto x = curState[i][2];
        auto y = curState[i][3];
        // draw circle
        for (int i = 0; i <= circleSegments; i++) {
           angle = i * 2.0f * PI / circleSegments;
           glVertex2f(cos(angle) *  x, sin(angle) *  y);
        }
        glEnd();
        glPopMatrix(); // Returns center point
    }
    glFlush();
}

/**
 handleRetina may be called in the class' constructor if the background has issues
 rendering the image.
 */
void MainComponent::handleRetina()
{
    double scaleFactor; // class member
    scaleFactor = juce::Desktop::getInstance().getDisplays().getMainDisplay().scale; //in class' constructor
    if (scaleFactor > 1) { setTransform(juce::AffineTransform::scale(scaleFactor, scaleFactor));

    } //after the Openglcontext was initialized

}
