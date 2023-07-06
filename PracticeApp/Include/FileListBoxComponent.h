#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileComponent.h"

class FileListBoxComponent : public Component, public ListBoxModel
{
public:
	FileListBoxComponent();
	~FileListBoxComponent();

	int getNumRows() override;
	void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate);
	void resized(void) override;
	void openFile();
	File getFile(int index);
	File getSelectedFile();

private:
	std::unique_ptr<juce::FileChooser> chooser;

	std::vector<FileComponent*> fileList;

	ListBox fileListBox;
};
