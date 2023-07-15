#include "PlaybackComponent.h"

PlaybackComponent::PlaybackComponent(TracksAudioSource* audioSource) :
    state(Stopped),
    audioSource(audioSource),
    timer(audioSource) 
{
    addAndMakeVisible(&playButton);
    addAndMakeVisible(&stopButton);
    addAndMakeVisible(timer);

    playButton.setLookAndFeel(&lafPlay);
    stopButton.setLookAndFeel(&lafStop);
    playButton.setToggleable(true);
    stopButton.setToggleable(true);

    playButton.addShortcut(KeyPress(KeyPress::spaceKey));

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
    if (slider != nullptr && bufferToFill.numSamples > 0) {
        float left =    bufferToFill.buffer->getMagnitude(0, 0, bufferToFill.numSamples);
        float right =   bufferToFill.buffer->getMagnitude(1, 0, bufferToFill.numSamples);
        slider->update(left, right);
    }
    
}

void PlaybackComponent::releaseResources()
{
	audioSource->releaseResources();
}

void PlaybackComponent::resized()
{
    int height = getHeight();

    juce::FlexBox flexBoxControls;
    flexBoxControls.flexDirection = juce::FlexBox::Direction::row;
    flexBoxControls.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexBoxControls.alignContent = juce::FlexBox::AlignContent::flexStart;
    flexBoxControls.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;

    juce::FlexItem playButtonItem(height, height, playButton);
    juce::FlexItem stopButtonItem(height, height, stopButton);

    flexBoxControls.items = { playButtonItem, stopButtonItem};

    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::row;
    flexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexBox.alignContent = juce::FlexBox::AlignContent::flexStart;
    flexBox.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;

    juce::FlexItem timerItem(300, height, timer);
    
    timerItem.margin = FlexItem::Margin::Margin(0, 200, 0, 10);
    juce::FlexItem flexBoxControlsItem(100, height, flexBoxControls);
    flexBoxControlsItem.margin = FlexItem::Margin::Margin(0, 10, 0, 10);

    flexBox.items = { flexBoxControlsItem, timerItem };

    flexBox.performLayout(getLocalBounds());
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

void PlaybackComponent::setVolumeGUI(VolumeSlider* slider) {
    this->slider = slider;
}

void PlaybackComponent::changeState(State newState)
{
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
        case Stopped:
            stopButton.setEnabled(false);
            audioSource->setPosition(0.0);
            break;

        case Starting:
            DBG("Staart");
            audioSource->start();
            break;

        case Playing:
            DBG("Plaaying");
            stopButton.setEnabled(true);
            break;

        case Pausing:
            audioSource->stop();
            break;

        case Paused:

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
        playButton.setToggleState(true, juce::dontSendNotification);
        changeState(Starting);
    }
        
    else if (state == Playing) {
        playButton.setToggleState(false, juce::dontSendNotification);
        changeState(Pausing);
    }

    
}

void PlaybackComponent::stopButtonClicked()
{
    if (state == Paused)
        changeState(Stopped);
    else
        changeState(Stopping);
    playButton.setToggleState(false, juce::dontSendNotification);
}
