/*
  ==============================================================================

    SynthSound.h
    Created: 17 Oct 2019 6:07:08pm
    Author:  Andre

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"



class SynthSound : public SynthesiserSound
{

public:
	bool appliesToNote(int midiNoteNumber) override
	{
		return true;
	}

	bool appliesToChannel(int midiNoteNumber) override
	{
		return true;
	}
};