#include "DummyComponent.h"

DummyComponent::DummyComponent(void) {
	juce::Random rand;
	colour = juce::Colour::fromRGB(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255));
}

DummyComponent::DummyComponent(Colour colour) : colour(colour) {
}

DummyComponent::~DummyComponent(void) {
}
//
void DummyComponent::paint(Graphics& g) {
	g.fillAll(colour);
}
//
void DummyComponent::resized(void) {
}