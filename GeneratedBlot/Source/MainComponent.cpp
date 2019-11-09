/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

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
	// Fill pair array
	for (auto i = 0; i < blobCount; ++i)
	{
		blobState.push_back(std::make_pair(std::vector<float>{0.0, 0.0, 0.0, 0.0}, std::vector<float>{0.0, 0.0, 0.0, 0.0}));
		curState.push_back(std::vector<float>{0.0,0.0,0.0,0.0});
	}

	createNextState();
	copyNextToCurState();
	translate(0);

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
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
	g.setColour(Colours::red);

	for (int i = 0; i < blobState.size(); i++)
	{
		g.fillEllipse(curState[i][0], curState[i][1], curState[i][2], curState[i][3]);
	}

}

void MainComponent::createNextState()
{
	auto padding = 50;
	auto height = getBounds().getHeight() - padding;
	auto width = getBounds().getWidth() - padding;
	auto midpoint = width / 2 + padding / 2;
	auto difference = width - midpoint - padding / 2;
	auto circleMaxDim = 40;
	auto circleMinDim = 5;

	for (int i = 0; i < blobState.size(); i+=2)
	{
		auto x = r.nextFloat() * difference;
		auto y = r.nextFloat() * height + padding / 2;
		auto dim = (r.nextFloat() * (circleMaxDim - circleMinDim)) + circleMinDim;

		auto& left = blobState[i].second;
		auto& right = blobState[(int64)i + (int64)1].second;

		left[0] = midpoint + x - dim / 2;
		left[1] = y - dim / 2;
		left[2] = dim;
		left[3] = dim;

		right[0] = midpoint - x - dim / 2;
		right[1] = y - dim / 2;
		right[2] = dim;
		right[3] = dim;
	}	
}

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

void MainComponent::translate(float elapsed)
{
	float progress = elapsed / translateTime;

	for (int i = 0; i < blobState.size(); i++)
	{
		auto from = blobState[i].first;
		auto to = blobState[i].second;

		// Create a new distance between points
		auto distance = sqrt(pow(2.0, (to[0] - from[0])) + pow(2.0, (to[1] - from[1])));
		auto boxSize = to[2] - from[2];

		curState[i][0] = from[0] + distance * progress * (float)((double)to[0] - from[0]);
		curState[i][1] = from[1] + distance * progress * (float)((double)to[1] - from[1]);
		curState[i][2] = curState[i][3] = progress * boxSize + from[2];
	}
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
