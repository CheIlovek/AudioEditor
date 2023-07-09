#include "TrackAudioBuffer.h"

TrackAudioBuffer::TrackAudioBuffer() {
}

TrackAudioBuffer::TrackAudioBuffer(int numChannelsToAllocate, int numSamplesToAllocate) :
	AudioSampleBuffer(numChannelsToAllocate, numSamplesToAllocate) {}

void TrackAudioBuffer::setOffset(int in) {
	offset = in;
}

int TrackAudioBuffer::getOffset() {
	return offset;
}
