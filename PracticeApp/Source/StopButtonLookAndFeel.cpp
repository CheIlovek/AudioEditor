#include "StopButtonLookAndFeel.h"

StopButtonLookAndFeel::StopButtonLookAndFeel() {
}

void StopButtonLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {

	const float thicknessPercentage = 0.1f;
	auto area = button.getLocalBounds().toFloat();
	float thickness = area.getWidth() * thicknessPercentage;
	float circleThickness = thickness;
	float halfThickness = circleThickness / 2;
	area.reduce(halfThickness, halfThickness);
	
	g.setGradientFill(ColourGradient(
		ProjectColours::Playback::PlayButton::startColour, 0.f, 0.f,
		ProjectColours::Playback::PlayButton::endColour, area.getWidth(), area.getHeight(), false));
	g.drawEllipse(area, circleThickness);

	area.reduce(circleThickness * 3.f, circleThickness * 2.f);

	g.fillRect(area.getX() - thickness / 2, area.getY(), thickness, area.getHeight());
	g.fillRect(area.getRight() - thickness / 2, area.getY(), thickness, area.getHeight());
}
