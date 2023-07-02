#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MainMenuBarModel : public MenuBarModel
{
public:
    MainMenuBarModel();
	~MainMenuBarModel();


	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int index, const String& name);
	void menuItemSelected(int menuID, int index);

    enum MenuIDs {
        CreateProject = 1000,
        OpenProject,
        Save,
        SaveAs,
        ExportAs,
        Import,
        CloseProject,
        Exit,

        Undo,
        Redo,

        AddTrack,
        RemoveTrack,
        Mute,
        Solo,
        SelectAllTracks,

        SelectAll,
        Area,
        FromStartToCursor,
        FromCursorToEnd,
        SetRange,

        Deceleration,
        Acceleration,
        RaisingTone,
        LoweringTone,
        Echo,
        Equalizer,

        Description,
        Help
    };

private:

};