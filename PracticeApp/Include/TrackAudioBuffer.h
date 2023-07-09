#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class TrackAudioBuffer : public AudioSampleBuffer {
public:
	TrackAudioBuffer();
	TrackAudioBuffer(int numChannelsToAllocate, int numSamplesToAllocate);
	TrackAudioBuffer(const TrackAudioBuffer& other);
	void setOffset(int);
	int getOffset();

private:
	int offset;


};
