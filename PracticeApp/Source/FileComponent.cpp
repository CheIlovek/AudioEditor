#include "FileComponent.h"

FileComponent::FileComponent(const File newFile, FileListBoxComponent& newOwner, int newRow) : file(newFile), owner(newOwner), row(newRow)
{
	fileName.setText(this->file.getFileName());
	addAndMakeVisible(fileName);
	addAndMakeVisible(isAddedToggle);

	fileName.setColour(ProjectColours::textColour);

	fileName.setFontHeight(16);

	isAddedToggle.setEnabled(false);

	isAddedToggle.setInterceptsMouseClicks(false, false);

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
	double textProportion = 0.7;
	double toggleProportion = 1 - textProportion;
	int margin = 5;
	fileName.setBounds(margin, 0, getWidth() * textProportion - margin, getHeight());
	fileName.setBoundingBox(Parallelogram<float>(Rectangle<float>(margin, 0, getWidth() * textProportion - margin, getHeight())));
	isAddedToggle.setBounds(getWidth() * textProportion, 0, getWidth() * toggleProportion, getHeight());
}

void FileComponent::mouseDown(const juce::MouseEvent& event)
{
	owner.listBoxItemClicked(row, event);
}

String FileComponent::getFileName()
{
	return file.getFileName();
}

File FileComponent::getFile()
{
	return file;
}
