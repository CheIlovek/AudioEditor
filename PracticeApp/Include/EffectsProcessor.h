#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "TrackAudioBuffer.h"
#include "ReverbWindowComponent.h"

class EffectsProcessor
{
public:
	enum Effects 
	{
		ReverbFilter,
		IirFilter
	};

	EffectsProcessor();
	~EffectsProcessor();

	void makeReverb(TrackAudioBuffer& buffer, double sampleRate);


private:
	Reverb reverb;
	OwnedArray<IIRFilter> iirFilters;
	//TracksAudioSource& owner;

	ReverbWindowComponent reverbWindowComponent;
};