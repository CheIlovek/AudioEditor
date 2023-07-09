#include "TrackComponent.h"
#include "TracksListBox.h"

TrackComponent::TrackComponent(juce::AudioFormatManager& formatManager, TracksListBox& newOwner,int row) :
	waveformCache(5),
	waveform(512, formatManager, waveformCache),
	volumeSlider(Colours::black),
	owner(newOwner),
	row(row) {
	trackName.setColour(textColour);
	trackName.setText("Audio 1");

	muteButton.setButtonText("MUTE");
	muteButton.setColour(juce::TextButton::buttonColourId, buttonColour);
	muteButton.setColour(juce::TextButton::buttonOnColourId, buttonColour);
	muteButton.setColour(juce::TextButton::ColourIds::textColourOffId, textColour);
	muteButton.setColour(juce::TextButton::textColourOnId, textColour);
	muteButton.setAlpha(1.0f);
	muteButton.setEnabled(true);
	muteButton.setClickingTogglesState(true);
	muteButton.setToggleState(false, juce::dontSendNotification);
	muteButton.onClick = [this] {
		if (muteButton.getToggleState()) {
			muteButton.setColour(juce::TextButton::buttonColourId, buttonColour);
			owner.unmuteTrack(this->row);
		}
		else {
			muteButton.setColour(juce::TextButton::buttonColourId, buttonColour.darker());
			owner.muteTrack(this->row);
		}
	};

	superiorButton.setButtonText("SOLO");
	superiorButton.setColour(juce::TextButton::buttonColourId, buttonColour);
	superiorButton.setEnabled(true);
	superiorButton.setClickingTogglesState(true);
	superiorButton.setToggleState(false, juce::dontSendNotification);
	superiorButton.onClick = [this] {
		if (superiorButton.getToggleState()) {
			superiorButton.setColour(juce::TextButton::buttonColourId, buttonColour);
			owner.soloTrack(-1);
		}
		else {
			superiorButton.setColour(juce::TextButton::buttonColourId, buttonColour.darker());
			owner.soloTrack(this->row);
		}
	};


	balanceSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	balanceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	balanceSlider.setColour(Slider::thumbColourId, sliderColour);
	balanceSlider.setBounds(0, 0, 50, 100);
	volumeSlider.setBounds(0, 0, 50, 100);


	addAndMakeVisible(trackName);
	addAndMakeVisible(muteButton);
	addAndMakeVisible(superiorButton);
	addAndMakeVisible(balanceSlider);
	addAndMakeVisible(waveform);
	addAndMakeVisible(volumeSlider);

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
	r.setBounds(r.getX() + waveformOffset, r.getY(), waveformSize, r.getHeight());
	waveform.setBounds(r);

	//juce::FlexItem leftSideBoxItem(100, getHeight(), leftSideBox);
	//juce::FlexItem volumeSliderItem(10, getHeight(), volumeSlider);
	//juce::FlexItem waveformItem(getWidth(), getHeight(), waveform);
	//controlsBox.items = { leftSideBoxItem, volumeSliderItem, waveformItem };

	//controlsBox.performLayout(getBounds());

}

void TrackComponent::setSource(TrackAudioBuffer* buffer, double sampleRate, int wavefromSize) {
	waveform.setSource(buffer, sampleRate);
	this->waveformSize = wavefromSize;
	resized();
}

void TrackComponent::clear() {
	waveform.clear();
}

void TrackComponent::mouseDown(const juce::MouseEvent& event) {
	owner.listBoxItemClicked(row, event);
	auto relEvent = event.getEventRelativeTo(&waveform);
	auto startPoint = event.getMouseDownPosition();
	if (waveform.contains(relEvent.getMouseDownPosition())) {
		DBG("WAVEFORM DOWNED");
		isDraggingWaveform = true;
		oldWaveformOffset = waveformOffset;
	}

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

void TrackComponent::mouseDrag(const MouseEvent& event) {
	if (isDraggingWaveform) {
		waveformOffset = std::max(0, oldWaveformOffset + event.getDistanceFromDragStartX());
		resized();
	}
	DBG("DRAG DIST: " << event.getMouseDownX() << " " << event.getMouseDownY());
}

void TrackComponent::mouseUp(const MouseEvent& event) {
	DBG("WAVEFORM RELEASED");
	owner.setTrackOffset(row, waveformOffset);
	isDraggingWaveform = false;
}
