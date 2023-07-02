#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackComponent.h"
class MainAudioComponent : public Component {
public:
    MainAudioComponent(void);
    ~MainAudioComponent(void) override;

    void paint(Graphics&) override;
    void resized(void) override;
    //void addTrack();
    //void removeTrack();
    

private:
    juce::ListBox tracks;
    TrackComponent dummy;
};


