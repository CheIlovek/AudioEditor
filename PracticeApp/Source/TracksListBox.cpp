#include "TracksListBox.h"
#include "TrackComponent.h"

TracksListBox::TracksListBox(void) : 
	playPosition(&audioMixer, zoomRatio, defaultPixelsBySecond),
	listBox("ListBox", this) {
	formatManager.registerBasicFormats();
	listBox.setColour(ListBox::outlineColourId,		ProjectColours::Tracks::listBoxOutline);
	listBox.setColour(ListBox::backgroundColourId,	ProjectColours::Tracks::listBoxBackground);
	listBox.setOutlineThickness(1);
	listBox.setMultipleSelectionEnabled(false);
	listBox.setRowSelectedOnMouseDown(true);
	addAndMakeVisible(listBox);
	addAndMakeVisible(playPosition);
	listBox.setRowHeight(150);
	//resized();
	
}

TracksListBox::~TracksListBox(void) {
}

int TracksListBox::getNumRows() {
	return dataList.size();
}

void TracksListBox::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) {
	if (rowIsSelected) {
		g.fillAll(ProjectColours::Tracks::listBoxBackground.brighter());
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

void TracksListBox::backgroundClicked(const MouseEvent&)
{
	listBox.deselectAllRows();
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

void TracksListBox::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) {
	auto relEvent = event.getEventRelativeTo(&playPosition);
	if (event.mods.isAltDown() && playPosition.contains(relEvent.getPosition())) {
		DBG("WHEEL WITH ALT SCROLLED");
		zoomRatio += wheel.deltaY * scrollStep;
		for (TrackComponent* comp : dataList) {
			comp->resized();
		}
	}
	
}

void TracksListBox::paint(Graphics& g) {
	g.fillAll(ProjectColours::Tracks::listBoxBackground);
}

void TracksListBox::addNewTrack() {
	auto track = std::make_unique<TrackComponent>(formatManager, *this, dataList.size(), zoomRatio);
	audioMixer.addInputSource(new TrackAudioBuffer(0, 0));
	dataList.add(track.release());
	listBox.updateContent();
	listBox.selectRow(dataList.size() - 1, true, true);
}

void TracksListBox::addNewTrack(juce::File file) {
	auto track = std::make_unique<TrackComponent>(formatManager, *this, dataList.size(), zoomRatio);
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
				int waveformSize = (double)(info.numSamples * defaultPixelsBySecond) / (reader->sampleRate) ;
				DBG("LISTBOX SIZE: " << waveformSize);
				dataList[trackId]->setSource(buffer, reader->sampleRate, waveformSize);
			}
			delete reader;
		}
	}
}

void TracksListBox::setFileOnTrack(juce::File file) {
	int index = listBox.getSelectedRow();
	if (index >= 0)
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

void TracksListBox::setTrackOffset(int trackId, int offsetInPixels) {
	double offsetInSeconds = offsetInPixels / (defaultPixelsBySecond);
	DBG("offsetInSeconds = " << offsetInSeconds);
	audioMixer.setOffset(trackId, offsetInSeconds);
}

bool TracksListBox::applyReverbOnTrack() {
	int trackId = getSelectedRow();
	if (trackId >= 0 && trackId < dataList.size()) {
		auto* curTrack = dataList[trackId];
		if (curTrack->haveSelection()) {
			auto pos = curTrack->getSelectedAreaInPixels();
			int startInSamps = (double)pos.first / defaultPixelsBySecond * audioMixer.getSampleRate();
			int endInSamps = (double)pos.second / defaultPixelsBySecond * audioMixer.getSampleRate();
			audioMixer.applyReverb(trackId, startInSamps, endInSamps);
		}
		else {
			audioMixer.applyReverb(trackId);
		}
		return true;
	}
	return false;
}

void TracksListBox::setStereoBalanceOnTrack(int trackId, float newBalance) {
	audioMixer.setStereoBalanceOnTrack(trackId, newBalance);
}

int TracksListBox::getNumOfSelectedRows()
{
	return listBox.getSelectedRows().size();
}

int TracksListBox::getSelectedRow()
{
	return listBox.getSelectedRow();
}

TrackComponent* TracksListBox::getTrack(int trackId)
{
	return dataList[trackId];
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
