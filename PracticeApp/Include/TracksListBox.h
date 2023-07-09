#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackComponent.h"
#include "TracksAudioSource.h"
#include "PlayPositionComponent.h"
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
    void paint(Graphics&) override;

    void addNewTrack();
    void addNewTrack(juce::File file);
    void setFileOnTrack(int trackId, juce::File file);
    void setFileOnTrack(juce::File file);
    void muteTrack(int trackId);
    void unmuteTrack(int trackId);
    void soloTrack(int trackId);
    void setTrackOffset(int trackId, int offset);

    int getNumOfSelectedRows();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void releaseResources();
    void getNextAudioBlock(const AudioSourceChannelInfo&);
    TracksAudioSource& getAudioSource();

private:
    const double defaultPixelsBySecond = 10;
    int zoomRatio = 1;

    const Colour background{ 0xff242223 };
    PlayPositionComponent playPosition;
    juce::AudioFormatManager formatManager;
    TracksAudioSource audioMixer;
    juce::Array<TrackComponent*> dataList;
    juce::ListBox listBox;
    TrackComponent* mouseSelected = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksListBox)

};


