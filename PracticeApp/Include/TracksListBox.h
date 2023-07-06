#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackComponent.h"
#include "TracksAudioSource.h"
class TracksListBox : public ListBoxModel, public Component {
public:
    TracksListBox(void);
    ~TracksListBox(void) override;

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate);
    void resized(void) override;

    void addNewTrack();
    void addNewTrack(juce::File file);
    void setFileOnTrack(int trackId, juce::File file);
    void setFileOnTrack(juce::File file);


    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void releaseResources();
    void getNextAudioBlock(const AudioSourceChannelInfo&);
    TracksAudioSource& getAudioSource();

private:
    const Colour background{ 0xff242223 };
    juce::AudioFormatManager formatManager;
    TracksAudioSource audioMixer;
    juce::Array<TrackComponent*> dataList;
    juce::ListBox listBox;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksListBox)

};


