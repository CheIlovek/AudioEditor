#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

/**
@brief AudioSampleBuffer � �������� ���������������
@detailed ��������� AudioSampleBuffer ��� ���������
� ������������� ���������� ��� ������������ �� �������� �������.
*/
class TrackAudioBuffer : public AudioSampleBuffer {
public:
	TrackAudioBuffer();
	TrackAudioBuffer(int numChannelsToAllocate, int numSamplesToAllocate);
	TrackAudioBuffer(const TrackAudioBuffer& other);
	void setOffset(int);
	int getOffset();

	void setStereoBalance(float);
	int getStereoBalance();

	void applyBalanceSettings();
	void restoreBalance();
	bool isChannelMuted(int id);

private:
	int offset;
	float balance = .0f;
	Array<bool> mutedChannels{ false,false };


};
