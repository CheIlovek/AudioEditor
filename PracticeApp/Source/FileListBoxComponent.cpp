#include "FileListBoxComponent.h"

FileListBoxComponent::FileListBoxComponent()
{
    fileListBox.setModel(this);
    fileListBox.setRowSelectedOnMouseDown(true);

    addAndMakeVisible(fileListBox);
    addAndMakeVisible(&name);
    addAndMakeVisible(&added);
    name.setText(RussianText::name.c_str());
    added.setText(RussianText::added.c_str());
    name.setColour(ProjectColours::textColour);
    added.setColour(ProjectColours::textColour);
    name.setFontHeight(16);
    added.setFontHeight(16);
    fileListBox.setRowHeight(20);
    fileListBox.setColour(ListBox::backgroundColourId,          Colour(0));
    fileListBox.setColour(ListBox::ColourIds::outlineColourId,  ProjectColours::Files::listBoxOutline);
    fileListBox.setOutlineThickness(1);
    
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
        g.fillAll(ProjectColours::Files::fileRowBackgroundSelected);
    else
        g.fillAll(ProjectColours::Files::fileRowBackgroundUnselected);
}

Component* FileListBoxComponent::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (rowNumber < 0 || rowNumber >= fileList.size())
        return nullptr;
    return fileList[rowNumber];
}

void FileListBoxComponent::listBoxItemClicked(int row, const MouseEvent& event)
{
    DBG("clicked");
    backgroundClicked(event);
    fileListBox.selectRow(row);
    repaint();
}

void FileListBoxComponent::backgroundClicked(const MouseEvent&)
{
    if (fileListBox.getNumSelectedRows() == 1)
    {
        fileList[fileListBox.getSelectedRow()]->deselect();
    }

    fileListBox.deselectAllRows();
}

void FileListBoxComponent::resized(void)
{
    double textProportion = 0.75;
    double toggleProportion = 1 - textProportion;
    int headersHeight = 20;
    int margin = 5;

    name.setBounds(margin, margin, getWidth() * textProportion - margin, headersHeight);
    Rectangle<float> nameBoundingBoxRectangle(name.getX(), name.getY(), name.getWidth(), name.getHeight());
    name.setBoundingBox(Parallelogram<float>(nameBoundingBoxRectangle));

    added.setBounds(getWidth() * textProportion, margin, getWidth() * toggleProportion, headersHeight);
    Rectangle<float> addedBoundingBoxRectangle(added.getX(), added.getY(), added.getWidth(), added.getHeight());
    added.setBoundingBox(Parallelogram<float>(addedBoundingBoxRectangle));

    fileListBox.setBounds(margin, headersHeight + 2 * margin, getWidth() - margin, getHeight() - (headersHeight + 2 * margin));
}

void FileListBoxComponent::paint(Graphics& g)
{
    if (fileList.isEmpty()) {
        g.fillAll(ProjectColours::Files::listBoxNoFileBackground);
        g.setColour(ProjectColours::Files::listBoxNoFileText);
        auto area = getLocalBounds();
        g.drawMultiLineText(
            RussianText::noFileInList.c_str(),
            area.getX(),
            area.getCentreY(),
            area.getWidth(),
            Justification::horizontallyCentred,
            0.4f);
    }
    else {
        g.fillAll(ProjectColours::Files::listBoxBackground);
    }

    
}

void FileListBoxComponent::openFile()
{
    chooser = std::make_unique<juce::FileChooser>("Select an audio file to open...", juce::File{}, "*.wav,*.mp3");     

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
                if (fileListBox.getNumSelectedRows() == 1)
                {
                    fileList[fileListBox.getSelectedRow()]->deselect();
                }
                fileListBox.selectRow(fileList.size() - 1, true, true);
                repaint();
            }
        });
}

void FileListBoxComponent::saveFile(AudioSource* source, int numSamples, int numChannels, int sampleRate) {
    chooser = std::make_unique<juce::FileChooser>("Select a path to save...", juce::File{}, "*.wav");

    auto chooserFlags = juce::FileBrowserComponent::saveMode
        | juce::FileBrowserComponent::canSelectFiles;
    chooser->launchAsync(chooserFlags, [source, numSamples, numChannels, sampleRate](const juce::FileChooser& fc) {
        auto file = fc.getResult();

        if (file != juce::File{}) {
            auto stream = file.createOutputStream();
            WavAudioFormat format;
            auto a = format.createWriterFor(stream.get(), sampleRate, numChannels,32,"", 0); // Нужны метаданныеееее
            a->writeFromAudioSource(*source, numSamples);
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

void FileListBoxComponent::selectedFileAdded()
{
    auto index = fileListBox.getSelectedRow();
    fileList[index]->fileAdded();
}

int FileListBoxComponent::getSelectedRow()
{
    return fileListBox.getSelectedRow();
}

