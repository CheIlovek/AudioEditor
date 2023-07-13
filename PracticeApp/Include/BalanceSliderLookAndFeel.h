#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ProjectColours.h"

class BalanceSliderLookAndFeel : public LookAndFeel_V2 {
public:
	void drawRotarySlider(Graphics& g, int x, int y, 
						int width, int height, float sliderPosProportional,
						float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
};