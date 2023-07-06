#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TracksAudioSource : public AudioSource,
    public juce::ChangeListener,
    public juce::ChangeBroadcaster {
public:

    TracksAudioSource();
    ~TracksAudioSource() override;

    void addInputSource(AudioSampleBuffer* newInput);
    void addInputSource(juce::File file, AudioFormatManager* formatManager);
    void setInputSource(int index, AudioSampleBuffer* newInput);
    void removeInputSource(AudioSampleBuffer* input);
    void removeInputSource(int index);
    AudioSampleBuffer* getBuffer(int index);
    void removeAllInputs();
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const AudioSourceChannelInfo&) override;

    double getLengthInSeconds() const;
    double getCurrentPosition() const;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    bool isPlaying() const;
    void setPosition(double newPosition);
    void start();
    void stop();


private:
    void recalculateBuffer();
    AudioSampleBuffer* getBufferMaxSize();
    //==============================================================================
    OwnedArray<AudioSampleBuffer> inputs;
    std::unique_ptr<MemoryAudioSource> mainBuffer;
    AudioTransportSource mainSource;
    CriticalSection lock;
    AudioBuffer<float> tempBuffer;
    double currentSampleRate;
    int bufferSizeExpected;
    int sourcesPlaying = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksAudioSource)
};
