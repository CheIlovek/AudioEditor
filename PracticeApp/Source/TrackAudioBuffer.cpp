#include "TrackAudioBuffer.h"

TrackAudioBuffer::TrackAudioBuffer() {
}

TrackAudioBuffer::TrackAudioBuffer(int numChannelsToAllocate, int numSamplesToAllocate) :
	AudioSampleBuffer(numChannelsToAllocate, numSamplesToAllocate) {
	offset = 0;
}

TrackAudioBuffer::TrackAudioBuffer(const TrackAudioBuffer& other) :
	AudioSampleBuffer(other), offset(other.offset) {}

void TrackAudioBuffer::setOffset(int in) {
	offset = in;
}

int TrackAudioBuffer::getOffset() {
	return offset;
}
