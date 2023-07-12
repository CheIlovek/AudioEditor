#include "ReverbWindowComponent.h"

ReverbWindowComponent::ReverbWindowComponent()
{
	roomSize.setText("Room Size");
	damping.setText("Damping");
	wetLevel.setText("Wet Level");
	dryLevel.setText("Dry Level");
	width.setText("Width");
	freezeMode.setText("Freeze Mode");

	labels.add(&roomSize);
	labels.add(&damping);
	labels.add(&wetLevel);
	labels.add(&dryLevel);
	labels.add(&width);
	labels.add(&freezeMode);

	sliders.add(&roomSizeSlider);
	sliders.add(&dampingSlider);
	sliders.add(&wetLevelSlider);
	sliders.add(&dryLevelSlider);
	sliders.add(&widthSlider);
	sliders.add(&freezeModeSlider);

	applyButton.setButtonText("Apply");
	applyButton.onClick = [this] {applyButtonClicked(); };
	applyButton.setColour(TextButton::buttonColourId, ProjectColours::DialogWindow::buttonColour);
	applyButton.setColour(TextButton::buttonOnColourId, ProjectColours::DialogWindow::buttonOnColour);
	applyButton.setColour(TextButton::textColourOnId, ProjectColours::DialogWindow::buttonTextColour);
	applyButton.setColour(TextButton::textColourOffId, ProjectColours::DialogWindow::buttonTextColour);
	addAndMakeVisible(&applyButton);

	for (int i = 0; i < 6; i++) {
		labels[i]->setColour(ProjectColours::textColour);
		sliders[i]->setSliderStyle(Slider::LinearHorizontal);
		sliders[i]->setTextBoxStyle(Slider::TextBoxRight, true, 100, 20);
		sliders[i]->setColour(Slider::thumbColourId, ProjectColours::DialogWindow::sliderColour);
		sliders[i]->setRange(0.0, 1.0, 0.01);
		addAndMakeVisible(labels[i]);
		addAndMakeVisible(sliders[i]);
	}
	
	roomSizeSlider.setValue(0.5);
	dampingSlider.setValue(0.5);
	wetLevelSlider.setValue(0.33);
	dryLevelSlider.setValue(0.4);
	widthSlider.setValue(1.0);
	freezeModeSlider.setValue(0.0);

	resized();
}

ReverbWindowComponent::~ReverbWindowComponent()
{
}

void ReverbWindowComponent::paint(Graphics& g)
{
	g.fillAll(ProjectColours::DialogWindow::dialogWindowBackground);
}

void ReverbWindowComponent::resized(void)
{
	// 390 x 280
	int textWidth = 100;
	int sliderWidth = 200;
	int rowHeight = 40;
	int margin = 20;

	for (int i = 0; i < 6; i++) {
		labels[i]->setBounds(margin, margin + rowHeight * i, textWidth, rowHeight);
		sliders[i]->setBounds(margin + textWidth, margin + rowHeight * i, sliderWidth, rowHeight);
	}

	applyButton.setBounds(110, 340, 60, 30);
}

void ReverbWindowComponent::applyButtonClicked()
{
	parameters.roomSize = roomSizeSlider.getValue();
	parameters.damping = dampingSlider.getValue();
	parameters.wetLevel = wetLevelSlider.getValue();
	parameters.dryLevel = dryLevelSlider.getValue();
	parameters.width = widthSlider.getValue();
	parameters.freezeMode = freezeModeSlider.getValue();
}

Reverb::Parameters ReverbWindowComponent::getParameters()
{
	return parameters;
}
