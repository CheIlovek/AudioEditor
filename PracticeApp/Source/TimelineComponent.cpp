#include "TimelineComponent.h"

TimelineComponent::TimelineComponent(const double& zoom, const double& pixelsPerSecond, const int leftSideSize) :
	zoom(zoom),
	pixelsPerSecond(pixelsPerSecond),
	leftSideSize(leftSideSize) {}

void TimelineComponent::paint(juce::Graphics& g) {
	auto area = getLocalBounds();
	area.removeFromLeft(leftSideSize);

	int len = area.getWidth();
	int height = area.getHeight();
	int curPos = area.getX();
	
	float truePixelPerSecond = pixelsPerSecond * zoom;
	float minSecRatio = 1;
	if (len / truePixelPerSecond < 10) {
		minSecRatio = 0.1;
	}
	int numSteps = len / (truePixelPerSecond * minSecRatio);
	if (numSteps > maxLines) {
		minSecRatio *= std::ceil(numSteps / maxLines);
		numSteps = len / (truePixelPerSecond * minSecRatio);
	}
	float pixelStep = truePixelPerSecond * minSecRatio;

	g.setColour(Colours::white);

	DBG("minSecRatio: " << minSecRatio);
	DBG("pixelStep: " << pixelStep);
	DBG("numSteps: " << numSteps);
	DBG("\n\n");

	for (int step = 0; step < numSteps; step++) {
		if (step % freqOfTimeLables == 0) {
			
			g.drawSingleLineText(
				getFormattedSting(step * minSecRatio),
				curPos, height - (lineHeight * 2) - 5,
				Justification::horizontallyCentred);
			g.drawVerticalLine(curPos, height - (lineHeight * 2), height);
		}
		else {
			g.drawVerticalLine(curPos, height - lineHeight, height);
		}
		curPos += pixelStep;
	}
}

juce::String TimelineComponent::getFormattedSting(float valueInSec) {
	int milsec = (int)(valueInSec * 100) % 1000;
	int remainSecs = valueInSec;
	int hours = remainSecs / (60 * 60);
	remainSecs %= (60 * 60);
	int mins = remainSecs / 60;
	remainSecs %= 60;
	char val[20];

	if (hours == 0) {
		if (mins == 0) {
			std::sprintf(val, "%02ds:%03dms", remainSecs, milsec);
		}
		else {
			std::sprintf(val, "%02dm:%02ds:%03dms", mins, remainSecs, milsec);
		}
		
	}
	else {
		std::sprintf(val, "%2dh:%02dm:%02ds:%03dms", hours, mins, remainSecs, milsec);
	}
	
	return juce::String(val);
}
