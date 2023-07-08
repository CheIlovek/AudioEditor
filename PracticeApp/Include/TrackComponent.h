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
    void setSource(juce::AudioSampleBuffer* buffer, double sampleRate);
    void clear();
    void mouseDown(const juce::MouseEvent& event) override;
    void setRow(int newRow);
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackComponent);
};


