#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileComponent.h"

class FileComponent;

class FileListBoxComponent : public Component, public ListBoxModel
{
public:

	FileListBoxComponent();
	~FileListBoxComponent();

	int getNumRows() override;
	void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate);
	void listBoxItemClicked(int row, const MouseEvent&) override;
	void backgroundClicked(const MouseEvent&) override;
	void resized(void) override;
	void paint(Graphics& g) override;
	void openFile();
	File getFile(int index);
	File getSelectedFile();
	int getNumOfSelectedRows();
	void selectedFileAdded();
	int getSelectedRow();

private:
	std::unique_ptr<juce::FileChooser> chooser;
	juce::Array<FileComponent*> fileList;
	ListBox fileListBox;

	DrawableText name;
	DrawableText added;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileListBoxComponent)
};

namespace RussianText {
	const std::wstring added(L"Добавлен");
	const std::wstring name(L"Имя");
	const std::wstring noFileInList(L"Нет файлов!\nВы можете добавить файл через меню Файл -> Импортировать");
}
