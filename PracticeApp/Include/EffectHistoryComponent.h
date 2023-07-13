#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ProjectColours.h"
#include "EffectListBoxModel.h"
#include "TracksListBox.h"

class EffectHistoryComponent : public Component
{
public:
	EffectHistoryComponent(TracksListBox*);
	~EffectHistoryComponent() override;

	void resized(void) override;
	void paint(Graphics& g) override;

	void addNewTrackHistory();
	void addNewEffect(String effectName);

	void comboBoxItemChanged();
	void clearButtonClicked();

	void clearButtonClicked();

private:
	Array<EffectListBoxModel*> modelList;
	ComboBox namesComboBox;
	ListBox listBox;
	TextButton clearButton;

	TracksListBox* tracks;
};

namespace RussianText {
	const std::wstring all(L"�������");
	const std::wstring choice(L"������� �������...");
	const std::wstring empty(L"�����");
	const std::wstring clear(L"������� ��� �������");

}