#include "GeneralVolumeComponent.h"

GeneralVolumeComponent::GeneralVolumeComponent(void) {
	label.setText(RussianText::generalVolume.c_str());
	label.setFontHeight(16);
	label.setJustification(Justification::centred);
	layout.setItemLayout(0, 2000, 200, -0.8);
	layout.setItemLayout(1, 200, 100, -0.2);
	addAndMakeVisible(slider);
	addAndMakeVisible(label);
	resized();
}

void GeneralVolumeComponent::paint(Graphics& g) {
	g.fillAll(Colours::cyan);
}

void GeneralVolumeComponent::resized(void) {
	auto area = getLocalBounds();
	auto labelArea = area.removeFromBottom(50);
	label.setBounds(labelArea);
	label.setBoundingBox(Parallelogram<float>(labelArea.toFloat()));
	slider.setBounds(area);
	
}
