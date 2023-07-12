#include "VolumeSlider.h"

VolumeSlider::VolumeSlider(void) {
	slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	slider.setValue(5);
	slider.setLookAndFeel(&laf);
}

void VolumeSlider::paint(Graphics& g) {
	int width = getWidth();
	int height = getHeight();
	auto grad = ColourGradient(
		ProjectColours::VolumeSlider::startColour, width / 2, getHeight(),
		ProjectColours::VolumeSlider::endColour, width / 2, 0, true);
	grad.addColour(0.65, ProjectColours::VolumeSlider::middleColour);
	g.setGradientFill(grad);
	Random rand;
	float curVolumeValLeft = rand.nextFloat();
	float curVolumeValRight = rand.nextFloat();
	Rectangle<int> leftRect	(0, height * curVolumeValLeft, width / 2, height);
	Rectangle<int> rightRect(width / 2, height * curVolumeValRight, width / 2, height);
	g.fillRect(leftRect);
	g.fillRect(rightRect);
}

void VolumeSlider::resized(void) {
	auto area = getLocalBounds();
	slider.setBounds(area);
}
