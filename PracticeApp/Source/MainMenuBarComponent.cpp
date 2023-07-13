#include "MainMenuBarComponent.h"

MainMenuBarComponent::MainMenuBarComponent(FileListBoxComponent* flbm, TracksListBox* tracks) :
    flbm(flbm), tracks(tracks)
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
        menu.addItem(CreateProject, RussianText::File::createProject.c_str());
        menu.addItem(OpenProject,   RussianText::File::openProject  .c_str());
        menu.addItem(Save,          RussianText::File::save         .c_str());
        menu.addItem(SaveAs,        RussianText::File::saveAs       .c_str());
        menu.addItem(ExportAs,      RussianText::File::exportAs     .c_str());
        menu.addItem(Import,        RussianText::File::import       .c_str());
        menu.addItem(CloseProject,  RussianText::File::closeProject .c_str());
        menu.addItem(Exit,          RussianText::File::exit         .c_str());
    }
    else if (name == RussianText::Edit::edit.c_str()) {
        menu.addItem(Undo, RussianText::Edit::undo.c_str());
        menu.addItem(Redo, RussianText::Edit::redo.c_str());
    }
    else if (name == RussianText::Tracks::tracks.c_str()) {
        menu.addItem(AddTrack,          RussianText::Tracks::addTrack       .c_str());
        menu.addItem(RemoveTrack,       RussianText::Tracks::removeTrack    .c_str());
        menu.addItem(AddAudio,          RussianText::Tracks::addAudio       .c_str());
        menu.addItem(Mute,              RussianText::Tracks::mute           .c_str());
        menu.addItem(Solo,              RussianText::Tracks::solo           .c_str());
        menu.addItem(SelectAllTracks,   RussianText::Tracks::selectAllTracks.c_str());
    }
    else if (name == RussianText::Selection::selection.c_str()) {
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
        menu.addItem(Deceleration,  RussianText::Effects::deceleration      .c_str());
        menu.addItem(Acceleration,  RussianText::Effects::accecelaration    .c_str());
        menu.addItem(RaisingTone,   RussianText::Effects::rasingTheTone     .c_str());
        menu.addItem(LoweringTone,  RussianText::Effects::loweringTheTone   .c_str());
        menu.addItem(Echo,          RussianText::Effects::echo              .c_str());
        menu.addItem(Equalizer,     RussianText::Effects::equalizer         .c_str());
    }
    else if (name == RussianText::About::about.c_str()) {
        menu.addItem(Description,   RussianText::About::decsription .c_str());
        menu.addItem(Help,          RussianText::About::help        .c_str());
    }
    return menu;
}

void MainMenuBarComponent::menuItemSelected(int menuID, int index)
{
    switch (menuID) {
    case Import:
        flbm->openFile();
        break;
    case AddTrack:
        tracks->addNewTrack();
        break;
    case AddAudio:
        if(tracks->getNumOfSelectedRows() == 1 && flbm->getNumOfSelectedRows() == 1)
            tracks->setFileOnTrack(flbm->getSelectedFile());
        break;
    case Reverberation:
        if (tracks->getNumOfSelectedRows() == 1)
        {
            int index = tracks->getSelectedRow();
            tracks->applyReverbOnTrack(index);
        }
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
