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

	void makeReverb(std::function<void()> updateBuffer, TrackAudioBuffer& buffer, double sampleRate, int startSamp = 0, int len = -1);


private:
	Reverb reverb;
	OwnedArray<IIRFilter> iirFilters;
	//TracksAudioSource& owner;

	ReverbWindowComponent reverbWindowComponent;
};