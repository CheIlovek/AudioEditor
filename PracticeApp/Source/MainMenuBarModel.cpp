#include "MainMenuBarModel.h"

MainMenuBarModel::MainMenuBarModel()
{
}

MainMenuBarModel::~MainMenuBarModel()
{
}

StringArray MainMenuBarModel::getMenuBarNames()
{
    const char* menuNames[] = { "File", "Edit", "Tracks", "Selection", "Effects", "About", 0 };
    return StringArray(menuNames);
}

PopupMenu MainMenuBarModel::getMenuForIndex(int index, const String& name)
{
    PopupMenu menu;
    if (name == "File")
    {
        menu.addItem(CreateProject, "Create project");
        menu.addItem(OpenProject, "Open project");
        menu.addItem(Save, "Save");
        menu.addItem(SaveAs, "Save as...");
        menu.addItem(ExportAs, "Export as...");
        menu.addItem(Import, "Import");
        menu.addItem(CloseProject, "Close project");
        menu.addItem(Exit, "Exit");
    }
    else if (name == "Edit") {
        menu.addItem(Undo, "Undo");
        menu.addItem(Redo, "Redo");
    }
    else if (name == "Tracks") {
        menu.addItem(AddTrack, "Add track");
        menu.addItem(RemoveTrack, "Remove track");
        menu.addItem(Mute, "Mute");
        menu.addItem(Solo, "Solo");
        menu.addItem(SelectAllTracks, "Select all tracks");
    }
    else if (name == "Selection") {
        menu.addItem(SelectAll, "Select all");
        menu.addItem(Area, "Area...");
    }
    else if (name == "Effects") {
        menu.addItem(Deceleration, "Deceleration");
        menu.addItem(Acceleration, "Acceleration");
        menu.addItem(RaisingTone, "Raising the tone");
        menu.addItem(LoweringTone, "Lowering the tone");
        menu.addItem(Echo, "Echo");
        menu.addItem(Equalizer, "Equalizer");
    }
    else if (name == "About") {
        menu.addItem(Description, "Description");
        menu.addItem(Help, "Help");
    }
    return menu;
}

void MainMenuBarModel::menuItemSelected(int menuID, int index)
{
    /*
    int a = 0;
    switch (menuID) {
    case LabelClear:
        a = 1;
        break;
    case SliderMin:
        a = 2;
        break;
    case SliderMax:
        a = 3;
        break;
    }
    */
}