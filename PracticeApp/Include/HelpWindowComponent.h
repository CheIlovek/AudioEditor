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
		std::wstring(L"Данный раздел отвечает за управление файлами внутри проекта.\n"),
		std::wstring(L"Добавить файл в раздел можно через меню:\nФайл -> Импортировать.\n"),
		std::wstring(L"Также, выделив файл левой кнопкой мыши, можно добавить его на существующую дорожку через меню:\nДорожки -> Добавить аудио\n"),
		//std::wstring(L"Функций"),
		//std::wstring(L"Раздела файлов"),
		//std::wstring(L"Программы"),
	};
	const Array<std::wstring> tracksText = {
		std::wstring(L"Данный раздел позволяет наслаивать различные аудиозаписи и применять эффекты к ним.\n"),
		std::wstring(L"Добавить дорожку можно через меню:\nДорожки-> Добавить дорожку\n"),
		std::wstring(L"Кнопка 'Соло' позволяет заглушить все остальные дорожки"),
		std::wstring(L"Кнопка 'Без звука' отключает соответствующую дорожку"),
		std::wstring(L"Круговой слайдер позволяет отрегулировать баланс звука между левым и правым каналами."),
		std::wstring(L"Спектрограммы звука можно перемещать зажатой ЛКМ, приближать при помощи 'ALT + Колёсико мыши' и выделять ПКМ"),
		std::wstring(L"На дорожки можно накладывать эффекты через меню 'Эффекты' на выделенную область, или, если она отсутствует, на всю дорожку"),
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
