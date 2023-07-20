#include "TrackComponent.h"
#include "TracksListBox.h"

int TrackComponent::TrackNumber = 1;

TrackComponent::TrackComponent(juce::AudioFormatManager& formatManager, TracksListBox& newOwner,int row, const double& zoom) :
	waveformCache(5),
	waveform(512, formatManager, waveformCache),
	volumeSlider(Colours::black),
	owner(newOwner),
	row(row),
	waveformZoom(zoom),
	selection(zoom) {
	trackName.setColour(ProjectColours::textColour);
	juce::String audio(RussianText::audio.c_str());
	trackName.setText(audio + ' ' + std::to_string(TrackNumber));
	TrackNumber++;

	muteButton.setButtonText(RussianText::mute.c_str());
	muteButton.setColour(TextButton::buttonColourId,	ProjectColours::Tracks::buttonColour);
	muteButton.setColour(TextButton::buttonOnColourId,	ProjectColours::Tracks::buttonColour);
	muteButton.setColour(TextButton::textColourOffId,	ProjectColours::textColour);
	muteButton.setColour(TextButton::textColourOnId,	ProjectColours::textColour);
	muteButton.setAlpha(1.0f);
	muteButton.setEnabled(true);
	muteButton.setClickingTogglesState(true);
	muteButton.setToggleState(true, juce::dontSendNotification);
	muteButton.onClick = [this] {
		if (muteButton.getToggleState()) {
			muteButton.setColour(juce::TextButton::buttonColourId, ProjectColours::Tracks::buttonColour);
			owner.unmuteTrack(this->row);
		}
		else {
			muteButton.setColour(juce::TextButton::buttonColourId, ProjectColours::Tracks::muteButtonActiveColour);
			owner.muteTrack(this->row);
		}
	};

	superiorButton.setButtonText(RussianText::solo.c_str());
	superiorButton.setColour(TextButton::buttonColourId,	ProjectColours::Tracks::buttonColour);
	superiorButton.setColour(TextButton::buttonOnColourId,	ProjectColours::Tracks::buttonColour);
	superiorButton.setColour(TextButton::textColourOffId,	ProjectColours::textColour);
	superiorButton.setColour(TextButton::textColourOnId,	ProjectColours::textColour);
	superiorButton.setEnabled(true);
	superiorButton.setClickingTogglesState(true);
	superiorButton.setToggleState(true, juce::dontSendNotification);
	superiorButton.onClick = [this] {
		if (superiorButton.getToggleState()) {
			superiorButton.setColour(juce::TextButton::buttonColourId, ProjectColours::Tracks::buttonColour);
			owner.soloTrack(-1);
		}
		else {
			superiorButton.setColour(juce::TextButton::buttonColourId, ProjectColours::Tracks::superiorButtonActiveColour);
			owner.soloTrack(this->row);
		}
	};


	balanceSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	balanceSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 20);
	balanceSlider.setRange(-1, 1);
	balanceSlider.setValue(0);
	balanceSlider.addListener(this);
	balanceSlider.setColour(Slider::thumbColourId, ProjectColours::Tracks::sliderColour);
	balanceSlider.setBounds(0, 0, 100, 100);
	balanceSlider.setLookAndFeel(&balanceLaf);
	volumeSlider.setBounds(0, 0, 50, 100);


	addAndMakeVisible(trackName);
	addAndMakeVisible(muteButton);
	addAndMakeVisible(superiorButton);
	addAndMakeVisible(balanceSlider);
	addAndMakeVisible(waveform);
	//addAndMakeVisible(volumeSlider);
	addAndMakeVisible(selection);
	resized();

}

TrackComponent::~TrackComponent(void) {
}

void TrackComponent::paint(Graphics& g) {
	auto area = getLocalBounds();
	area.removeFromLeft(110);
	area = area.removeFromTop(audioFilenameHeight);
	g.setColour(ProjectColours::Tracks::filenameBackground);
	g.fillRect(area);
	g.setColour(ProjectColours::Tracks::filenameText);
	g.drawSingleLineText(audioFilename, area.getX(), area.getHeight()-2);
	g.setColour(Colours::black);
	g.drawHorizontalLine(getHeight()-1, 0, 110);
}

void TrackComponent::resized(void) {

	juce::FlexBox leftSideBox;
	leftSideBox.flexDirection = juce::FlexBox::Direction::column;
	leftSideBox.flexWrap = juce::FlexBox::Wrap::wrap;
	leftSideBox.alignContent = juce::FlexBox::AlignContent::flexStart;
	leftSideBox.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;


	juce::FlexItem trackNameItem(100, 20, trackName);
	juce::FlexItem muteButtonItem(30, 20, muteButton);
	juce::FlexItem superiorButtonItem(30, 20, superiorButton);
	juce::FlexItem balanceSliderItem(70, 70, balanceSlider);

	trackNameItem.margin =		FlexItem::Margin::Margin(0, 0, 0, 5);
	muteButtonItem.margin =		FlexItem::Margin::Margin(0, 0, 0, 5);
	superiorButtonItem.margin = FlexItem::Margin::Margin(0, 0, 0, 5);
	balanceSliderItem.margin =	FlexItem::Margin::Margin(0, 0, 5, 0);

	superiorButtonItem.maxWidth = 70;
	muteButtonItem.maxWidth = 70;
	
	balanceSliderItem.alignSelf = FlexItem::AlignSelf::center;
	balanceSliderItem.maxWidth = 80;
	balanceSliderItem.minWidth = 80;
	balanceSliderItem.maxHeight = 80;
	balanceSliderItem.minHeight = 80;
	leftSideBox.items = { trackNameItem, muteButtonItem, superiorButtonItem, balanceSliderItem };
	auto r = getLocalBounds();
	leftSideBox.performLayout(r.removeFromLeft(110));
	//volumeSlider.setBounds(r.removeFromLeft(10));
	r.removeFromTop(audioFilenameHeight);
	selection.setBounds(r);
	r.setBounds(r.getX() + (waveformOffset * waveformZoom), r.getY(), waveformSize * waveformZoom, r.getHeight());
	waveform.setBounds(r);
	
}

