#include "TrackSelection.h";


TrackSelection::TrackSelection() {}

void TrackSelection::paint(juce::Graphics& g) {
    if (startSelectionPos != -1 && endSelectionPos != -1) {
        float trueStart = std::min(startSelectionPos, endSelectionPos);
        float width = std::abs(startSelectionPos - endSelectionPos);
        if (width == 0)
            return;
        g.setColour(ProjectColours::Tracks::selectionArea);
        g.fillRect(trueStart, 0.f, width, (float)getHeight());

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
    endSelectionPos = -1;

}

bool TrackSelection::isAreaSelected() {
    return startSelectionPos != -1.f && endSelectionPos != -1.f;
}

std::pair<float, float> TrackSelection::getSelectedArea() {
    float trueStart = std::min(startSelectionPos, endSelectionPos);
    float trueEnd = std::max(startSelectionPos, endSelectionPos);
    return { trueStart, trueEnd };
}

void TrackSelection::setSelectedArea(float start, float end) {
    setStartOfSelection(start);
    setEndOfSelection(end);
}



