#include "TracksListBox.h"
#include "TrackComponent.h"

TracksListBox::TracksListBox(void) : listBox("ListBox", this) {
	formatManager.registerBasicFormats();
	listBox.setColour(juce::ListBox::outlineColourId, Colours::darkgreen);
	listBox.setOutlineThickness(1);
	listBox.setMultipleSelectionEnabled(false);
	listBox.setRowSelectedOnMouseDown(true);
	listBox.setColour(ListBox::backgroundColourId, background);
	addAndMakeVisible(listBox);
	listBox.setRowHeight(150);
	resized();
}

TracksListBox::~TracksListBox(void) {
}

int TracksListBox::getNumRows() {
	return dataList.size();
}

void TracksListBox::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) {
	if (rowIsSelected) {
		g.fillAll(juce::Colours::blue);
	}
	else {
		g.fillAll(juce::Colours::red);
	}
}

Component* TracksListBox::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate) {
	if (rowNumber < 0 || rowNumber >= dataList.size()) {
		return nullptr;
	}
	return dataList[rowNumber];
}

void TracksListBox::resized(void) {
	listBox.setBounds(getLocalBounds());
}

void TracksListBox::addNewTrack() {
	auto track = std::make_unique<TrackComponent>(formatManager);
	audioMixer.addInputSource(new AudioSampleBuffer(0, 0));
	dataList.add(track.release());
	listBox.updateContent();
	listBox.selectRow(dataList.size() - 1, true, true);
}

void TracksListBox::addNewTrack(juce::File file) {
	auto track = std::make_unique<TrackComponent>(formatManager);
	audioMixer.addInputSource(new AudioSampleBuffer());
	dataList.add(track.release());
	setFileOnTrack(dataList.size() - 1, file);
	listBox.updateContent();
	listBox.selectRow(dataList.size() - 1, true, true);

}

void TracksListBox::setFileOnTrack(int trackId, juce::File file) {
	if (trackId >= 0 && trackId < dataList.size()) {
		if (file != juce::File{}) {
			auto* reader = formatManager.createReaderFor(file);
			if (reader != nullptr) {
				auto buffer = new AudioBuffer<float>(reader->numChannels, reader->lengthInSamples);
				AudioSourceChannelInfo info(*buffer);
				reader->read(buffer, 0, reader->lengthInSamples, 0, true, true);
				audioMixer.setInputSource(trackId, buffer);
				dataList[trackId]->setSource(buffer, reader->sampleRate);
			}
			delete reader;
		}
	}
}

void TracksListBox::setFileOnTrack(juce::File file) {
	setFileOnTrack(listBox.getSelectedRow(),file);
}

void TracksListBox::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
	audioMixer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void TracksListBox::releaseResources() {
	audioMixer.releaseResources();
}

void TracksListBox::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
	if (dataList.isEmpty())
		bufferToFill.clearActiveBufferRegion();
	else
		audioMixer.getNextAudioBlock(bufferToFill);

}


TracksAudioSource& TracksListBox::getAudioSource() {
	return audioMixer;
}
