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

    void addNewTrack();
    void setAudioOnTrack();
    void setFileList(FileListBoxComponent* flbm);

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
    

};