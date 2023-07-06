#include "../Include/MainComponent.h"
//
MainComponent::MainComponent(void) : mainMenuBarModel(&fileListBoxComponent, &mainAudioTracksContainer)
{
    //mainMenuBarModel.setFileList(&fileListBoxComponent);
    mainMenuBarContainer.setModel(&mainMenuBarModel);
    addAndMakeVisible(effectHistoryContainer);
    addAndMakeVisible(fileListBoxComponent);
    addAndMakeVisible(mainAudioTracksContainer);
    addAndMakeVisible(generalVolumeContainer);
    addAndMakeVisible(playControlsContainer);
    addAndMakeVisible(mainMenuBarContainer);
    setOpaque(true);
    setSize(800, 800);
}
//
MainComponent::~MainComponent(void)
{
}
//
void MainComponent::paint(Graphics& g)
{
    g.fillAll(Colours::hotpink);
}
//
void MainComponent::resized(void)
{
    const double percentageSystemMenu = 0.03;
    const double percentageLeftSide = 0.3;
    const double percentageEffects = 0.5;
    const double percentageGeneralVolume = 0.1;
    const double percentagePlayControls = 0.05;
    
    auto r = getBounds();
    mainMenuBarContainer.setBounds(r.removeFromTop(r.getHeight() * percentageSystemMenu));
    auto leftSide = r.removeFromLeft(getWidth() * percentageLeftSide);
    effectHistoryContainer.setBounds(leftSide.removeFromTop(leftSide.getHeight() * percentageEffects));
    fileListBoxComponent.setBounds(leftSide);
    playControlsContainer.setBounds(r.removeFromBottom(r.getHeight() * percentagePlayControls));
    generalVolumeContainer.setBounds(r.removeFromRight(r.getWidth() * percentageGeneralVolume));
    mainAudioTracksContainer.setBounds(r);

}
