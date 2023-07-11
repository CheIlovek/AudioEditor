#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackAudioBuffer.h"
//#include "Headers.h"
#include "EffectsProcessor.h"

//class EffectsProcessor;

/**
@brief Класс реализует работу со звуком в проекте
*/
class TracksAudioSource : public AudioSource,
    public juce::ChangeListener,
    public juce::ChangeBroadcaster {
public:

    TracksAudioSource();
    ~TracksAudioSource() override;

    void addInputSource(TrackAudioBuffer* newInput);
    void addInputSource(juce::File file, AudioFormatManager* formatManager);
    void setInputSource(int index, TrackAudioBuffer* newInput);
    void removeInputSource(TrackAudioBuffer* input);
    void removeInputSource(int index);
    TrackAudioBuffer* getBuffer(int index);
    EffectsProcessor& getEffectsProcessor();
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
    void setSampleRate(double);
    double getSampleRate();
    void unmuteTrack(int trackId);
    void muteTrack(int trackId);
    void soloTrack(int trackId);
    void setOffset(int trackId, double offset);


private:
    void recalculateBuffer();
    TrackAudioBuffer* getBufferMaxSize();
    //==============================================================================
    OwnedArray<TrackAudioBuffer> inputs;
    std::unique_ptr<MemoryAudioSource> mainBuffer;
    AudioTransportSource mainSource;
    CriticalSection lock;
    AudioBuffer<float> tempBuffer;
    EffectsProcessor effectsProcessor;
    double currentSampleRate;
    int bufferSizeExpected;
    int sourcesPlaying = 0;
    double sampleRate = 44100;
    BigInteger muteChannels;
    int soloId = -1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksAudioSource)
};
