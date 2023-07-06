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
        menu.addItem(AddAudio, "Add audio");
        menu.addItem(Mute, "Mute");
        menu.addItem(Solo, "Solo");
        menu.addItem(SelectAllTracks, "Select all tracks");
    }
    else if (name == "Selection") {
        menu.addItem(SelectAll, "Select all");
        PopupMenu subMenu;
        subMenu.addItem(FromStartToCursor, "From start to cursor");
        subMenu.addItem(FromCursorToEnd, "From cursor to end");
        subMenu.addItem(SetRange, "Set range");
        menu.addSubMenu("Area", subMenu);
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
    switch (menuID) {
    case Import:
        flbm->openFile();
        break;
    }
}

void MainMenuBarModel::setFileList(FileListBoxComponent* f)
{
    flbm = f;
}
