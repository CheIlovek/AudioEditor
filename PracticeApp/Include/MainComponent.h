#pragma once
//
#include "../JuceLibraryCode/JuceHeader.h"
#include "DummyComponent.h"
#include "TracksListBox.h"
#include "MainMenuBarModel.h"
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
    DummyComponent effectHistoryContainer;
    DummyComponent projectFilesContainer;
    TracksListBox mainAudioWaveContainer;
    DummyComponent generalVolumeContainer;
    DummyComponent playControlsContainer;
    MainMenuBarModel mainMenuBarModel;
    MenuBarComponent mainMenuBarContainer; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};