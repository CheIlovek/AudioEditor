#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileListBoxComponent.h"
#include "TracksListBox.h"

class MainMenuBarComponent : public MenuBarModel, public Component
{
public:
    MainMenuBarComponent(FileListBoxComponent*, TracksListBox*);
	~MainMenuBarComponent();


	StringArray getMenuBarNames() override;
	PopupMenu getMenuForIndex(int index, const String& name) override;
	void menuItemSelected(int menuID, int index) override;

    void resized(void) override;
    void paint(Graphics& g) override;

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

    MenuBarComponent menuBar;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainMenuBarComponent)
};