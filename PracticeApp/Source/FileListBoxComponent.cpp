#include "FileListBoxComponent.h"

FileListBoxComponent::FileListBoxComponent()
{
    fileListBox.setModel(this);
    fileListBox.setOutlineThickness(1);
    fileListBox.setRowSelectedOnMouseDown(true);

    addAndMakeVisible(fileListBox);
    addAndMakeVisible(&name);
    addAndMakeVisible(&added);

    name.setText("Name");
    added.setText("Added");
    name.setColour(ProjectColours::textColour);
    added.setColour(ProjectColours::textColour);
    name.setFontHeight(16);
    added.setFontHeight(16);
    fileListBox.setRowHeight(20);
    fileListBox.setColour(ListBox::backgroundColourId, ProjectColours::Files::listBoxBackground);
    
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
    if (rowIsSelected)
        g.fillAll(Colours::grey);
    else
        g.fillAll(ProjectColours::Files::fileRowBackground);
}

Component* FileListBoxComponent::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (rowNumber < 0 || rowNumber >= fileList.size())
        return nullptr;
    return fileList[rowNumber];
}

void FileListBoxComponent::listBoxItemClicked(int row, const MouseEvent&)
{
    DBG("clicked");
    fileListBox.selectRow(row);
    repaint();
}

void FileListBoxComponent::backgroundClicked(const MouseEvent&)
{
    fileListBox.deselectAllRows();
}

void FileListBoxComponent::resized(void)
{
    name.setBounds(5, 0, getWidth() * 0.8 - 5, 20);
    added.setBounds(getWidth() * 0.8, 0, getWidth() * 0.2, 20);
    fileListBox.setBounds(0, 20, getWidth(), getHeight() - 20);
}

void FileListBoxComponent::paint(Graphics& g)
{
    g.fillAll(ProjectColours::Files::listBoxBackground);
}

void FileListBoxComponent::openFile()
{
    chooser = std::make_unique<juce::FileChooser>("Select a Wave file to play...", juce::File{}, "*.wav,*.mp3");     

    auto chooserFlags = juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)    
        {
            auto file = fc.getResult();

            if (file != juce::File{})                                                
            {
                auto fileComponent = std::make_unique<FileComponent>(file, *this, fileList.size());

                fileList.add(fileComponent.release());
                
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

int FileListBoxComponent::getNumOfSelectedRows()
{
    return fileListBox.getSelectedRows().size();
}

