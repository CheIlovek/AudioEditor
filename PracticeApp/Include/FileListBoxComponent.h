#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileComponent.h"

class FileComponent;

class FileListBoxComponent : public Component, public ListBoxModel
{
public:
	const Colour colour{ 0xff131313 };

	FileListBoxComponent();
	~FileListBoxComponent();

	int getNumRows() override;
	void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate);
	void listBoxItemClicked(int row, const MouseEvent&) override;
	void backgroundClicked(const MouseEvent&) override;
	void resized(void) override;
	void paint(Graphics& g) override;
	void openFile();
	File getFile(int index);
	File getSelectedFile();
	int getNumOfSelectedRows();

private:
	std::unique_ptr<juce::FileChooser> chooser;
	juce::Array<FileComponent*> fileList;
	ListBox fileListBox;

	DrawableText name;
	DrawableText added;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileListBoxComponent)
};
