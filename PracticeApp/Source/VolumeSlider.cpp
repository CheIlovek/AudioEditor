#include "VolumeSlider.h"

VolumeSlider::VolumeSlider(void) {
	startTimer(50);
	slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	slider.setRange(0, 1);
	slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	slider.setValue(1);
	slider.setLookAndFeel(&laf);
	slider.addListener(this);
	addAndMakeVisible(slider);
}

void VolumeSlider::paint(Graphics& g) {
	int width = getWidth();
	int height = getHeight();
	auto grad = ColourGradient(
		ProjectColours::VolumeSlider::startColour, width / 2, getHeight(),
		ProjectColours::VolumeSlider::endColour, width / 2, 0, true);
	grad.addColour(0.65, ProjectColours::VolumeSlider::middleColour);
	g.setGradientFill(grad);
	float gainMax = slider.getValue();
	float curVolumeValLeft =	std::min(gainMax, leftVol);
	float curVolumeValRight =	std::min(gainMax, rightVol);
	
	Rectangle<int> leftRect	(0, height - height * curVolumeValLeft, width / 2, height);
	Rectangle<int> rightRect(width / 2, height - height * curVolumeValRight, width / 2, height);
	g.fillRect(leftRect);
	g.fillRect(rightRect);
}

void VolumeSlider::resized(void) {
	auto area = getLocalBounds();
	slider.setBounds(area);
}

void VolumeSlider::update(float left, float right) {
	leftVol = left;
	rightVol = right;
}

void VolumeSlider::setSource(TracksAudioSource* source) {
	this->source = source;
}


void VolumeSlider::sliderValueChanged(Slider* slider) {
	if (slider == &this->slider) {
		source->setGain(slider->getValue());
	}
}

void VolumeSlider::timerCallback() {
	DBG(slider.getValue());
	repaint();
}




