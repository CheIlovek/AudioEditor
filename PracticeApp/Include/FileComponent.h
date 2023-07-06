#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class FileComponent : public Component
{
public:

	FileComponent(const File file);
	~FileComponent() override;

	void paint(Graphics& g) override;
	void resized(void) override;

	String getFileName();
	File getFile();

private:
	DrawableText fileName;
	ToggleButton isAddedToggle;
	File file;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileComponent)
};