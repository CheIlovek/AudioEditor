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
		std::wstring(L"Общее"),
		std::wstring(L"Меню"),
		std::wstring(L"Раздел файлов"),
		std::wstring(L"Раздел дорожек"),
		std::wstring(L"Воспроизведение"),
		std::wstring(L"Раздел эффектов"),
	};
	const Array<std::wstring> generalText = {
		std::wstring(L"Здесь"),
		std::wstring(L"Будет"),
		std::wstring(L"Описание"),
		std::wstring(L"Общих"),
		std::wstring(L"Функций"),
		std::wstring(L"Программы"),
	};
	const Array<std::wstring> menuText = {
		std::wstring(L"Здесь"),
		std::wstring(L"Будет"),
		std::wstring(L"Описание"),
		std::wstring(L"Функций"),
		std::wstring(L"Меню"),
		std::wstring(L"Программы"),
	};
	const Array<std::wstring> filesText = {
		std::wstring(L"Здесь"),
		std::wstring(L"Будет"),
		std::wstring(L"Описание"),
		std::wstring(L"Функций"),
		std::wstring(L"Раздела файлов"),
		std::wstring(L"Программы"),
	};
	const Array<std::wstring> tracksText = {
		std::wstring(L"Здесь"),
		std::wstring(L"Будет"),
		std::wstring(L"Описание"),
		std::wstring(L"Функций"),
		std::wstring(L"Раздела дорожек и самих дорожек"),
		std::wstring(L"Программы"),
	};
	const Array<std::wstring> playbackText = {
		std::wstring(L"Здесь"),
		std::wstring(L"Будет"),
		std::wstring(L"Описание"),
		std::wstring(L"Функций"),
		std::wstring(L"Разделов воспроизведения громкости"),
		std::wstring(L"Программы"),
	};
	const Array<std::wstring> effectsText = {
		std::wstring(L"Здесь"),
		std::wstring(L"Будет"),
		std::wstring(L"Описание"),
		std::wstring(L"Функций"),
		std::wstring(L"Раздела истории эффектов"),
		std::wstring(L"Программы"),
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
