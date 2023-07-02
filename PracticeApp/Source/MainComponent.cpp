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
    const char* menuNames[] = { "File", "Edit", "Tracks", "Selection", "Effects", "About", 0};
    return StringArray(menuNames);
}

PopupMenu MainComponent::getMenuForIndex(int index, const String& name)
{
    PopupMenu menu;
    if (name == "File")
    {
        menu.addItem(CreateProject, "Create project");
        menu.addItem(OpenProject, "Open project");
        menu.addItem(Save, "Save");
        menu.addItem(SaveAs, "Save as...");
        menu.addItem(ExportAs, "Export as...");
        menu.addItem(Import, "Import");
        menu.addItem(CloseProject, "Close project");
        menu.addItem(Exit, "Exit");
    }
    else if (name == "Edit") {
        menu.addItem(Undo, "Undo");
        menu.addItem(Redo, "Redo");
    }
    else if (name == "Tracks") {
        menu.addItem(AddTrack, "Add track");
        menu.addItem(RemoveTrack, "Remove track");
        menu.addItem(Mute, "Mute");
        menu.addItem(Solo, "Solo");
        menu.addItem(SelectAllTracks, "Select all tracks");
    }
    else if (name == "Selection") {
        menu.addItem(SelectAll, "Select all");
        menu.addItem(Area, "Area...");
    }
    else if (name == "Effects") {
        menu.addItem(Deceleration, "Deceleration");
        menu.addItem(Acceleration, "Acceleration");
        menu.addItem(RaisingTone, "Raising the tone");
        menu.addItem(LoweringTone, "Lowering the tone");
        menu.addItem(Echo, "Echo");
        menu.addItem(Equalizer, "Equalizer");
    }
    else if (name == "About") {
        menu.addItem(Description, "Description");
        menu.addItem(Help, "Help");
    }
    return menu;
}

void MainComponent::menuItemSelected(int menuID, int index)
{
    /*
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
    */
}
