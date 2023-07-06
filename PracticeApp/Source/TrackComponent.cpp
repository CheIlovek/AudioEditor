#include "TrackComponent.h"

TrackComponent::TrackComponent(juce::AudioFormatManager& formatManager) :
	waveformCache(5),
	waveform(512, formatManager, waveformCache),
	volumeSlider(Colours::black) {
	trackName.setColour(textColour);
	trackName.setText("Audio 1");

	muteButton.setButtonText("MUTE");
	muteButton.setColour(juce::TextButton::buttonColourId, buttonColour);
	muteButton.setColour(juce::TextButton::buttonOnColourId, buttonColour);
	muteButton.setColour(juce::TextButton::ColourIds::textColourOffId, textColour);
	muteButton.setColour(juce::TextButton::textColourOnId, textColour);
	muteButton.setAlpha(1.0f);
	muteButton.setEnabled(true);

	superiorButton.setButtonText("SOLO");
	superiorButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
	superiorButton.setEnabled(false);

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
	//g.fillAll(juce::Colours::aqua);
}

void TrackComponent::resized(void) {

	const double controlPanelPercentage = 0.1;

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

	juce::FlexItem leftSideBoxItem(100, getHeight(), leftSideBox);
	juce::FlexItem volumeSliderItem(10, getHeight(), volumeSlider);
	juce::FlexItem waveformItem(getWidth(), getHeight(), waveform);
	controlsBox.items = { leftSideBoxItem, volumeSliderItem, waveformItem };

	controlsBox.performLayout(getBounds());

}

void TrackComponent::setSource(juce::AudioSampleBuffer* buffer, double sampleRate) {
	waveform.setSource(buffer, sampleRate);

}

void TrackComponent::clear() {
	waveform.clear();
}
