#include "PlayPositionComponent.h";


PlayPositionComponent::PlayPositionComponent(TracksAudioSource* transportSourceToUse, int& zoom, const double& pixelsPerSecond) :
    transportSource(transportSourceToUse),
    curZoom(zoom),
    pixelsPerSecond(pixelsPerSecond) {
    startTimer(40);
}

void PlayPositionComponent::paint(juce::Graphics& g) {
    double duration = transportSource->getLengthInSeconds();

    if (duration > 0.0) {
        auto audioPosition = (float)transportSource->getCurrentPosition();
        auto drawPosition = (audioPosition / duration) * duration * curZoom * pixelsPerSecond;

        g.setColour(juce::Colours::green);
        g.drawLine(drawPosition, 0.0f, drawPosition, (float)getHeight(), 2.0f);
    }
}

void PlayPositionComponent::mouseDown(const juce::MouseEvent& event) {
    auto duration = transportSource->getLengthInSeconds();

    if (duration > 0.0) {
        auto clickPosition = event.position.x;
        auto audioPosition = (clickPosition / (duration *curZoom * pixelsPerSecond)) * duration;

        transportSource->setPosition(audioPosition);
    }
    getParentComponent()->mouseDown(event);
}

void PlayPositionComponent::mouseDrag(const MouseEvent& event) {
    getParentComponent()->mouseDrag(event);
}

void PlayPositionComponent::mouseUp(const MouseEvent& event) {
    getParentComponent()->mouseUp(event);
}


void PlayPositionComponent::timerCallback() {
    repaint();
}


