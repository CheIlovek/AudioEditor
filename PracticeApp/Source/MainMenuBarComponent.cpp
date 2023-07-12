#include "MainMenuBarComponent.h"

MainMenuBarComponent::MainMenuBarComponent(FileListBoxComponent* flbm, TracksListBox* tracks) :
    flbm(flbm), tracks(tracks)
{
    menuBar.setModel(this);
    addAndMakeVisible(menuBar);
}

MainMenuBarComponent::~MainMenuBarComponent()
{
}

StringArray MainMenuBarComponent::getMenuBarNames()
{
    const char* menuNames[] = { "File", "Edit", "Tracks", "Selection", "Effects", "About", 0 };
    return StringArray(menuNames);
}

PopupMenu MainMenuBarComponent::getMenuForIndex(int index, const String& name)
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
        menu.addItem(Reverberation, "Reverberation");
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

void MainMenuBarComponent::menuItemSelected(int menuID, int index)
{
    switch (menuID) {
    case Import:
        flbm->openFile();
        break;
    case AddTrack:
        tracks->addNewTrack();
        break;
    case AddAudio:
        if(tracks->getNumOfSelectedRows() == 1 && flbm->getNumOfSelectedRows() == 1)
            tracks->setFileOnTrack(flbm->getSelectedFile());
        break;
    case Reverberation:
        if (tracks->getNumOfSelectedRows() == 1)
        {
            int index = tracks->getSelectedRow();
            tracks->applyReverbOnTrack(index);
        }
        break;
    }
}

void MainMenuBarComponent::resized(void)
{
    menuBar.setBounds(0, 0, getWidth(), getHeight());
}

void MainMenuBarComponent::paint(Graphics& g)
{
}