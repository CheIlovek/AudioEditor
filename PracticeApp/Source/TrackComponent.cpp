#include "TrackComponent.h"
#include "TracksListBox.h"

int TrackComponent::TrackNumber = 1;

TrackComponent::TrackComponent(juce::AudioFormatManager& formatManager, TracksListBox& newOwner,int row, const double& zoom) :
	waveformCache(5),
	waveform(512, formatManager, waveformCache),
	volumeSlider(Colours::black),
	owner(newOwner),
	row(row),
	waveformZoom(zoom) {
	trackName.setColour(ProjectColours::textColour);
	trackName.setText("Audio " + std::to_string(TrackNumber));
	TrackNumber++;

	muteButton.setButtonText("MUTE");
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
			muteButton.setColour(juce::TextButton::buttonColourId, ProjectColours::Tracks::buttonColour.darker());
			owner.muteTrack(this->row);
		}
	};

	superiorButton.setButtonText("SOLO");
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
			superiorButton.setColour(juce::TextButton::buttonColourId, ProjectColours::Tracks::buttonColour.darker());
			owner.soloTrack(this->row);
		}
	};


	balanceSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	balanceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	balanceSlider.setColour(Slider::thumbColourId, ProjectColours::Tracks::sliderColour);
	balanceSlider.setBounds(0, 0, 50, 100);
	volumeSlider.setBounds(0, 0, 50, 100);


	addAndMakeVisible(trackName);
	addAndMakeVisible(muteButton);
	addAndMakeVisible(superiorButton);
	addAndMakeVisible(balanceSlider);
	addAndMakeVisible(waveform);
	addAndMakeVisible(volumeSlider);
	addAndMakeVisible(selection);
	resized();

}

TrackComponent::~TrackComponent(void) {
}

void TrackComponent::paint(Graphics& g) {
}

void TrackComponent::resized(void) {

	juce::FlexBox controlsBox;
	controlsBox.flexDirection = juce::FlexBox::Direction::row;
	controlsBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	controlsBox.alignContent = juce::FlexBox::AlignContent::flexStart;
	controlsBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;

	juce::FlexBox leftSideBox;
	leftSideBox.flexDirection = juce::FlexBox::Direction::column;
	leftSideBox.flexWrap = juce::FlexBox::Wrap::wrap;
	leftSideBox.alignContent = juce::FlexBox::AlignContent::flexStart;
	leftSideBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;


	juce::FlexItem trackNameItem(100, 20, trackName);
	juce::FlexItem muteButtonItem(30, 20, muteButton);
	juce::FlexItem superiorButtonItem(30, 20, superiorButton);
	juce::FlexItem balanceSliderItem(50, 70, balanceSlider);
	//balanceSliderItem.maxWidth = 200;
	leftSideBox.items = { trackNameItem, muteButtonItem, superiorButtonItem, balanceSliderItem };
	auto r = getLocalBounds();
	leftSideBox.performLayout(r.removeFromLeft(100));
	volumeSlider.setBounds(r.removeFromLeft(10));
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

void TrackComponent::mouseDown(const juce::MouseEvent& event) {
	DBG("BUTTON PRESSED");
	owner.listBoxItemClicked(row, event);
	if (curState == State::selecting)
		selection.clearSelection();
	if (event.mods.isLeftButtonDown()) {
		auto relEvent = event.getEventRelativeTo(&waveform);
		auto startPoint = event.getMouseDownPosition();
		if (waveform.contains(relEvent.getMouseDownPosition())) {
			DBG("WAVEFORM DOWNED");
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


