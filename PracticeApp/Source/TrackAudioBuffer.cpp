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

void TrackAudioBuffer::setStereoBalance(float in) {
	if (in > -1 && in < 1)
		balance = in;
	mutedChannels.set(1, in == -1);
	mutedChannels.set(0, in == 1);
}

int TrackAudioBuffer::getStereoBalance() {
	return balance;
}

void TrackAudioBuffer::applyBalanceSettings() {
	if (getNumChannels() == 2) {
		DBG("LEFT APPLY : " << 1.f - balance);
		DBG("RIGHT APPLY : " << 1.f + balance);
		applyGain(0, 0, getNumSamples(), 1.f - balance);
		applyGain(1, 0, getNumSamples(), 1.f + balance);
	}
}

void TrackAudioBuffer::restoreBalance() {
	if (getNumChannels() == 2) {
		DBG("LEFT RESTORE : " << 1.f / (1.f - balance));
		DBG("RIGHT RESTORE : " << 1.f / (1.f + balance));
		applyGain(0, 0, getNumSamples(), 1.f / (1.f - balance));
		applyGain(1, 0, getNumSamples(), 1.f / (1.f + balance));
	}
}

bool TrackAudioBuffer::isChannelMuted(int id) {
	if (id < 2 && id >= 0)
		return mutedChannels.getUnchecked(id);
	return true;
}
