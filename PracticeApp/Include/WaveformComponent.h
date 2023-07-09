#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackAudioBuffer.h"

class WaveformComponent : public juce::Component, private juce::ChangeListener {
public:
    WaveformComponent(int sourceSamplesPerThumbnailSample,
        juce::AudioFormatManager& formatManager,
        juce::AudioThumbnailCache& cache);

    void setSource(const TrackAudioBuffer* buffer, double sampleRate);
    void paint(juce::Graphics& g) override;
    void paintIfNoFileLoaded(juce::Graphics& g);
    void paintIfFileLoaded(juce::Graphics& g);
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void clear();

private:
    void thumbnailChanged();

    juce::AudioThumbnail thumbnail;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformComponent)
};
