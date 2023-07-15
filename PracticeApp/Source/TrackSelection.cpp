#include "TrackSelection.h";


TrackSelection::TrackSelection(const double& zoom) :
    zoom(zoom) {}

void TrackSelection::paint(juce::Graphics& g) {
    if (startSelectionPos != -1 && endSelectionPos != -1) {
        float trueStart = std::min(startSelectionPos, endSelectionPos) * zoom;
        float width = std::abs(startSelectionPos - endSelectionPos) * zoom;
        if (width == 0)
            return;
        g.setColour(ProjectColours::Tracks::selectionArea);
        g.fillRect(trueStart, 0.f, width, (float)getHeight());

        g.setColour(ProjectColours::Tracks::selectionBorders);
        g.drawLine(trueStart, 0.0f, trueStart, (float)getHeight(), lineWidth);
        g.drawLine(trueStart + width, 0.0f, trueStart + width, (float)getHeight(), lineWidth);
    }
}

void TrackSelection::setStartOfSelection(float startPos) {
    if (startPos >= 0)
        startSelectionPos = startPos / zoom;
}

void TrackSelection::setEndOfSelection(float endPos) {
    if (endPos >= 0)
        endSelectionPos = endPos / zoom;
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
    return { trueStart * zoom, trueEnd * zoom};
}

void TrackSelection::setSelectedArea(float start, float end) {
    setStartOfSelection(start);
    setEndOfSelection(end);
    repaint();
}



