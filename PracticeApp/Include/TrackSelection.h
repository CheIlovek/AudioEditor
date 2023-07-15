#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TracksAudioSource.h"
#include "ProjectColours.h"

class TrackSelection : public juce::Component {

public:
    TrackSelection(const double& zoom);

    void paint(juce::Graphics& g) override;

    void setStartOfSelection(float startPos);
    void setEndOfSelection(float endPos);
    void clearSelection();
    bool isAreaSelected();


    std::pair<float, float> getSelectedArea();
    void setSelectedArea(float start, float end);

private:
    float startSelectionPos = -1;
    float endSelectionPos = 0;
    const float lineWidth = 2.f;
    const double& zoom;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackSelection);
};
#pragma once
