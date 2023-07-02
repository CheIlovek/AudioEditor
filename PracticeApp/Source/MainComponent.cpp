#include "../Include/MainComponent.h"
//
MainComponent::MainComponent(void) : systemMenuContainer(this)
{
    addAndMakeVisible(effectHistoryContainer);
    addAndMakeVisible(projectFilesContainer);
    addAndMakeVisible(mainAudioWaveContainer);
    addAndMakeVisible(generalVolumeContainer);
    addAndMakeVisible(playControlsContainer);
    addAndMakeVisible(&systemMenuContainer);
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
    systemMenuContainer.setBounds(r.removeFromTop(r.getHeight() * percentageSystemMenu));
    auto leftSide = r.removeFromLeft(getWidth() * percentageLeftSide);
    effectHistoryContainer.setBounds(leftSide.removeFromTop(leftSide.getHeight() * percentageEffects));
    projectFilesContainer.setBounds(leftSide);
    playControlsContainer.setBounds(r.removeFromBottom(r.getHeight() * percentagePlayControls));
    generalVolumeContainer.setBounds(r.removeFromRight(r.getWidth() * percentageGeneralVolume));
    mainAudioWaveContainer.setBounds(r);

}

StringArray MainComponent::getMenuBarNames()
{
    const char* menuNames[] = { "Label", "Slider", 0 };
    return StringArray(menuNames);
}

PopupMenu MainComponent::getMenuForIndex(int index, const String& name)
{
    PopupMenu menu;
    if (name == "Label")
    {
        menu.addItem(LabelClear, "Clear");
    }
    else if (name == "Slider") {
        menu.addItem(SliderMin, "Set to minimum");
        menu.addItem(SliderMax, "Set to maximum");
    }
    return menu;
}

void MainComponent::menuItemSelected(int menuID, int index)
{
    int a = 0;
    switch (menuID) {
    case LabelClear:
        a = 1;
        break;
    case SliderMin:
        a = 2;
        break;
    case SliderMax:
        a = 3;
        break;
    }
}
