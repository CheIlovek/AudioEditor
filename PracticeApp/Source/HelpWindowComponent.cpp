#include "HelpWindowComponent.h"

HelpWindowComponent::HelpWindowComponent()
{
	addAndMakeVisible(&sections);
	addAndMakeVisible(&label);

	sections.onChange = [this] {comboBoxItemChanged(); };
	sections.setColour(ComboBox::backgroundColourId, ProjectColours::HelpWindow::comboBoxbackgroundColour);
	sections.setColour(ComboBox::ColourIds::textColourId, ProjectColours::textColour);
	sections.setColour(ComboBox::ColourIds::outlineColourId, ProjectColours::HelpWindow::comboBoxOutline);
	sections.setColour(ComboBox::ColourIds::focusedOutlineColourId, ProjectColours::HelpWindow::comboBoxFocusedOutline);
	sections.setColour(ComboBox::ColourIds::arrowColourId, ProjectColours::textColour);

	for (int i = 0; i < RussianText::sectionNames.size(); i++)
		sections.addItem(RussianText::sectionNames[i].c_str(), i + 1);

	sections.setSelectedId(1, NotificationType::dontSendNotification);

	label.setColour(Label::backgroundColourId, ProjectColours::HelpWindow::backgroundColour);
	label.setColour(Label::textColourId, ProjectColours::textColour);
	label.setFont(Font(16));
	comboBoxItemChanged();

	resized();
}

HelpWindowComponent::~HelpWindowComponent()
{
}

void HelpWindowComponent::resized(void)
{
	int height = 500;
	int width = 600;
	int margin = 20;
	int comboBoxWidth = 200;
	int comboBoxHeight = 30;

	setSize(width, height);
	sections.setBounds(width / 2 - comboBoxWidth / 2, margin, comboBoxWidth, comboBoxHeight);
	label.setBounds(margin, 2 * margin + comboBoxHeight, width - 2 * margin, height - (3 * margin + comboBoxHeight));
}

void HelpWindowComponent::paint(Graphics& g)
{
	g.fillAll(ProjectColours::HelpWindow::backgroundColour);
}

void HelpWindowComponent::comboBoxItemChanged()
{
	int index = sections.getSelectedId() - 1;
	String text;

	for (std::wstring str : RussianText::text[index])
	{
		text += str.c_str();
		text += "\n";
	}

	label.setText(text, NotificationType::dontSendNotification);
}
