#include "ReverbWindowComponent.h"

ReverbWindowComponent::ReverbWindowComponent()
{
	roomSize.setText(RussianText::roomSize.c_str());
	damping.setText(RussianText::damping.c_str());
	wetLevel.setText(RussianText::wetLevel.c_str());
	dryLevel.setText(RussianText::dryLevel.c_str());
	width.setText(RussianText::width.c_str());
	freezeMode.setText(RussianText::freezeMode.c_str());

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

	applyButton.setButtonText(RussianText::apply.c_str());
	applyButton.setColour(TextButton::buttonColourId, ProjectColours::ReverbWindow::buttonColour);
	applyButton.setColour(TextButton::textColourOffId, ProjectColours::ReverbWindow::buttonTextColour);
	addAndMakeVisible(&applyButton);

	for (int i = 0; i < 6; i++) {
		labels[i]->setColour(ProjectColours::textColour);
		sliders[i]->setSliderStyle(Slider::LinearHorizontal);
		sliders[i]->setTextBoxStyle(Slider::TextBoxRight, true, 100, 20);
		sliders[i]->setColour(Slider::thumbColourId, ProjectColours::ReverbWindow::sliderColour);
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
	if(applyButton.isDown())
		applyButton.setColour(TextButton::buttonColourId, ProjectColours::ReverbWindow::buttonOnColour);
	else
		applyButton.setColour(TextButton::buttonColourId, ProjectColours::ReverbWindow::buttonColour);
	g.fillAll(ProjectColours::ReverbWindow::dialogWindowBackground);
}

void ReverbWindowComponent::resized(void)
{
	// 440 x 320
	int textWidth = 150;
	int sliderWidth = 300;
	int rowHeight = 40;
	int margin = 20;
	int buttonWidth = 100;
	int buttonHeight = 30;
	int allWidth = 2 * margin + textWidth + sliderWidth;
	int allHeight = 3 * margin + 6 * rowHeight + buttonHeight;
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

	applyButton.setBounds(allWidth / 2 - buttonWidth / 2, 2 * margin + rowHeight * 6, buttonWidth, buttonHeight);
	setSize(allWidth, allHeight);
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
