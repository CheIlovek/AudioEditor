#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TracksAudioSource.h"
#include "ProjectColours.h"

class PlayTimerComponent : public juce::Component, private juce::Timer {

public:
    PlayTimerComponent(TracksAudioSource* transportSourceToUse);

    void paint(juce::Graphics& g) override;

private:
    void timerCallback() override;
    juce::String getTime();

    TracksAudioSource* transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayTimerComponent);
};
