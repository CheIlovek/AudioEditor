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
        const std::wstring file(L"����");
        const std::wstring createProject(L"������� ������");
        const std::wstring openProject(L"������� ������");
        const std::wstring save(L"���������");
        const std::wstring saveAs(L"��������� ���...");
        const std::wstring exportAs(L"�������������� ���...");
        const std::wstring import(L"�������������");
        const std::wstring closeProject(L"������� ������");
        const std::wstring exit(L"�����");
    }
    namespace Edit {
        const std::wstring edit(L"������");
        const std::wstring redo(L"������� ��������");
        const std::wstring undo(L"�������� ��������");
    }

    namespace Tracks {
        const std::wstring tracks(L"�������");
        const std::wstring addTrack(L"�������� �������");
        const std::wstring removeTrack(L"������� �������");
        const std::wstring addAudio(L"�������� �����");
        const std::wstring mute(L"��� �����");
        const std::wstring solo(L"����");
        const std::wstring selectAllTracks(L"�������� ��� �������");
    }

    namespace Selection {
        const std::wstring selection(L"���������");
        const std::wstring selectAll(L"�������� ��");
        namespace Area {
            const std::wstring area(L"�������");
            const std::wstring fromStartToCursor(L"�� ������ �� �������");
            const std::wstring fromCursorToEnd(L"�� ������� �� �����");
            const std::wstring setRange(L"������ ��������");
        } 
    }
    
    namespace Effects {
        const std::wstring effects(L"�������");
        const std::wstring reverberation(L"������������");
        const std::wstring deceleration(L"����������");
        const std::wstring accecelaration(L"���������");
        const std::wstring rasingTheTone(L"��������� ����");
        const std::wstring loweringTheTone(L"��������� ����");
        const std::wstring echo(L"���");
        const std::wstring equalizer(L"����������");
    }

    namespace About {
        const std::wstring about(L"�������");
        const std::wstring decsription(L"� ���������");
        const std::wstring help(L"������");
        const std::wstring descriptionText(L"\n������: �������� ���������, ������� ������\n����������: ����� ��������\n���� � ���������: �++ Juce");
    }

}