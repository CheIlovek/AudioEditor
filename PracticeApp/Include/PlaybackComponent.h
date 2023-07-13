#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TracksAudioSource.h"
#include "PlayButtonLookAndFeel.h"
#include "StopButtonLookAndFeel.h"
#include "VolumeSlider.h"

class PlaybackComponent : public AudioAppComponent, public ChangeListener
{
public:
	PlaybackComponent(TracksAudioSource* audioSource);
	~PlaybackComponent();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void setVolumeGUI(VolumeSlider* slider);

private:
    enum State
    {
        Stopped,
        Starting,
        Playing,
        Pausing,
        Paused,
        Stopping
    };
    
    void changeState(State newState);
    void playButtonClicked();
    void stopButtonClicked();

    PlayButtonLookAndFeel lafPlay;
    StopButtonLookAndFeel lafStop;
    TextButton playButton;
    TextButton stopButton;

    TracksAudioSource* audioSource;
    State state;
    VolumeSlider* slider = nullptr;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaybackComponent)
};