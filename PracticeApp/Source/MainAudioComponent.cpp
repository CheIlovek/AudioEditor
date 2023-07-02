#include "../Include/MainAudioComponent.h"

MainAudioComponent::MainAudioComponent(void) {
	addAndMakeVisible(dummy);

}

MainAudioComponent::~MainAudioComponent(void) {
}
//
void MainAudioComponent::paint(Graphics& g) {
	g.fillAll(juce::Colours::black);
	

}
//
void MainAudioComponent::resized(void) {
	auto area = getLocalBounds();
	dummy.setBounds(area.removeFromTop(getHeight() * 0.3));
}