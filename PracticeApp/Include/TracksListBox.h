#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackComponent.h"
class TracksListBox : public ListBoxModel, public Component {
public:
    TracksListBox(void);
    ~TracksListBox(void) override;

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate);
    void resized(void) override;

    //void addElement(Component*);


private:
    juce::ListBox listBox;
    std::vector<TrackComponent*> dataList;

};


