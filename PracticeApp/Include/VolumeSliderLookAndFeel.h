#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ProjectColours.h"

class VolumeSliderLookAndFeel : public LookAndFeel_V2 {
public:
	VolumeSliderLookAndFeel();

	void drawLinearSlider(Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider&) override;

	void drawLinearSliderBackground(Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider&) override;

	void drawLinearSliderThumb(Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider&) override;

};