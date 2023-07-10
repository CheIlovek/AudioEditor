#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

/**
@brief AudioSampleBuffer с отступом воспроизведения
@detailed Реализует AudioSampleBuffer без изменений
и дополнительно запоминает своё расположение на звуковой дорожке.
*/
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
