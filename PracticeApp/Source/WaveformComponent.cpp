#include "WaveformComponent.h"


WaveformComponent::WaveformComponent(int sourceSamplesPerThumbnailSample,
    juce::AudioFormatManager& formatManager,
    juce::AudioThumbnailCache& cache)
    : thumbnail(sourceSamplesPerThumbnailSample, formatManager, cache) {
    thumbnail.addChangeListener(this);
}

void WaveformComponent::setSource(const juce::AudioSampleBuffer* buffer, double sampleRate) {
    thumbnail.setSource(buffer, sampleRate, 0); // TODO: считать хеш
}

void WaveformComponent::paint(juce::Graphics& g) {
    if (!thumbnail.isFullyLoaded() && thumbnail.getNumChannels() == 0)
        paintIfNoFileLoaded(g);
    else
        paintIfFileLoaded(g);
}

void WaveformComponent::paintIfNoFileLoaded(juce::Graphics& g) {
    g.fillAll(juce::Colours::white);
    g.setColour(juce::Colours::darkgrey);
    g.drawFittedText("No File Loaded", getLocalBounds(), juce::Justification::centred, 1);
}

void WaveformComponent::paintIfFileLoaded(juce::Graphics& g) {
    g.fillAll(juce::Colours::white);

    g.setColour(juce::Colours::red);
    thumbnail.drawChannels(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 1.0f);
}

void WaveformComponent::changeListenerCallback(juce::ChangeBroadcaster* source) {
    if (source == &thumbnail)
        thumbnailChanged();
}

void WaveformComponent::clear() {
    thumbnail.clear();
}


void WaveformComponent::thumbnailChanged() {
    repaint();
}
