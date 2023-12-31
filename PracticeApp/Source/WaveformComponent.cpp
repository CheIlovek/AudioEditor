#include "WaveformComponent.h"

int WaveformComponent::brushCounter = 0;

WaveformComponent::WaveformComponent(int sourceSamplesPerThumbnailSample,
    juce::AudioFormatManager& formatManager,
    juce::AudioThumbnailCache& cache)
    : thumbnail(sourceSamplesPerThumbnailSample, formatManager, cache) {
    auto& colours = ProjectColours::Tracks::Waveform::waveformBrushes;
    colour = colours[brushCounter++ % colours.size()];
    thumbnail.addChangeListener(this);
}

void WaveformComponent::setSource(TrackAudioBuffer* buffer, double sampleRate) {
    thumbnail.setSource(buffer, sampleRate, 0); // TODO: ������� ���
}

void WaveformComponent::paint(juce::Graphics& g) {
    if (!thumbnail.isFullyLoaded() || thumbnail.getNumChannels() == 0)
        paintIfNoFileLoaded(g);
    else
        paintIfFileLoaded(g);
}

void WaveformComponent::paintIfNoFileLoaded(juce::Graphics& g) {
    g.fillAll(ProjectColours::Tracks::Waveform::noLoadFileBackground);
    g.setColour(ProjectColours::Tracks::Waveform::noLoadFileText);
    g.drawFittedText(RussianText::noFile.c_str(), getLocalBounds(), juce::Justification::centred, 2);
}

void WaveformComponent::paintIfFileLoaded(juce::Graphics& g) {
    g.fillAll(ProjectColours::Tracks::Waveform::loadFileBackground);
    g.setColour(colour);
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
