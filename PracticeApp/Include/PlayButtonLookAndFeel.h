#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ProjectColours.h"

class PlayButtonLookAndFeel : public LookAndFeel_V4 {
public:
	PlayButtonLookAndFeel();

	void drawButtonBackground(Graphics&, Button&, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

	void drawButtonOnPlay(Graphics& g, Rectangle<float> area);
	void drawButtonOnPause(Graphics& g, Rectangle<float> area);

private:
	const float thicknessPercentage = 0.1f;
};