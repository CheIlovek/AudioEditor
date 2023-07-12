#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ProjectColours.h"

class PlayButtonLookAndFeel : public LookAndFeel_V4 {
public:
	PlayButtonLookAndFeel();

	void drawButtonBackground(Graphics&, Button&, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};