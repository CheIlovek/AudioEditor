#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TracksAudioSource.h"

class PlayPositionComponent : public juce::Component, private juce::Timer {

public:
    PlayPositionComponent(TracksAudioSource* transportSourceToUse,int&, const double&);

    void paint(juce::Graphics& g) override;

    void mouseDown(const juce::MouseEvent& event) override;

private:
    int& curZoom;
    const double& pixelsPerSecond;
    void timerCallback() override;

    TracksAudioSource* transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayPositionComponent);
};
