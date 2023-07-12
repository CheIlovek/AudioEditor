#pragma once
//
#include "../JuceLibraryCode/JuceHeader.h"
#include "DummyComponent.h"
#include "TracksListBox.h"
#include "MainMenuBarComponent.h"
#include "FileListBoxComponent.h"
#include "PlaybackComponent.h"
#include "FileComponent.h"
//
class MainComponent : public Component
{
public:
    MainComponent(void);
    ~MainComponent(void) override;
    //
    void paint(Graphics&) override;
    void resized(void) override;
    //
private:
    DummyComponent effectHistorySection;

    FileListBoxComponent fileListBoxSection;

    TracksListBox audioTracksSection;

    DummyComponent generalVolumeSection;

    PlaybackComponent playbackSection;

    MainMenuBarComponent mainMenuBarSection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};