#include "../Include/MainComponent.h"
//
MainComponent::MainComponent(void) :
    mainMenuBarSection(&fileListBoxSection, &audioTracksSection, &effectHistorySection),
    playbackSection(&audioTracksSection.getAudioSource()),
    effectHistorySection(&audioTracksSection)
{
    addAndMakeVisible(effectHistorySection);
    addAndMakeVisible(fileListBoxSection);
    addAndMakeVisible(audioTracksSection);
    addAndMakeVisible(generalVolumeSection);
    addAndMakeVisible(playbackSection);
    addAndMakeVisible(mainMenuBarSection);
    setOpaque(true);
    setSize(800, 800);
    playbackSection.setVolumeGUI(&generalVolumeSection.getSlider());
    generalVolumeSection.getSlider().setSource(&audioTracksSection.getAudioSource());
}
//
MainComponent::~MainComponent(void)
{
}
//
void MainComponent::paint(Graphics& g)
{
    g.fillAll(ProjectColours::generalBackground);
}
//
void MainComponent::resized(void)
{
    //const double percentageSystemMenu = 0.03;
    const double percentageLeftSide = 0.3;
    const double percentageEffects = 0.5;
    const double percentageGeneralVolume = 0.1;
    const double percentagePlayback = 0.05;
    
    auto r = getBounds();
    mainMenuBarSection.setBounds(r.removeFromTop(22));
    auto leftSide = r.removeFromLeft(getWidth() * percentageLeftSide);
    effectHistorySection.setBounds(leftSide.removeFromTop(leftSide.getHeight() * percentageEffects));
    fileListBoxSection.setBounds(leftSide);
    playbackSection.setBounds(r.removeFromBottom(r.getHeight() * percentagePlayback));
    generalVolumeSection.setBounds(r.removeFromRight(r.getWidth() * percentageGeneralVolume));
    audioTracksSection.setBounds(r);

}
