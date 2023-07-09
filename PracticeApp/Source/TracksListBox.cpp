#include "TracksListBox.h"
#include "TrackComponent.h"

TracksListBox::TracksListBox(void) : 
	playPosition(&audioMixer, zoomRatio, defaultPixelsBySecond),
	listBox("ListBox", this) {
	formatManager.registerBasicFormats();
	listBox.setColour(juce::ListBox::outlineColourId, Colours::black);
	listBox.setOutlineThickness(1);
	listBox.setMultipleSelectionEnabled(false);
	listBox.setRowSelectedOnMouseDown(true);
	listBox.setColour(ListBox::backgroundColourId, background);
	addAndMakeVisible(listBox);
	addAndMakeVisible(playPosition);
	listBox.setRowHeight(150);
	//resized();
	
}

TracksListBox::~TracksListBox(void) {
	//listBox.setModel(nullptr);
	//listBox.updateContent();
}

int TracksListBox::getNumRows() {
	return dataList.size();
}

void TracksListBox::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) {
	if (rowIsSelected) {
		g.fillAll(background.brighter());
	}
}

Component* TracksListBox::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate) {
	if (rowNumber < 0 || rowNumber >= dataList.size()) {
		return nullptr;
	}
	return dataList[rowNumber];
}

void TracksListBox::resized(void) {
	auto r = getLocalBounds();
	r.setWidth(10000);
	listBox.setBounds(r);
	r.removeFromLeft(100 + 10);
	playPosition.setBounds(r);
}

void TracksListBox::listBoxItemClicked(int row, const MouseEvent& event) {
	listBox.selectRowsBasedOnModifierKeys(row, event.mods, false);
	DBG("ITEM CLICKED DIST: " << event.getDistanceFromDragStartX());
}

void TracksListBox::mouseDown(const MouseEvent& event) {
	for (TrackComponent* comp : dataList) {
		auto relEvent = event.getEventRelativeTo(comp);
		if (comp->contains(relEvent.getMouseDownPosition())) {
			mouseSelected = comp;
			DBG("TRACK DOWNED");
			mouseSelected->mouseDown(event);
			break;
		}
	}
}

void TracksListBox::mouseUp(const MouseEvent& event) {
	if (mouseSelected != nullptr) {
		mouseSelected->mouseUp(event);
		mouseSelected = nullptr;
		DBG("TRACK RELEASED");
	}
	
}

void TracksListBox::mouseDrag(const MouseEvent& event) {
	if (mouseSelected != nullptr) {
		mouseSelected->mouseDrag(event);
	}
}

void TracksListBox::paint(Graphics& g) {
	g.fillAll(background);
}

void TracksListBox::addNewTrack() {
	auto track = std::make_unique<TrackComponent>(formatManager, *this, dataList.size());
	audioMixer.addInputSource(new TrackAudioBuffer(0, 0));
	dataList.add(track.release());
	listBox.updateContent();
	listBox.selectRow(dataList.size() - 1, true, true);
}

void TracksListBox::addNewTrack(juce::File file) {
	auto track = std::make_unique<TrackComponent>(formatManager, *this, dataList.size());
	audioMixer.addInputSource(new TrackAudioBuffer());
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
				auto buffer = new TrackAudioBuffer(reader->numChannels, reader->lengthInSamples);
				AudioSourceChannelInfo info(*buffer);
				reader->read(buffer, 0, reader->lengthInSamples, 0, true, true);
				audioMixer.setSampleRate(reader->sampleRate);
				audioMixer.setInputSource(trackId, buffer);
				DBG("DUR_LISTBOX: " << (double)info.numSamples / reader->sampleRate);
				int waveformSize = (double)(info.numSamples * defaultPixelsBySecond * zoomRatio) / (reader->sampleRate) ;
				DBG("LISTBOX SIZE: " << waveformSize);
				dataList[trackId]->setSource(buffer, reader->sampleRate, waveformSize);
			}
			delete reader;
		}
	}
}

void TracksListBox::setFileOnTrack(juce::File file) {
	setFileOnTrack(listBox.getSelectedRow(),file);
}

void TracksListBox::muteTrack(int trackId) {
	audioMixer.muteTrack(trackId);
}

void TracksListBox::unmuteTrack(int trackId) {
	audioMixer.unmuteTrack(trackId);
}

void TracksListBox::soloTrack(int trackId) {
	audioMixer.soloTrack(trackId);
}

void TracksListBox::setTrackOffset(int trackId, int offset) {
	double offsetInSeconds = offset / (defaultPixelsBySecond * zoomRatio);
	DBG("offsetInSeconds = " << offsetInSeconds);
	audioMixer.setOffset(trackId, offsetInSeconds);
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
