#include "PlayPositionComponent.h";


PlayPositionComponent::PlayPositionComponent(TracksAudioSource* transportSourceToUse)
    : transportSource(transportSourceToUse) {
    startTimer(40);
}

void PlayPositionComponent::paint(juce::Graphics& g) {
    auto duration = (float)transportSource->getLengthInSeconds();

    if (duration > 0.0) {
        auto audioPosition = (float)transportSource->getCurrentPosition();
        auto drawPosition = (audioPosition / duration) * (float)getWidth();

        g.setColour(juce::Colours::green);
        g.drawLine(drawPosition, 0.0f, drawPosition, (float)getHeight(), 2.0f);
    }
}

void PlayPositionComponent::mouseDown(const juce::MouseEvent& event) {
    auto duration = transportSource->getLengthInSeconds();

    if (duration > 0.0) {
        auto clickPosition = event.position.x;
        auto audioPosition = (clickPosition / (float)getWidth()) * duration;

        transportSource->setPosition(audioPosition);
    }
}


void PlayPositionComponent::timerCallback() {
    repaint();
}


