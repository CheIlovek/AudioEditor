#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TracksAudioSource.h"
#include "VolumeSliderLookAndFeel.h"
#include "ProjectColours.h"

class VolumeSlider : public Component, private Timer, public Slider::Listener {
public:
    VolumeSlider(void);

    void paint(Graphics&) override;
    void resized(void) override;
    void update(float left, float right);
    void setSource(TracksAudioSource* source);
    
    float leftVol = 0.f;
    float rightVol = 0.f;

    void sliderValueChanged(Slider* slider) override;

private:
    void timerCallback() override;
    
    TracksAudioSource* source;
    VolumeSliderLookAndFeel laf;
    Slider slider;
};
