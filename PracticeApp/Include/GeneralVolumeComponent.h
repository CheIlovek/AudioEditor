#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "VolumeSliderLookAndFeel.h"
#include "VolumeSlider.h"

class GeneralVolumeComponent : public Component {
public:
    GeneralVolumeComponent(void);

    void paint(Graphics&) override;
    void resized(void) override;
    VolumeSlider& getSlider();

private:
    StretchableLayoutManager layout;
    DrawableText label;
    VolumeSlider slider;
};

namespace RussianText {
    const std::wstring generalVolume(L"Общая\nгромкость");
}


#pragma once
