#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "DummyComponent.h"
#include "WaveformComponent.h"
#include "ProjectColours.h"

class TracksListBox;

/**
@brief ����������� ����������� ����� ������� �������
*/
class TrackComponent : public Component {
public:
    TrackComponent(juce::AudioFormatManager&, TracksListBox&, int, const double&);
    ~TrackComponent(void) override;

    void paint(Graphics&) override;
    void resized(void) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;

    /**
    * @brief ������������� �������� �������� ��� �����������
    * @param buffer ����� �������� �����
    * @param wavefromSize ����������� ������ �������������(��� ����� �����������)
    */
    void setSource(TrackAudioBuffer* buffer, double sampleRate, int wavefromSize);
    /**
    * @brief ������� �������� ��������
    */
    void clear();
    /**
    * @brief ��������� ���������� � ��������� ������� � ����� ������
    * @detailed ����� �� ������ �� ������������ ������� � ������,
    * � ������������ ������ ��� ���������� ���������� ��� ������� ������������.
    */
    void setRow(int newRow);
    /**
    * @brief �������� ��������� ������ �������������
    * @param newSize ����� ������ �������������(��� ����� �����������)
    */
    void setWaveformSize(int newSize);
    /**
    * @brief ������ ������ ��� �������������
    * @param newOffset ������ ������������� � ��������
    */
    void setWaveformOffset(int);
    /**
    * @brief ���������� �� ����� ������ ������ ��������� �������
    */
    int getRow();
    

private:
    
    juce::DrawableText trackName;
    juce::TextButton muteButton;
    juce::TextButton superiorButton;
    juce::Slider balanceSlider;
    DummyComponent volumeSlider; // �������

    juce::AudioThumbnailCache waveformCache;
    WaveformComponent waveform;
    TracksListBox& owner;
    int row;
    int waveformSize = 0;
    int waveformOffset = 0;
    const double& waveformZoom;
    int oldWaveformOffset = 0;
    static int TrackNumber;

    bool isDraggingWaveform = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackComponent);
};


