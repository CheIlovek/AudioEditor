#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TracksAudioSource.h"
#include "ProjectColours.h"

class TrackSelection : public juce::Component {

public:
    TrackSelection();

    void paint(juce::Graphics& g) override;

    void setStartOfSelection(float startPos);
    void setEndOfSelection(float endPos);
    void clearSelection();


    std::pair<float, float> getSelectedArea();
    void setSelectedArea(float start, float end);

private:
    float startSelectionPos = -1;
    float endSelectionPos = 0;
    const double& curZoom;
    const double& pixelsPerSecond;
    const float lineWidth = 2.f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackSelection);
};
#pragma once
