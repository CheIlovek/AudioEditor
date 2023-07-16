#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "ProjectColours.h"

class HelpWindowComponent : public Component
{
public:
	HelpWindowComponent();
	~HelpWindowComponent() override;

	void resized(void) override;
	void paint(Graphics& g) override;

	void comboBoxItemChanged();
private:
	//Array<String> text;
	Label label;
	ComboBox sections;
};

namespace RussianText {
	const Array<std::wstring> sectionNames = {
		std::wstring(L"�����"),
		std::wstring(L"����"),
		std::wstring(L"������ ������"),
		std::wstring(L"������ �������"),
		std::wstring(L"���������������"),
		std::wstring(L"������ ��������"),
	};
	const Array<std::wstring> generalText = {
		std::wstring(L"�����"),
		std::wstring(L"�����"),
		std::wstring(L"��������"),
		std::wstring(L"�����"),
		std::wstring(L"�������"),
		std::wstring(L"���������"),
	};
	const Array<std::wstring> menuText = {
		std::wstring(L"�����"),
		std::wstring(L"�����"),
		std::wstring(L"��������"),
		std::wstring(L"�������"),
		std::wstring(L"����"),
		std::wstring(L"���������"),
	};
	const Array<std::wstring> filesText = {
		std::wstring(L"������ ������ �������� �� ���������� ������� ������ �������.\n"),
		std::wstring(L"�������� ���� � ������ ����� ����� ����:\n���� -> �������������.\n"),
		std::wstring(L"�����, ������� ���� ����� ������� ����, ����� �������� ��� �� ������������ ������� ����� ����:\n������� -> �������� �����\n"),
		//std::wstring(L"�������"),
		//std::wstring(L"������� ������"),
		//std::wstring(L"���������"),
	};
	const Array<std::wstring> tracksText = {
		std::wstring(L"������ ������ ��������� ���������� ��������� ����������� � ��������� ������� � ���.\n"),
		std::wstring(L"�������� ������� ����� ����� ����:\n�������-> �������� �������\n"),
		std::wstring(L"������ '����' ��������� ��������� ��� ��������� �������"),
		std::wstring(L"������ '��� �����' ��������� ��������������� �������"),
		std::wstring(L"�������� ������� ��������� �������������� ������ ����� ����� ����� � ������ ��������."),
		std::wstring(L"������������� ����� ����� ���������� ������� ���, ���������� ��� ������ 'ALT + ������� ����' � �������� ���"),
		std::wstring(L"�� ������� ����� ����������� ������� ����� ���� '�������' �� ���������� �������, ���, ���� ��� �����������, �� ��� �������"),
	};
	const Array<std::wstring> playbackText = {
		std::wstring(L"�����"),
		std::wstring(L"�����"),
		std::wstring(L"��������"),
		std::wstring(L"�������"),
		std::wstring(L"�������� ��������������� ���������"),
		std::wstring(L"���������"),
	};
	const Array<std::wstring> effectsText = {
		std::wstring(L"�����"),
		std::wstring(L"�����"),
		std::wstring(L"��������"),
		std::wstring(L"�������"),
		std::wstring(L"������� ������� ��������"),
		std::wstring(L"���������"),
	};

	const Array<Array<std::wstring>> text = {
		generalText,
		menuText,
		filesText,
		tracksText,
		playbackText,
		effectsText,
	};
}
