#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "DummyComponent.h"
class TrackComponent : public Component {
public:
    TrackComponent(void);
    ~TrackComponent(void) override;

    void paint(Graphics&) override;
    void resized(void) override;


private:
    juce::DrawableText trackName;
    juce::TextButton muteButton;
    juce::TextButton superiorButton;
    juce::Slider balanceSlider;
    DummyComponent waveform; // затычка
    DummyComponent volumeSlider; // затычка
};


