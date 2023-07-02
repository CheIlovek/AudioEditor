#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MenuBar : public Component, public MenuBarModel
{
public:
	MenuBar();
	~MenuBar() override;

	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int index, const String& name);
	void menuItemSelected(int menuID, int index);

	enum MenuIDs {
		LabelClear = 1000,
		SliderMin,
		SliderMax
	};

};