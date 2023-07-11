#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//#include "Headers.h"
#include "TrackAudioBuffer.h"
//class TracksAudioSource;

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
};