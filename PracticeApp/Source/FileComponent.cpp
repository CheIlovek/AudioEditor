#include "FileComponent.h"

FileComponent::FileComponent(const File file)
{
	this->file = file;
	fileName.setText(this->file.getFileName());
	addAndMakeVisible(fileName);
	addAndMakeVisible(isAddedToggle);

	fileName.setColour(Colours::white);
	Font font(16, Font::italic);
	fileName.setFont(font, true);
	//fileName.setFontHeight(20);

	isAddedToggle.setEnabled(false);
	
	resized();
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
	fileName.setBounds(5, 0, getWidth() * 0.8 - 5, getHeight());
	isAddedToggle.setBounds(getWidth() * 0.8, 0, getWidth() * 0.2, getHeight());
}

String FileComponent::getFileName()
{
	return file.getFileName();
}

File FileComponent::getFile()
{
	return file;
}
