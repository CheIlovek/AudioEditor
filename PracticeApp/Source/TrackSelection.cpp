#include "TrackSelection.h";


TrackSelection::TrackSelection(const double& zoom, const double& pixelsPerSecond) :
    curZoom(zoom),
    pixelsPerSecond(pixelsPerSecond) {

}

void TrackSelection::paint(juce::Graphics& g) {
    if (startSelectionPos != -1) {
        float width = startSelectionPos - endSelectionPos;
        g.setColour(ProjectColours::Tracks::selectionArea);
        g.drawRect(startSelectionPos, 0.f, width, (float)getHeight());

        g.setColour(ProjectColours::Tracks::selectionBorders);
        g.drawLine(startSelectionPos, 0.0f, startSelectionPos, (float)getHeight(), lineWidth);
        g.drawLine(endSelectionPos, 0.0f, endSelectionPos, (float)getHeight(), lineWidth);
    }
}

void TrackSelection::setStartOfSelection(float startPos) {
    if (startPos > 0)
        startSelectionPos = startPos;
}

void TrackSelection::setEndOfSelection(float endPos) {
    if (endPos > 0)
        endSelectionPos = endPos;
}

void TrackSelection::clearSelection() {
    startSelectionPos = -1;

}

std::pair<float, float> TrackSelection::getSelectedArea() {
    return { startSelectionPos, endSelectionPos };
}

void TrackSelection::setSelectedArea(float start, float end) {
    setStartOfSelection(start);
    setEndOfSelection(end);
}



