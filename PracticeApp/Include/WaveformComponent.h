#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackAudioBuffer.h"
#include "ProjectColours.h"

/**
@brief Класс для отображение спектрограммы звука
*/
class WaveformComponent : public juce::Component, private juce::ChangeListener {
public:
    WaveformComponent(int sourceSamplesPerThumbnailSample,
        juce::AudioFormatManager& formatManager,
        juce::AudioThumbnailCache& cache);

    void setSource(TrackAudioBuffer* buffer, double sampleRate);
    void paint(juce::Graphics& g) override;
    void paintIfNoFileLoaded(juce::Graphics& g);
    void paintIfFileLoaded(juce::Graphics& g);
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void clear();

private:
    void thumbnailChanged();
    static int brushCounter;
    Colour colour;

    juce::AudioThumbnail thumbnail;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformComponent)
};

namespace RussianText {
    const std::wstring noFile(L"На дорожке нет аудио!\nЗагрузите файл на дорожку через меню Треки -> Добавить аудио");
}
