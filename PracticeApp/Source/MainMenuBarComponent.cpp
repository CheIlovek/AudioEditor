#include "MainMenuBarComponent.h"

MainMenuBarComponent::MainMenuBarComponent(FileListBoxComponent* flbm, TracksListBox* tracks, EffectHistoryComponent* effectHistory) :
    flbm(flbm), tracks(tracks), effectHistory(effectHistory)
{
    menuBar.setModel(this);
    addAndMakeVisible(menuBar);
}

MainMenuBarComponent::~MainMenuBarComponent()
{
}

StringArray MainMenuBarComponent::getMenuBarNames()
{
    StringArray strs({
        RussianText::File::file.c_str(),
        RussianText::Edit::edit.c_str(),
        RussianText::Selection::selection.c_str(),
        RussianText::Tracks::tracks.c_str(),
        RussianText::Effects::effects.c_str(),
        RussianText::About::about.c_str(),
    });
    return strs;
}

PopupMenu MainMenuBarComponent::getMenuForIndex(int index, const String& name)
{
    DBG(name);
    PopupMenu menu;
    if (name == RussianText::File::file.c_str())
    {
        menu.addItem(CreateProject, RussianText::File::createProject.c_str(), false);
        menu.addItem(OpenProject,   RussianText::File::openProject  .c_str());
        menu.addItem(Save,          RussianText::File::save         .c_str(), false);
        menu.addItem(SaveAs,        RussianText::File::saveAs       .c_str());
        menu.addItem(ExportAs,      RussianText::File::exportAs     .c_str());
        menu.addItem(Import,        RussianText::File::import       .c_str());
        menu.addItem(CloseProject,  RussianText::File::closeProject .c_str(), false);
        menu.addItem(Exit,          RussianText::File::exit         .c_str());
    }
    else if (name == RussianText::Edit::edit.c_str()) {
        menu.addItem(Undo, RussianText::Edit::undo.c_str(), false);
        menu.addItem(Redo, RussianText::Edit::redo.c_str(), false);
    }
    else if (name == RussianText::Tracks::tracks.c_str()) {
        menu.addItem(AddTrack,          RussianText::Tracks::addTrack       .c_str());
        menu.addItem(RemoveTrack,       RussianText::Tracks::removeTrack    .c_str(), false);
        menu.addItem(AddAudio,          RussianText::Tracks::addAudio       .c_str());
        menu.addItem(Mute,              RussianText::Tracks::mute           .c_str());
        menu.addItem(Solo,              RussianText::Tracks::solo           .c_str());
        menu.addItem(SelectAllTracks,   RussianText::Tracks::selectAllTracks.c_str(), false);
    }
    else if (name == RussianText::Selection::selection.c_str()) {
        //MAKE DISABLED, IF THESE BUTTONS WILL NOT BE IMPLEMENTED!!!!!!!
        menu.addItem(SelectAll,             RussianText::Selection::selectAll               .c_str());
        PopupMenu subMenu;
        subMenu.addItem(FromStartToCursor,  RussianText::Selection::Area::fromStartToCursor .c_str());
        subMenu.addItem(FromCursorToEnd,    RussianText::Selection::Area::fromCursorToEnd   .c_str());
        subMenu.addItem(SetRange,           RussianText::Selection::Area::setRange          .c_str());
        menu.addSubMenu(                    RussianText::Selection::Area::area              .c_str(),
            subMenu);
    }
    else if (name == RussianText::Effects::effects.c_str()) {
        menu.addItem(Reverberation, RussianText::Effects::reverberation     .c_str());
        menu.addItem(Deceleration,  RussianText::Effects::deceleration      .c_str(), false);
        menu.addItem(Acceleration,  RussianText::Effects::accecelaration    .c_str(), false);
        menu.addItem(RaisingTone,   RussianText::Effects::rasingTheTone     .c_str(), false);
        menu.addItem(LoweringTone,  RussianText::Effects::loweringTheTone   .c_str(), false);
        menu.addItem(Echo,          RussianText::Effects::echo              .c_str(), false);
        menu.addItem(Equalizer,     RussianText::Effects::equalizer         .c_str(), false);
    }
    else if (name == RussianText::About::about.c_str()) {
        menu.addItem(Description,   RussianText::About::decsription .c_str());
        menu.addItem(Help,          RussianText::About::help        .c_str());
    }
    return menu;
}

void MainMenuBarComponent::menuItemSelected(int menuID, int index)
{
    auto& source = tracks->getAudioSource();
    switch (menuID) {
    case OpenProject:
        manager.openProject();
        break;
    case SaveAs:
        manager.saveProject();
        break;
    case ExportAs:
        flbm->saveFile(&source, source.getNumSamples(), source.getNumChannels(), source.getSampleRate());
        break;
    case Import:
        flbm->openFile();
        break;
    case Exit:
        JUCEApplication::getInstance()->systemRequestedQuit();
        break;
    case AddTrack:
        tracks->addNewTrack();
        effectHistory->addNewTrackHistory();
        break;
    case AddAudio:
        if (tracks->getNumOfSelectedRows() == 1 && flbm->getNumOfSelectedRows() == 1)
        {
            tracks->setFileOnTrack(flbm->getSelectedFile());
            flbm->selectedFileAdded();
        }
        break;
    case Mute:
        if (tracks->getNumOfSelectedRows() == 1)
        {
            auto track = tracks->getTrack(tracks->getSelectedRow());
            track->muteButtonClicked();
        }
        break;
    case Solo:
        if (tracks->getNumOfSelectedRows() == 1)
        {
            auto track = tracks->getTrack(tracks->getSelectedRow());
            track->superiorButtonClicked();
        }
        break;
    case SelectAll:
        tracks->selectAllOnTrack();
        break;
    case FromStartToCursor:
        tracks->selectAreaBeforePointer();
        break;
    case FromCursorToEnd:
        tracks->selectAreaAfterPointer();
        break;
        //Осталась AREAAAAAAAAAAAAA
    case Reverberation:
        if (tracks->getNumOfSelectedRows() == 1)
            tracks->applyReverbOnTrack([this] {effectHistory->addNewEffect(RussianText::Effects::reverberation.c_str()); });
        break;
    case Description:
        showDescriptionWindow();
        break;
    case Help:
        showHelpWindow();
        break;
    }
}

void MainMenuBarComponent::resized(void)
{
    menuBar.setBounds(0, 0, getWidth(), getHeight());
}

void MainMenuBarComponent::paint(Graphics& g)
{
}

void MainMenuBarComponent::showDescriptionWindow()
{
    AlertWindow::showMessageBoxAsync(MessageBoxIconType::InfoIcon, "ASAP Audition",
        RussianText::About::descriptionText.c_str(), "OK");
}

void MainMenuBarComponent::showHelpWindow()
{
    DialogWindow::showDialog(RussianText::About::help.c_str(), &helpWindowComponent, NULL,
        ProjectColours::HelpWindow::backgroundColour, true);
}
