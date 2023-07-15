#include "PlayTimerComponent.h"

PlayTimerComponent::PlayTimerComponent(TracksAudioSource* transportSourceToUse) :
	transportSource(transportSourceToUse) {
	startTimer(40);
}

void PlayTimerComponent::paint(juce::Graphics& g) {
	auto area = getLocalBounds();
	g.setColour(ProjectColours::Playback::Timer::boxBackground);
	g.fillRect(area);

	g.setColour(ProjectColours::Playback::Timer::boxOutline);
	g.drawRect(area);

	g.setColour(ProjectColours::Playback::Timer::text);
	g.setFont(Font(35));
	g.drawFittedText(
		getTime(),
		area,
		Justification::centred,
		1
	);
	//g.drawSingleLineText(
	//	getTime(),
	//	0,
	//	area.getHeight()
	//);
}

void PlayTimerComponent::timerCallback() {
	repaint();
}

juce::String PlayTimerComponent::getTime() {
	double valueInSec = transportSource->getCurrentPosition();
	int milsec = (int)(valueInSec * 100) % 1000;
	int remainSecs = valueInSec;
	int hours = remainSecs / (60 * 60);
	remainSecs %= (60 * 60);
	int mins = remainSecs / 60;
	remainSecs %= 60;
	char val[20];

	std::sprintf(val, "%2dh:%02dm:%02ds:%03dms", hours, mins, remainSecs, milsec);

	return juce::String(val);
}
