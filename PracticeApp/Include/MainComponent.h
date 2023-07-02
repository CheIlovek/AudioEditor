#pragma once
//
#include "../JuceLibraryCode/JuceHeader.h"
#include "DummyComponent.h"
#include "TracksListBox.h"
//
class MainComponent : public Component, public MenuBarModel
{
public:
    MainComponent(void);
    ~MainComponent(void) override;
    //
    void paint(Graphics&) override;
    void resized(void) override;
    //

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
    DummyComponent effectHistoryContainer;
    DummyComponent projectFilesContainer;
    TracksListBox mainAudioWaveContainer;
    DummyComponent generalVolumeContainer;
    DummyComponent playControlsContainer;
    MenuBarComponent systemMenuContainer; // Твоя менюшка сверху
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};