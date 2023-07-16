#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "ProjectColours.h"

class ReverbWindowComponent : public Component
{
public:
	ReverbWindowComponent();
	~ReverbWindowComponent() override;

	void paint(Graphics& g) override;
	void resized(void) override;

	void updateParameters();
	TextButton* getApllyButton();
	Reverb::Parameters getParameters();

private:
	DrawableText roomSize;
	DrawableText damping;
	DrawableText wetLevel;
	DrawableText dryLevel;
	DrawableText width;
	DrawableText freezeMode;

	Slider roomSizeSlider;
	Slider dampingSlider;
	Slider wetLevelSlider;
	Slider dryLevelSlider;
	Slider widthSlider;
	Slider freezeModeSlider;

	Array<DrawableText*> labels;
	Array<Slider*> sliders;

	TextButton applyButton;

	Reverb::Parameters parameters;
};

namespace RussianText {
	const std::wstring roomSize(L"������ �������");
	const std::wstring damping(L"���������");
	const std::wstring wetLevel(L"������� ���������");
	const std::wstring dryLevel(L"������� �������");
	const std::wstring width(L"������ ������");
	const std::wstring freezeMode(L"������������");
	const std::wstring apply(L"���������");

}