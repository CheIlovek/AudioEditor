#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "VolumeSliderLookAndFeel.h"
#include "ProjectColours.h"

class VolumeSlider : public Component {
public:
    VolumeSlider(void);

    void paint(Graphics&) override;
    void resized(void) override;

    
private:
    VolumeSliderLookAndFeel laf;
    Slider slider;
};
