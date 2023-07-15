#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackComponent.h"
#include "TracksAudioSource.h"
#include "PlayPositionComponent.h"
#include "ProjectColours.h"
#include "TimelineComponent.h"

/**
@brief ����� ��� ������ �� ��������� ���������
@detailed ����� �������� ��� ����������� ������������� �������,
��� � �� ����������� ����������
*/
class TracksListBox : public ListBoxModel, public Component {
public:
    TracksListBox(void);
    ~TracksListBox(void) override;

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate);
    void resized(void) override;
    void listBoxItemClicked(int row, const MouseEvent&) override;
    void backgroundClicked(const MouseEvent&) override;
    void mouseDown(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;
    void mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) override;
    void paint(Graphics&) override;


    /*
    * @brief ��������� ������ ������� � ����� ������
    */
    void addNewTrack();
    /*
    * @brief ��������� ������� � ����� ������ � �������� ������
    * @param file �������� ���� ��� �������
    */
    void addNewTrack(juce::File file);
    /*
    * @brief ����� �������� ���� ��� �������� �������
    * @param trackId ����� �������
    * @param file �������� ���� ��� �������
    */
    void setFileOnTrack(int trackId, juce::File file);
    /*
    * @brief ����� �������� ���� ��� ���������� �������
    * @detailed ���� �������� ������� �� �������� - ������ �� ����������
    * @param file �������� ���� ��� �������
    */
    void setFileOnTrack(juce::File file);
    /*
    * @brief ��������� ����������� ���� � �������� �������
    * @param trackId ����� �������
    */
    void muteTrack(int trackId);
    /*
    * @brief ��������� ����������� ���� � �������� �������
    * @param trackId ����� �������
    */
    void unmuteTrack(int trackId);
    /*
    * @brief ������������� ������������ ����� ������ � ����� �������
    * @detailed ��� ���������� ����-������ �������� -1
    * @param trackId ����� �������
    */
    void soloTrack(int trackId);
    /*
    * @brief ������ ������ ��������� ����� �� �������� �������
    * @detailed �� �������� ����������� ����������� �������
    * @param trackId ����� �������
    * @param offsetInPixels ������ � ��������
    */
    void setTrackOffset(int trackId, int offsetInPixels);

    bool applyReverbOnTrack(std::function<void()> activateEffectHistory);
    void setStereoBalanceOnTrack(int trackId, float newBalance);

    int getNumOfSelectedRows();
    int getSelectedRow();
    TrackComponent* getTrack(int trackId);


    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void releaseResources();
    void getNextAudioBlock(const AudioSourceChannelInfo&);
    TracksAudioSource& getAudioSource();

private:
    const double defaultPixelsBySecond = 10;
    const double scrollStep = 1;
    double zoomRatio = 1;

    const double zoomMinValue = 0.01;
    const double zoomMaxValue = 13;

    PlayPositionComponent playPosition;
    TimelineComponent timeline;
    juce::AudioFormatManager formatManager;
    TracksAudioSource audioMixer;
    juce::Array<TrackComponent*> dataList;
    juce::ListBox listBox;
    TrackComponent* mouseSelected = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksListBox)

};


