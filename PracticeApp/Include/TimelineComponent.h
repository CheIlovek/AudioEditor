#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackAudioBuffer.h"
#include "ProjectColours.h"

/**
@brief Класс для отображение временной шкалы
*/
class TimelineComponent : public juce::Component {
public:
    TimelineComponent(const double& zoom, const double& pixelsPerSecond, const int leftSideSize);
    void paint(juce::Graphics& g) override;

    juce::String getFormattedSting(float valueInSec);
private:
    const double& zoom;
    const double& pixelsPerSecond;
    const int leftSideSize;

    const int maxLines = 20;
    const int lineHeight = 5;
    const int freqOfTimeLables = 5;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TimelineComponent)
};
