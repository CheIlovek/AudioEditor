#include "PlayPositionComponent.h";


PlayPositionComponent::PlayPositionComponent(TracksAudioSource* transportSourceToUse, const double& zoom, const double& pixelsPerSecond) :
    transportSource(transportSourceToUse),
    curZoom(zoom),
    pixelsPerSecond(pixelsPerSecond) {
    startTimer(40);
}

void PlayPositionComponent::paint(juce::Graphics& g) {
    double duration = transportSource->getLengthInSeconds();
    
    if (duration > 0.0) {
        auto audioPosition = (float)transportSource->getCurrentPosition();
        curPos = (audioPosition / duration) * duration * curZoom * pixelsPerSecond;

        g.setColour(ProjectColours::Tracks::playMarker);
        g.drawLine(curPos, 0.0f, curPos, (float)getHeight(), 2.0f);
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

double PlayPositionComponent::getPositionInPixels() {
    return curPos;
}


void PlayPositionComponent::timerCallback() {
    repaint();
}


