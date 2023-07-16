#include "EffectHistoryComponent.h"

EffectHistoryComponent::EffectHistoryComponent(TracksListBox* tracks) : tracks(tracks)
{
	addAndMakeVisible(&namesComboBox);
	addAndMakeVisible(&clearButton);
	addAndMakeVisible(&listBox);

	namesComboBox.onChange = [this] {comboBoxItemChanged(); };
	namesComboBox.setColour(ComboBox::ColourIds::backgroundColourId, ProjectColours::EffectHistory::comboBoxbackgroundColour);
	namesComboBox.setColour(ComboBox::ColourIds::textColourId, ProjectColours::textColour);
	namesComboBox.setColour(ComboBox::ColourIds::outlineColourId, ProjectColours::EffectHistory::comboBoxOutline);
	namesComboBox.setColour(ComboBox::ColourIds::focusedOutlineColourId, ProjectColours::EffectHistory::comboBoxFocusedOutline);
	namesComboBox.setColour(ComboBox::ColourIds::arrowColourId, ProjectColours::textColour);

	namesComboBox.setTextWhenNothingSelected(RussianText::choice.c_str());
	namesComboBox.setTextWhenNoChoicesAvailable(RussianText::empty.c_str());

	clearButton.setButtonText(RussianText::clear.c_str());
	clearButton.onClick = [this] {clearButtonClicked(); };
	clearButton.setColour(TextButton::ColourIds::buttonColourId, ProjectColours::EffectHistory::buttonColour);
	clearButton.setColour(TextButton::ColourIds::buttonOnColourId, ProjectColours::EffectHistory::buttonOnColour);
	clearButton.setColour(TextButton::ColourIds::textColourOnId, ProjectColours::textColour);
	clearButton.setColour(TextButton::ColourIds::textColourOffId, ProjectColours::textColour);
	clearButton.setEnabled(false);
	
	listBox.setRowHeight(20);
	listBox.setColour(ListBox::backgroundColourId, ProjectColours::EffectHistory::listBoxBackground);
	listBox.setColour(ListBox::outlineColourId, ProjectColours::EffectHistory::listBoxOutline);
	listBox.setOutlineThickness(1);
}

EffectHistoryComponent::~EffectHistoryComponent()
{
}

void EffectHistoryComponent::resized(void)
{
	int buttonWidth = 150;
	int margin = 5;
	int topSideHeight = 30;
	int rowHeight = 20;
	clearButton.setBounds(getWidth() - buttonWidth, margin, buttonWidth, topSideHeight);
	namesComboBox.setBounds(margin, margin, getWidth() - buttonWidth - margin * 2, topSideHeight);
	listBox.setBounds(0, topSideHeight + margin * 2, getWidth(), getHeight() - (topSideHeight + margin * 2));
	for (EffectListBoxModel* model : modelList)
	{
		for (int i = 0; i < model->getNumRows(); i++)
		{
			Rectangle<float> boundingBoxRectangle(5, 0, getWidth() - 5, rowHeight);
			model->getDrawableText(i)->setBoundingBox(Parallelogram<float>(boundingBoxRectangle));
		}
	}
}

void EffectHistoryComponent::paint(Graphics& g)
{
	g.fillAll(ProjectColours::EffectHistory::listBoxBackground);

	ColourGradient headerColour(
		ProjectColours::EffectHistory::headerStartColour,
		0, 0,
		ProjectColours::EffectHistory::headerEndColour,
		getWidth(), 40,
		true
	);
	g.setGradientFill(headerColour);
	g.fillRect(0, 0, getWidth(), 40);
}

void EffectHistoryComponent::addNewTrackHistory()
{
	String name = tracks->getTrack(tracks->getSelectedRow())->getTrackName();
	auto newModel = std::make_unique<EffectListBoxModel>(name);
	modelList.add(newModel.release());
	namesComboBox.addItem(name, modelList.size());
}

void EffectHistoryComponent::addNewEffect(String effectName)
{
	int trackId = tracks->getSelectedRow();
	auto track = tracks->getTrack(trackId);
	int pixelsBySecond = 10; //defaultPixelsBySecond = 10 in TracksListBox

	String time1;
	String time2;

	if (track->haveSelection()) {
		auto pos = track->getSelectedAreaInPixels();
		
		std::time_t startTime((double)pos.first / pixelsBySecond);
		std::tm* t1 = gmtime(&startTime);
		time1 = std::to_string(t1->tm_hour) + ':' + std::to_string(t1->tm_min) + ':' + std::to_string(t1->tm_sec);

		std::time_t endTime((double)pos.second / pixelsBySecond);
		std::tm* t2 = gmtime(&endTime);
		time2 = std::to_string(t2->tm_hour) + ':' + std::to_string(t2->tm_min) + ':' + std::to_string(t2->tm_sec);

		modelList[trackId]->addNewElement(effectName + ' ' + time1 + " - " + time2);
	}
	else {
		std::time_t startTime((double)0);
		std::tm* t1 = gmtime(&startTime);
		time1 = std::to_string(t1->tm_hour) + ':' + std::to_string(t1->tm_min) + ':' + std::to_string(t1->tm_sec);

		std::time_t endTime((double)track->getWaveformSize() / pixelsBySecond);
		std::tm* t2 = gmtime(&endTime);
		time2 = std::to_string(t2->tm_hour) + ':' + std::to_string(t2->tm_min) + ':' + std::to_string(t2->tm_sec);

		modelList[trackId]->addNewElement(effectName + ' ' + time1 + " - " + time2 + ' ' + RussianText::all.c_str());
	}

	if (namesComboBox.getSelectedId() == trackId + 1)
	{
		listBox.updateContent();
		listBox.setSize(getWidth(), 150);
		resized();
	}
		
}

void EffectHistoryComponent::comboBoxItemChanged()
{
	int modelId = namesComboBox.getSelectedId() - 1;
	listBox.setModel(modelList[modelId]);
	listBox.updateContent();
	listBox.setSize(getWidth(), 150);
	resized();
}

void EffectHistoryComponent::clearButtonClicked()
{
}
