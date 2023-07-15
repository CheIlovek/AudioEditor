#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "DummyComponent.h"
#include "WaveformComponent.h"
#include "ProjectColours.h"
#include "TrackSelection.h"
#include "BalanceSliderLookAndFeel.h"

class TracksListBox;

/**
@brief Графическое отображение одной звуквой дорожки
*/
class TrackComponent : public Component, public Slider::Listener {
public:
    TrackComponent(juce::AudioFormatManager&, TracksListBox&, int, const double&);
    ~TrackComponent(void) override;

    void paint(Graphics&) override;
    void resized(void) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;

    /**
    * @brief Устанавливает звуковой источник для отображения
    * @param buffer Новый источник звука
    * @param wavefromSize Изначальный размер спектрограммы(без учёта приближения)
    */
    void setSource(TrackAudioBuffer* buffer, double sampleRate, int wavefromSize);
    /**
    * @brief Удаляет звуковой источник
    */
    void clear();
    /**
    * @brief Обновляет информацию о положении дорожки в общем списке
    * @detailed Метод не влияет на расположение дорожки в списке,
    * а предназначен только для обновления информации при измении расположения.
    */
    void setRow(int newRow);
    /**
    * @brief Изменяет начальный размер спектрограммы
    * @param newSize Новый размер спектрограммы(без учёта приближения)
    */
    void setWaveformSize(int newSize);
    /**
    * @brief Задает отступ для спектрограммы
    * @param newOffset Отступ спектрограммы в пикселях
    */
    void setWaveformOffset(int);
    /**
    * @brief Возвращает на какой строке списка находится дорожка
    */
    int getRow();
    String getTrackName();
    int getWaveformSize();
    bool haveSelection();
    std::pair<float, float> getSelectedAreaInPixels();
    void setAudioFilename(juce::String str);
    void muteButtonClicked();
    void superiorButtonClicked();

    
private:
    void sliderValueChanged(juce::Slider* slider) override;

    enum State {
        selecting,
        dragging,
        none
    };
    
    State curState = State::none;

    BalanceSliderLookAndFeel balanceLaf;
    juce::DrawableText trackName;
    juce::TextButton muteButton;
    juce::TextButton superiorButton;
    juce::Slider balanceSlider;
    DummyComponent volumeSlider; // затычка

    juce::AudioThumbnailCache waveformCache;
    WaveformComponent waveform;
    TrackSelection selection;
    TracksListBox& owner;
    int row;
    int waveformSize = 0;
    int waveformOffset = 0;
    const double& waveformZoom;
    int oldWaveformOffset = 0;
    static int TrackNumber;
    const int audioFilenameHeight = 15;
    juce::String audioFilename;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackComponent);

};

namespace RussianText {
    const std::wstring mute(L"Без звука");
    const std::wstring solo(L"Соло");
    const std::wstring audio(L"Аудио");
}


