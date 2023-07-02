#include "../Include/Menubar.h"
#include "juce_data_structures/juce_data_structures.h"

MenuBar::MenuBar()
{

}

MenuBar::~MenuBar()
{

}

StringArray MenuBar::getMenuBarNames()
{
	const char* menuNames[] = {"Label", "Slider", 0};
	return StringArray(menuNames);
}

PopupMenu MenuBar::getMenuForIndex(int index, const String& name)
{
	PopupMenu menu;
	if (name == "Label")
	{
		menu.addItem(LabelClear, "Clear");
	}
	else if (name == "Slider") {
		menu.addItem(SliderMin, "Set to minimum");
		menu.addItem(SliderMax, "Set to maximum");
	}
	return menu;

}

void MenuBar::menuItemSelected(int menuID, int index)
{
	switch (menuID) {
	case LabelClear:
		//label.setText(String::empty, dontSendNotification);
		break;
	case SliderMin:
		//slider.setValue(slider.getMinimum());
		break;
	case SliderMax:
		//slider.setValue(slider.getMaximum());
		break;
	}

}
