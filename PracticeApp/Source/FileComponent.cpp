#include "FileComponent.h"

FileComponent::FileComponent(const File file)
{
	this->file = file;
	fileName.setText(this->file.getFileName());
	fileName.setColour(Colours::white);
	isAddedToggle.setEnabled(false);
	fileName.setBounds(0, 0, 20, 100);
	isAddedToggle.setBounds(100, 0, 20, 20);

	addAndMakeVisible(fileName);
	addAndMakeVisible(isAddedToggle);
}

FileComponent::~FileComponent()
{
}

void FileComponent::paint(Graphics& g)
{
	g.fillAll(juce::Colours::grey);
}

void FileComponent::resized(void)
{
}

String FileComponent::getFileName()
{
	return file.getFileName();
}

File FileComponent::getFile()
{
	return file;
}
