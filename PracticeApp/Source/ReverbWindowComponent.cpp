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
	// 440 x 320
	int textWidth = 100;
	int sliderWidth = 300;
	int rowHeight = 40;
	int margin = 20;
	Rectangle<float> textLabelsRectangle(margin, margin, textWidth, rowHeight * 6);

	FlexBox labelsBox;
	labelsBox.flexDirection = FlexBox::Direction::column;
	labelsBox.flexWrap = FlexBox::Wrap::wrap;
	labelsBox.alignContent = FlexBox::AlignContent::flexStart;
	labelsBox.justifyContent = FlexBox::JustifyContent::flexStart;

	Array<FlexItem> labelItems;

	for (int i = 0; i < 6; i++) {
		labels[i]->setBoundingBox(Parallelogram<float>(Rectangle<float>(5, 0, textWidth - 5, rowHeight)));
		labelItems.add(FlexItem(textWidth, rowHeight, *labels[i]));
		//labels[i]->setBounds(margin, margin + rowHeight * i, textWidth, rowHeight);
		sliders[i]->setBounds(margin + textWidth, margin + rowHeight * i, sliderWidth, rowHeight);
	}

	labelsBox.items = labelItems;
	labelsBox.performLayout(textLabelsRectangle);

	applyButton.setBounds(190, 270, 60, 30);
	setSize(440, 320);
}

void ReverbWindowComponent::updateParameters()
{
	parameters.roomSize = roomSizeSlider.getValue();
	parameters.damping = dampingSlider.getValue();
	parameters.wetLevel = wetLevelSlider.getValue();
	parameters.dryLevel = dryLevelSlider.getValue();
	parameters.width = widthSlider.getValue();
	parameters.freezeMode = freezeModeSlider.getValue();
}

TextButton* ReverbWindowComponent::getApllyButton()
{
	return &applyButton;
}

Reverb::Parameters ReverbWindowComponent::getParameters()
{
	return parameters;
}
