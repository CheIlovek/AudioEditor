#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "VolumeSliderLookAndFeel.h"
#include "VolumeSlider.h"

class GeneralVolumeComponent : public Component {
public:
    GeneralVolumeComponent(void);

    void paint(Graphics&) override;
    void resized(void) override;

private:
    StretchableLayoutManager layout;
    DrawableText label;
    VolumeSlider slider;
};


#pragma once
