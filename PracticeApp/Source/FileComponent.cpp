#include "FileComponent.h"

FileComponent::FileComponent(const File newFile, FileListBoxComponent& newOwner, int newRow) : file(newFile), owner(newOwner), row(newRow)
{
	fileName.setText(this->file.getFileName());
	addAndMakeVisible(fileName);
	addAndMakeVisible(isAddedToggle);

	fileName.setColour(Colours::white);
	//Font font(16, Font::italic);
	//fileName.setFont(font, true);
	//fileName.setBoundsInset(BorderSize<int>(1));
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
	//g.fillAll(juce::Colours::grey);
}

void FileComponent::resized(void)
{
	fileName.setBounds(5, 0, getWidth() * 0.8 - 5, getHeight());
	fileName.setBoundingBox(Parallelogram<float>(Rectangle<float>(5, 0, getWidth() * 0.8 - 5, getHeight())));
	isAddedToggle.setBounds(getWidth() * 0.8, 0, getWidth() * 0.2, getHeight());
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
