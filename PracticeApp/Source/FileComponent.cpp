#include "FileComponent.h"

FileComponent::FileComponent(const File newFile, FileListBoxComponent& newOwner, int newRow) : file(newFile), owner(newOwner), row(newRow)
{
	fileName.setText(this->file.getFileName());
	addAndMakeVisible(fileName);
	addAndMakeVisible(isAddedToggle);

	fileName.setColour(ProjectColours::textColour);
	fileName.setFontHeight(16);

	isAddedToggle.setEnabled(true);
	isAddedToggle.setInterceptsMouseClicks(false, false);
	isAddedToggle.setColour(ToggleButton::tickColourId, ProjectColours::textColour);
	isAddedToggle.setColour(ToggleButton::tickDisabledColourId, ProjectColours::Files::fileRowBackgroundSelected);

	fileName.toBack();
	isAddedToggle.toBack();
	toFront(true);
	
	resized();
}

FileComponent::~FileComponent()
{
}

void FileComponent::paint(Graphics& g)
{
}

void FileComponent::resized(void)
{
	double textProportion = 0.8;
	double toggleProportion = 1 - textProportion;
	int margin = 5;
	fileName.setBounds(margin, 0, getWidth() * textProportion - margin, getHeight());
	fileName.setBoundingBox(Parallelogram<float>(Rectangle<float>(margin, 0, getWidth() * textProportion - margin, getHeight())));
	isAddedToggle.setBounds(getWidth() * textProportion, 0, getWidth() * toggleProportion, getHeight());
}

void FileComponent::mouseDown(const juce::MouseEvent& event)
{
	owner.listBoxItemClicked(row, event);
	isAddedToggle.setColour(ToggleButton::tickDisabledColourId, ProjectColours::Files::fileRowBackgroundSelected);
}

String FileComponent::getFileName()
{
	return file.getFileName();
}

File FileComponent::getFile()
{
	return file;
}

void FileComponent::fileAdded()
{
	isAddedToggle.triggerClick();
}

void FileComponent::deselect()
{
	isAddedToggle.setColour(ToggleButton::tickDisabledColourId, ProjectColours::Files::fileRowBackgroundUnselected);
}
