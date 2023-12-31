#pragma once
//
#include "../JuceLibraryCode/JuceHeader.h"
#include "DummyComponent.h"
#include "TracksListBox.h"
#include "MainMenuBarComponent.h"
#include "FileListBoxComponent.h"
#include "PlaybackComponent.h"
#include "FileComponent.h"
#include "GeneralVolumeComponent.h"
#include "EffectHistoryComponent.h"
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
    EffectHistoryComponent effectHistorySection;

    FileListBoxComponent fileListBoxSection;

    TracksListBox audioTracksSection;

    GeneralVolumeComponent generalVolumeSection;

    PlaybackComponent playbackSection;

    MainMenuBarComponent mainMenuBarSection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};