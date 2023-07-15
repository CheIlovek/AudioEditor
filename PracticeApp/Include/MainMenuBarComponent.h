#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileListBoxComponent.h"
#include "TracksListBox.h"
#include "EffectHistoryComponent.h"

class MainMenuBarComponent : public MenuBarModel, public Component
{
public:
    MainMenuBarComponent(FileListBoxComponent*, TracksListBox*, EffectHistoryComponent*);
	~MainMenuBarComponent();


	StringArray getMenuBarNames() override;
	PopupMenu getMenuForIndex(int index, const String& name) override;
	void menuItemSelected(int menuID, int index) override;

    void resized(void) override;
    void paint(Graphics& g) override;

    void showDescriptionWindow();
    void showHelpWindow();

    enum MenuIDs {
        CreateProject = 1,
        OpenProject,
        Save,
        SaveAs,
        ExportAs,
        Import,
        CloseProject,
        Exit,

        Undo,
        Redo,

        AddTrack,
        RemoveTrack,
        AddAudio,
        Mute,
        Solo,
        SelectAllTracks,

        SelectAll,
        Area,
        FromStartToCursor,
        FromCursorToEnd,
        SetRange,

        Reverberation,
        Deceleration,
        Acceleration,
        RaisingTone,
        LoweringTone,
        Echo,
        Equalizer,

        Description,
        Help,
    };

private:
    FileListBoxComponent* flbm;
    TracksListBox* tracks;
    EffectHistoryComponent* effectHistory;

    MenuBarComponent menuBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainMenuBarComponent)
};

namespace RussianText {
    namespace File {
        const std::wstring file(L"Файл");
        const std::wstring createProject(L"Создать проект");
        const std::wstring openProject(L"Открыть проект");
        const std::wstring save(L"Сохранить");
        const std::wstring saveAs(L"Сохранить как...");
        const std::wstring exportAs(L"Экспортировать как...");
        const std::wstring import(L"Импортировать");
        const std::wstring closeProject(L"Закрыть проект");
        const std::wstring exit(L"Выйти");
    }
    namespace Edit {
        const std::wstring edit(L"Правка");
        const std::wstring redo(L"Вернуть действие");
        const std::wstring undo(L"Отменить действие");
    }

    namespace Tracks {
        const std::wstring tracks(L"Дорожки");
        const std::wstring addTrack(L"Добавить дорожку");
        const std::wstring removeTrack(L"Удалить дорожку");
        const std::wstring addAudio(L"Добавить аудио");
        const std::wstring mute(L"Без звука");
        const std::wstring solo(L"Соло");
        const std::wstring selectAllTracks(L"Выделить все дорожки");
    }

    namespace Selection {
        const std::wstring selection(L"Выделение");
        const std::wstring selectAll(L"Выделить всё");
        namespace Area {
            const std::wstring area(L"Область");
            const std::wstring fromStartToCursor(L"От начала до курсора");
            const std::wstring fromCursorToEnd(L"От курсора до конца");
            const std::wstring setRange(L"Задать диапазон");
        } 
    }
    
    namespace Effects {
        const std::wstring effects(L"Эффекты");
        const std::wstring reverberation(L"Реверберация");
        const std::wstring deceleration(L"Замедление");
        const std::wstring accecelaration(L"Ускорение");
        const std::wstring rasingTheTone(L"Повышение тона");
        const std::wstring loweringTheTone(L"Понижение тона");
        const std::wstring echo(L"Эхо");
        const std::wstring equalizer(L"Эквалайзер");
    }

    namespace About {
        const std::wstring about(L"Справка");
        const std::wstring decsription(L"О программе");
        const std::wstring help(L"Помощь");
        const std::wstring descriptionText(L"\nАвторы: Соловьёв Александр, Правдин Андрей\nНазначение: аудио редактор\nЯзык и фреймворк: С++ Juce");
    }

}