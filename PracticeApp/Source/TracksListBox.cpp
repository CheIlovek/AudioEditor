#include "TracksListBox.h"

TracksListBox::TracksListBox(void) : listBox("ListBox", this) {
	listBox.setColour(juce::ListBox::outlineColourId, juce::Colours::grey);
	listBox.setOutlineThickness(1);
	listBox.setMultipleSelectionEnabled(true);
	
	dataList.push_back(new TrackComponent());
	dataList.push_back(new TrackComponent());
	dataList.push_back(new TrackComponent());
	dataList.push_back(new TrackComponent());
	addAndMakeVisible(listBox);
	listBox.setRowHeight(250);
	resized();
}

TracksListBox::~TracksListBox(void) {
}

int TracksListBox::getNumRows() {
	return dataList.size();
}

void TracksListBox::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) {
	if (rowIsSelected) {
		g.fillAll(juce::Colours::lightblue);
	}
	else {
		g.fillAll(juce::Colours::darkblue);
	}
}

Component* TracksListBox::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate) {
	// Иногда выходит за границы, но почему...
	if (rowNumber < 0 || rowNumber >= dataList.size()) {
		return nullptr;
	}
	return dataList[rowNumber];
}

void TracksListBox::resized(void) {
	listBox.setBounds(getLocalBounds());
}
