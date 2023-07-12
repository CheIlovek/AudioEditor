#include "VolumeSliderLookAndFeel.h"

VolumeSliderLookAndFeel::VolumeSliderLookAndFeel() {
}

void VolumeSliderLookAndFeel::drawLinearSlider(Graphics& g, int x, int y,
												int width, int height, float sliderPos,
												float minSliderPos, float maxSliderPos,
												const Slider::SliderStyle style, Slider& slider) {



}

void VolumeSliderLookAndFeel::drawLinearSliderBackground(Graphics& g, int x, int y,
														int width, int height, float sliderPos,
														float minSliderPos, float maxSliderPos, 
														const Slider::SliderStyle style, Slider& slider) {

	
}

void VolumeSliderLookAndFeel::drawLinearSliderThumb(Graphics& g, int x, int y,
													int width, int height, float sliderPos,
													float minSliderPos, float maxSliderPos,
													const Slider::SliderStyle, Slider&) {
	g.setColour(Colours::white);
	g.drawHorizontalLine(sliderPos, 0, width);
}

