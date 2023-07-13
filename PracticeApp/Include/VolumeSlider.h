#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TracksAudioSource.h"
#include "VolumeSliderLookAndFeel.h"
#include "ProjectColours.h"

class VolumeSlider : public Component, private Timer {
public:
    VolumeSlider(void);

    void paint(Graphics&) override;
    void resized(void) override;
    void update(float left, float right);
    
    float leftVol = 0.f;
    float rightVol = 0.f;
private:
    void timerCallback() override;
    
    VolumeSliderLookAndFeel laf;
    Slider slider;
};
