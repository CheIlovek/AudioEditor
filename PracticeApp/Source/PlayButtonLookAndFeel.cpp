#include "PlayButtonLookAndFeel.h"

PlayButtonLookAndFeel::PlayButtonLookAndFeel() {
}

void PlayButtonLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
	
	const float thicknessPercentage = 0.1f;
	
	auto area = button.getLocalBounds().toFloat();
	float circleThickness = area.getWidth() * thicknessPercentage;
	float halfThickness = circleThickness / 2;
	area.reduce(halfThickness, halfThickness);

	g.setGradientFill(ColourGradient(
		ProjectColours::Playback::PlayButton::startColour, 0.f, 0.f,
		ProjectColours::Playback::PlayButton::endColour, area.getWidth(), area.getHeight(),false));
	g.drawEllipse(area, circleThickness);

	area.reduce(circleThickness * 1.5f, circleThickness * 1.5f);
	float center = area.getWidth() / 2;
	float centerOffset = center * std::sqrt(2) / 2;
	float centerOffsetX = center * std::sqrt(3) / 2;
	float centerOffsetY = center / 2;
	Path icon;
	icon.addTriangle(area.getWidth(), center, center - centerOffsetY, center - centerOffsetX, center - centerOffsetY, center + centerOffsetX);
	icon.applyTransform(AffineTransform::translation(circleThickness * 2.f, circleThickness * 2.f));
	g.fillPath(icon);
}
