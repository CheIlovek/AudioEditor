#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileListBoxComponent.h"
#include "ProjectColours.h"
class FileListBoxComponent;

class FileComponent : public Component
{
public:

	FileComponent(const File, FileListBoxComponent&, int);
	~FileComponent() override;

	void paint(Graphics& g) override;
	void resized(void) override;

	void mouseDown(const juce::MouseEvent& event) override;

	String getFileName();
	File getFile();
	void fileAdded();
	void deselect();

private:
	FileListBoxComponent& owner;
	int row;

	DrawableText fileName;
	ToggleButton isAddedToggle;
	File file;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileComponent)
};