#include "FilesTableComponent.h"

FilesTableComponent::TableTutorialComponent() {
    const auto callback = [this](const juce::FileChooser& chooser) {
        loadData(chooser.getResult());                                             // [1]

        addAndMakeVisible(table);                                                  // [1]

        table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey);      // [2]
        table.setOutlineThickness(1);

        if (columnList != nullptr) {
            for (auto* columnXml : columnList->getChildIterator()) {
                table.getHeader().addColumn(columnXml->getStringAttribute("name"), // [2]
                    columnXml->getIntAttribute("columnId"),
                    columnXml->getIntAttribute("width"),
                    50,
                    400,
                    juce::TableHeaderComponent::defaultFlags);
            }
        }

        table.getHeader().setSortColumnId(1, true);                                // [3]

        table.setMultipleSelectionEnabled(true);                                   // [4]

        resized();
    };

    fileChooser.launchAsync(juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles,
        callback);
}

int FilesTableComponent::getNumRows() {
    return numRows;
}

void FilesTableComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) {
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void FilesTableComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId,
    int width, int height, bool rowIsSelected) override {
    g.setColour(rowIsSelected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));  // [5]
    g.setFont(font);

    if (auto* rowElement = dataList->getChildElement(rowNumber)) {
        auto text = rowElement->getStringAttribute(getAttributeNameForColumnId(columnId));

        g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);                             // [6]
    }

    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);                                                                               // [7]
}

void FilesTableComponent::sortOrderChanged(int newSortColumnId, bool isForwards) {
    if (newSortColumnId != 0) {
        TutorialDataSorter sorter(getAttributeNameForColumnId(newSortColumnId), isForwards);
        dataList->sortChildElements(sorter);

        table.updateContent();
    }
}

Component* FilesTableComponent::refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/,
    Component* existingComponentToUpdate)  {
    if (columnId == 9)  // [8]
    {
        auto* selectionBox = static_cast<SelectionColumnCustomComponent*> (existingComponentToUpdate);

        if (selectionBox == nullptr)
            selectionBox = new SelectionColumnCustomComponent(*this);

        selectionBox->setRowAndColumn(rowNumber, columnId);
        return selectionBox;
    }

    if (columnId == 8)  // [9]
    {
        auto* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);

        if (textLabel == nullptr)
            textLabel = new EditableTextCustomComponent(*this);

        textLabel->setRowAndColumn(rowNumber, columnId);
        return textLabel;
    }

    jassert(existingComponentToUpdate == nullptr);
    return nullptr;     // [10]
}

int FilesTableComponent::getColumnAutoSizeWidth(int columnId)  {
    if (columnId == 9)
        return 50;

    int widest = 32;

    for (auto i = getNumRows(); --i >= 0;) {
        if (auto* rowElement = dataList->getChildElement(i)) {
            auto text = rowElement->getStringAttribute(getAttributeNameForColumnId(columnId));

            widest = juce::jmax(widest, font.getStringWidth(text));
        }
    }

    return widest + 8;
}

int FilesTableComponent::getSelection(const int rowNumber) const {
    return dataList->getChildElement(rowNumber)->getIntAttribute("Select");
}

void FilesTableComponent::setSelection(const int rowNumber, const int newSelection) {
    dataList->getChildElement(rowNumber)->setAttribute("Select", newSelection);
}

juce::String FilesTableComponent::getText(const int columnNumber, const int rowNumber) const {
    return dataList->getChildElement(rowNumber)->getStringAttribute(getAttributeNameForColumnId(columnNumber));
}

void FilesTableComponent::setText(const int columnNumber, const int rowNumber, const juce::String& newText) {
    const auto& columnName = table.getHeader().getColumnName(columnNumber);
    dataList->getChildElement(rowNumber)->setAttribute(columnName, newText);
}

//==============================================================================
void FilesTableComponent::resized() {
    table.setBoundsInset(juce::BorderSize<int>(8));
}