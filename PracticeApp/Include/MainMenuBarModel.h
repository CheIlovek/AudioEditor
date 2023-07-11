#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileListBoxComponent.h"
#include "TracksListBox.h"

class MainMenuBarModel : public MenuBarModel
{
public:
    MainMenuBarModel(FileListBoxComponent*, TracksListBox*);
    MainMenuBarModel();
	~MainMenuBarModel();


	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int index, const String& name);
	void menuItemSelected(int menuID, int index);

    enum MenuIDs {
        CreateProject = 1,
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
        AddAudio,
        Mute,
        Solo,
        SelectAllTracks,

        SelectAll,
        Area,
        FromStartToCursor,
        FromCursorToEnd,
        SetRange,

        Reverberation,
        Deceleration,
        Acceleration,
        RaisingTone,
        LoweringTone,
        Echo,
        Equalizer,

        Description,
        Help,
    };

private:
    FileListBoxComponent* flbm;
    TracksListBox* tracks;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainMenuBarModel)
};