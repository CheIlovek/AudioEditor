#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "DummyComponent.h"
#include "WaveformComponent.h"
class TrackComponent : public Component {
public:
    TrackComponent(juce::AudioFormatManager&);
    ~TrackComponent(void) override;

    void paint(Graphics&) override;
    void resized(void) override;
    void setSource(juce::AudioSampleBuffer* buffer, double sampleRate);
    void clear();

private:

    juce::DrawableText trackName;
    juce::TextButton muteButton;
    juce::TextButton superiorButton;
    juce::Slider balanceSlider;
    DummyComponent volumeSlider; // затычка

    juce::AudioThumbnailCache waveformCache;
    WaveformComponent waveform;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackComponent);
};


