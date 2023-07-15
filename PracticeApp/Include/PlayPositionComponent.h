#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TracksAudioSource.h"
#include "ProjectColours.h"

class PlayPositionComponent : public juce::Component, private juce::Timer {

public:
    PlayPositionComponent(TracksAudioSource* transportSourceToUse, const double&, const double&);

    void paint(juce::Graphics& g) override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;
    double getPositionInPixels();

private:
    const double& curZoom;
    const double& pixelsPerSecond;
    double curPos = 0;
    void timerCallback() override;

    TracksAudioSource* transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayPositionComponent);
};
