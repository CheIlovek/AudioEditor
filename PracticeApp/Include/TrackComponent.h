#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "DummyComponent.h"
#include "WaveformComponent.h"
//#include "TracksListBox.h"
class TracksListBox;

class TrackComponent : public Component {
public:
    TrackComponent(juce::AudioFormatManager&, TracksListBox&, int);
    ~TrackComponent(void) override;

    void paint(Graphics&) override;
    void resized(void) override;
    void setSource(TrackAudioBuffer* buffer, double sampleRate, int wavefromSize);
    void clear();
    void mouseDown(const juce::MouseEvent& event) override;
    void setRow(int newRow);
    void setWaveformSize(int);
    void setWaveformOffset(int);
    int getRow();

private:

    const Colour textColour{ 0xffffffff };
    const Colour buttonColour{ 0xff363636 };
    const Colour sliderColour{ 0xff23c1fe };
    
    juce::DrawableText trackName;
    juce::TextButton muteButton;
    juce::TextButton superiorButton;
    juce::Slider balanceSlider;
    DummyComponent volumeSlider; // затычка

    juce::AudioThumbnailCache waveformCache;
    WaveformComponent waveform;
    TracksListBox& owner;
    int row;
    int waveformSize = 0;
    int waveformOffset = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackComponent);
};


