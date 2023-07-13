#include "BalanceSliderLookAndFeel.h"

void BalanceSliderLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, 
												int width, int height, float sliderPosProportional,
												float rotaryStartAngle, float rotaryEndAngle, Slider& slider) {

	const Colour mainColour = ProjectColours::Tracks::sliderColour;
	const float circleThickness = 2.f;
	const float pointerThickness = 2.f;
	const float letterSize = 0.15f;
	Rectangle<float> circleArea(x, y, width, height);

	auto valueTextArea = circleArea.removeFromBottom(width * letterSize * 2.f);
	auto leftLetterArea =	circleArea.removeFromLeft(width * letterSize);
	auto rightLetterArea =	circleArea.removeFromRight(width * letterSize);
	circleArea.reduce(circleThickness * 2.f, circleThickness * 2.f);
	
	
	// Рисуем буквы
	g.setFont(20);
	g.setColour(mainColour);
	g.drawText("L", leftLetterArea, juce::Justification::centredBottom);
	g.drawText("R", rightLetterArea, juce::Justification::centredBottom);

	// Рисуем значение слайдера
	char val[6];
	std::sprintf(val, "%.2f", slider.getValue());

	g.drawText(val, valueTextArea, juce::Justification::centredBottom);

	// Рисуем круг
	g.setColour(Colours::darkgrey);
	g.fillEllipse(circleArea);

	g.setColour(mainColour);
	g.drawEllipse(circleArea,circleThickness);

	float r = circleArea.getWidth() / 2.f;
	double angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
	g.drawLine(
		circleArea.getX() + r, circleArea.getY() + r,
		circleArea.getX() + r + r * std::sin(angle), circleArea.getY() + r - r * std::cos(angle), pointerThickness);



}
