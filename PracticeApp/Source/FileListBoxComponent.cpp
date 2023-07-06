#include "FileListBoxComponent.h"

FileListBoxComponent::FileListBoxComponent()
{
    fileListBox.setModel(this);
    fileListBox.setColour(ListBox::outlineColourId, Colours::white);
    fileListBox.setOutlineThickness(1);
    fileListBox.setRowSelectedOnMouseDown(false);
    fileListBox.setRowSelectedOnMouseDown(true);
    addAndMakeVisible(fileListBox);
    fileListBox.setRowHeight(20);
    resized();
}

FileListBoxComponent::~FileListBoxComponent()
{
}

int FileListBoxComponent::getNumRows()
{
    return fileList.size();
}

void FileListBoxComponent::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    g.fillAll(juce::Colours::darkgrey);
}

Component* FileListBoxComponent::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (rowNumber < 0 || rowNumber >= fileList.size())
        return nullptr;
    return fileList[rowNumber];
}

void FileListBoxComponent::resized(void)
{
    fileListBox.setBounds(getLocalBounds());
}

void FileListBoxComponent::openFile()
{
    chooser = std::make_unique<juce::FileChooser>("Select a Wave file to play...", juce::File{}, "*.wav");     

    auto chooserFlags = juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)    
        {
            auto file = fc.getResult();

            if (file != juce::File{})                                                
            {
                fileList.push_back(new FileComponent(file));
                
                fileListBox.updateContent();
                fileListBox.selectRow(fileList.size() - 1, true, true);
            }
        });
}

File FileListBoxComponent::getFile(int index)
{
    return fileList[index]->getFile();
}

File FileListBoxComponent::getSelectedFile() {
    auto f = fileListBox.getSelectedRow();
    return getFile(f);
}

