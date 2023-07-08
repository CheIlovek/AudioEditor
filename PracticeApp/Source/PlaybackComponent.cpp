#include "PlaybackComponent.h"

PlaybackComponent::PlaybackComponent(TracksAudioSource* audioSource) : state(Stopped), audioSource(audioSource)
{
    addAndMakeVisible(&playButton);
    addAndMakeVisible(&stopButton);
    
    playButton.setButtonText("Play");
    stopButton.setButtonText("Stop");

    playButton.onClick = [this] { playButtonClicked(); };
    stopButton.onClick = [this] { stopButtonClicked(); };

    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);

    playButton.setEnabled(true);
    stopButton.setEnabled(false);

    audioSource->addChangeListener(this);

    setAudioChannels(2, 2);
}

PlaybackComponent::~PlaybackComponent()
{
	shutdownAudio();
}

void PlaybackComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	audioSource->prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlaybackComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	audioSource->getNextAudioBlock(bufferToFill);
}

void PlaybackComponent::releaseResources()
{
	audioSource->releaseResources();
}

void PlaybackComponent::resized()
{
    playButton.setBounds(0, 0, 100, getHeight());
    stopButton.setBounds(100, 0, 100, getHeight());
}

void PlaybackComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == audioSource)
    {
        if (audioSource->isPlaying())
        {
            DBG("Playing");
            changeState(Playing);
        }
        else if ((state == Stopping) || (state == Playing))
            changeState(Stopped);
        else if (state == Pausing)
            changeState(Paused);
    }
}

void PlaybackComponent::changeState(State newState)
{
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
        case Stopped:
            playButton.setButtonText("Play");
            stopButton.setButtonText("Stop");
            stopButton.setEnabled(false);
            audioSource->setPosition(0.0);
            break;

        case Starting:
            DBG("Staart");
            audioSource->start();
            break;

        case Playing:
            DBG("Plaaying");
            playButton.setButtonText("Pause");
            stopButton.setButtonText("Stop");
            stopButton.setEnabled(true);
            break;

        case Pausing:
            audioSource->stop();
            break;

        case Paused:
            playButton.setButtonText("Resume");
            stopButton.setButtonText("Return to Zero");
            break;

        case Stopping:
            audioSource->stop();
            break;
        }
    }
}

void PlaybackComponent::playButtonClicked()
{
    if (audioSource->getLengthInSeconds() == 0)
    {
        if (state != Stopped)
        {
            if (state == Paused)
                changeState(Stopped);
            else
                changeState(Stopping);
        }
        else
            return;
    }
    else if ((state == Stopped) || (state == Paused))
    {
        DBG("Start");
        changeState(Starting);
    }
        
    else if (state == Playing)
        changeState(Pausing);

    
}

void PlaybackComponent::stopButtonClicked()
{
    if (state == Paused)
        changeState(Stopped);
    else
        changeState(Stopping);
}