void TrackComponent::setSource(TrackAudioBuffer* buffer, double sampleRate, int wavefromSize) {
	waveform.setSource(buffer, sampleRate);
	this->waveformSize = wavefromSize;
	resized();
}

void TrackComponent::clear() {
	waveform.clear();
}

void TrackComponent::setRow(int newRow) {
	row = newRow;
}

void TrackComponent::setWaveformSize(int newSize) {
	waveformSize = newSize;
}

void TrackComponent::setWaveformOffset(int newOffset) {
	waveformOffset = newOffset;
}

int TrackComponent::getRow() {
	return row;
}

String TrackComponent::getTrackName()
{
	return trackName.getText();
}

float TrackComponent::getWaveformSize()
{
	return waveformSize * waveformZoom;
}

float TrackComponent::getWaveformOffset() {
	return waveformOffset;
}

float TrackComponent::getTrueWaveformOffset() {
	return waveformOffset * waveformZoom;
}

void TrackComponent::mouseDown(const juce::MouseEvent& event) {
	owner.listBoxItemClicked(row, event);
	if (curState == State::selecting)
		selection.clearSelection();
	if (event.mods.isLeftButtonDown()) {
		auto relEvent = event.getEventRelativeTo(&waveform);
		auto startPoint = event.getMouseDownPosition();
		if (waveform.contains(relEvent.getMouseDownPosition())) {
			curState = State::dragging;
			oldWaveformOffset = waveformOffset;
		}
	}
	else if (event.mods.isRightButtonDown()) {
		curState = State::selecting;
		selection.setStartOfSelection(event.position.x);
	}
	

}

void TrackComponent::mouseDrag(const MouseEvent& event) {
	int newOffset;
	switch (curState) {
	case TrackComponent::selecting:
		selection.setEndOfSelection(event.position.x);
		break;
	case TrackComponent::dragging:
		newOffset = oldWaveformOffset + event.getDistanceFromDragStartX() / waveformZoom;
		waveformOffset = std::max(0, newOffset);
		resized();
		break;
	}
	
}

void TrackComponent::mouseUp(const MouseEvent& event) {
	switch (curState) {
	case TrackComponent::selecting:
		selection.setEndOfSelection(event.position.x);
		break;
	case TrackComponent::dragging:
		if (oldWaveformOffset != waveformOffset)
			owner.setTrackOffset(row, waveformOffset);
		curState = State::none;
		break;
	}
	
}

bool TrackComponent::haveSelection() {
	return selection.isAreaSelected();
}

std::pair<float, float> TrackComponent::getSelectedAreaInPixels() {
	auto pos = selection.getSelectedArea();
	pos.first /= waveformZoom;
	pos.first -= waveformOffset;
	
	pos.second /= waveformZoom;
	pos.second -= waveformOffset;

	pos.first = std::max(pos.first, 0.f);
	pos.second = std::min(pos.second, (float)waveformSize);

	return pos;
}

void TrackComponent::setSelectedAreaInPixels(float start, float end) {
	selection.setSelectedArea(start, end);
}

void TrackComponent::selectAll(bool selectOnlyOnWaveform) {
	if (selectOnlyOnWaveform) {
		float offset = waveformOffset * waveformZoom;
		float size = waveformSize * waveformZoom;
		selection.setSelectedArea(offset, offset + size);
	}
	else {
		selection.setSelectedArea(0, selection.getWidth());
	}
}

void TrackComponent::selectAllBefore(float end, bool selectOnlyOnWaveform) {
	if (selectOnlyOnWaveform) {
		float offset = waveformOffset * waveformZoom;
		float size = waveformSize * waveformZoom;
		if (offset < end) {
			end = std::min(offset + size, end);
			selection.setSelectedArea(offset, end);
		}
	}
	else {
		selection.setSelectedArea(0, end);
	}
}

void TrackComponent::selectAllAfter(float start, bool selectOnlyOnWaveform) {
	if (selectOnlyOnWaveform) {
		float offset = waveformOffset * waveformZoom;
		float size = waveformSize * waveformZoom;
		if (start < offset + size) {
			start = std::max(offset, start);
			selection.setSelectedArea(start, offset + size);
		}
	}
	else {
		selection.setSelectedArea(start, selection.getWidth());
	}
}

void TrackComponent::sliderValueChanged(juce::Slider* slider) {
	if (slider == &balanceSlider) {
		owner.setStereoBalanceOnTrack(row,balanceSlider.getValue());
	}
}


void TrackComponent::setAudioFilename(juce::String str) {
	audioFilename = str;
}

void TrackComponent::muteButtonClicked()
{
	muteButton.triggerClick();
}

void TrackComponent::superiorButtonClicked()
{
	superiorButton.triggerClick();
}

void TrackComponent::setSoloButtonState(bool state) {
	superiorButton.setToggleState(state,dontSendNotification);
}

