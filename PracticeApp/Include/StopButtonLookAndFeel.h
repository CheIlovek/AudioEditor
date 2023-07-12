#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ProjectColours.h"

class StopButtonLookAndFeel : public LookAndFeel_V4 {
public:
	StopButtonLookAndFeel();

	void drawButtonBackground(Graphics&, Button&, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};
