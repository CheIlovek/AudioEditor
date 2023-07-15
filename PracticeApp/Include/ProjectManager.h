#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class ProjectManager
{
public:
	ProjectManager();
	~ProjectManager();

	void openProject();
	void saveProject();

private:
	std::unique_ptr<juce::FileChooser> chooser;
};