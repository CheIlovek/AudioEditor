#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
class FilesTableComponent : public Component, public TableListBoxModel {
public:
    FilesTableComponent(void);
    ~FilesTableComponent(void) override;

    void paint(Graphics&) override;
    void resized(void) override;

    int getNumRows();
    void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    int getColumnAutoSizeWidth(int columnId) override;
    void sortOrderChanged(int newSortColumnId, bool isForwards) override;

private:
    juce::TableListBox table{ {}, this };
    juce::Font font;
    int numRows = 0;
    juce::XmlElement* dataList;

    juce::String getAttributeNameForColumnId(const int columnId) const;
    void loadData(juce::File tableFile);
};


