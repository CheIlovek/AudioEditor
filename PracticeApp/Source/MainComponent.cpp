#include "../Include/MainComponent.h"
#include "../Include/Menubar.h"
//
MainComponent::MainComponent(void)
{
    addAndMakeVisible(effectHistoryContainer);
    addAndMakeVisible(projectFilesContainer);
    addAndMakeVisible(mainAudioWaveContainer);
    addAndMakeVisible(generalVolumeContainer);
    addAndMakeVisible(playControlsContainer);
    addAndMakeVisible(systemMenuContainer);
    setOpaque(true);
    setSize(800, 800);
    MenuBar mb = MenuBar();
    menuBarComp.setModel(&mb);
    addAndMakeVisible(&menuBarComp);
    menuBarComp.setBounds(0, 0, proportionOfWidth(1.0f), 20);
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
    systemMenuContainer.setBounds(r.removeFromTop(r.getHeight() * percentageSystemMenu));
    auto leftSide = r.removeFromLeft(getWidth() * percentageLeftSide);
    effectHistoryContainer.setBounds(leftSide.removeFromTop(leftSide.getHeight() * percentageEffects));
    projectFilesContainer.setBounds(leftSide);
    playControlsContainer.setBounds(r.removeFromBottom(r.getHeight() * percentagePlayControls));
    generalVolumeContainer.setBounds(r.removeFromRight(r.getWidth() * percentageGeneralVolume));
    mainAudioWaveContainer.setBounds(r);

    menuBarComp.setBounds(0, 0, proportionOfWidth(1.0f), 20);
}