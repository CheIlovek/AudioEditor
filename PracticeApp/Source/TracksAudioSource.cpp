#include "TracksAudioSource.h";

TracksAudioSource::TracksAudioSource()
    : currentSampleRate(0.0), bufferSizeExpected(0) {
    mainSource.addChangeListener(this);
}

TracksAudioSource::~TracksAudioSource() {
    removeAllInputs();
}

//==============================================================================
void TracksAudioSource::addInputSource(AudioSampleBuffer* input) {
    if (input != nullptr && !inputs.contains(input)) {
        double localRate;
        int localBufferSize;
        {
            const ScopedLock sl(lock);
            localRate = currentSampleRate;
            localBufferSize = bufferSizeExpected;
        }
        const ScopedLock sl(lock);
        inputs.add(input);
        recalculateBuffer();
    }
}

void TracksAudioSource::addInputSource(juce::File file, AudioFormatManager* formatManager) {
    if (file != juce::File{}) {
        auto* reader = formatManager->createReaderFor(file);
        if (reader != nullptr) {
            auto buffer = new AudioBuffer<float>(reader->numChannels, reader->lengthInSamples);
            AudioSourceChannelInfo info(*buffer);
            reader->read(buffer, 0, reader->lengthInSamples, 0, true, true);
            addInputSource(buffer);
        }
        delete reader;
    }
}

void TracksAudioSource::setInputSource(int index, AudioSampleBuffer* newInput) {
    inputs.set(index, newInput, true);
    recalculateBuffer();
}

void TracksAudioSource::removeInputSource(AudioSampleBuffer* const input) {
    if (input != nullptr) {
        {
            const ScopedLock sl(lock);
            const int index = inputs.indexOf(input);

            if (index < 0)
                return;

            inputs.remove(index);
            recalculateBuffer();
        }

    }

}

void TracksAudioSource::removeInputSource(int index) {
    inputs.remove(index);
}

AudioSampleBuffer* TracksAudioSource::getBuffer(int index) {
    return inputs[index];
}

void TracksAudioSource::removeAllInputs() {
    const ScopedLock sl(lock);
    inputs.clear();
}

void TracksAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    tempBuffer.setSize(2, samplesPerBlockExpected);

    const ScopedLock sl(lock);
    currentSampleRate = sampleRate;
    bufferSizeExpected = samplesPerBlockExpected;
    recalculateBuffer();
    mainSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void TracksAudioSource::releaseResources() {
    const ScopedLock sl(lock);
    mainSource.releaseResources();
    tempBuffer.setSize(2, 0);
    currentSampleRate = 0;
    bufferSizeExpected = 0;
}

void TracksAudioSource::getNextAudioBlock(const AudioSourceChannelInfo& info) {
    const ScopedLock sl(lock);
    mainSource.getNextAudioBlock(info);
}

double TracksAudioSource::getLengthInSeconds() const {
    return mainSource.getLengthInSeconds();
}

double TracksAudioSource::getCurrentPosition() const {
    return mainSource.getCurrentPosition();
}

void TracksAudioSource::changeListenerCallback(juce::ChangeBroadcaster* source) {
    if (source = &mainSource)
        sendChangeMessage();
}

bool TracksAudioSource::isPlaying() const {
    return mainSource.isPlaying();
}

void TracksAudioSource::setPosition(double newPosition) {
    mainSource.setPosition(newPosition);
}

void TracksAudioSource::start() {
    mainSource.start();
}

void TracksAudioSource::stop() {
    mainSource.stop();
}

void TracksAudioSource::recalculateBuffer() {
    if (inputs.size() > 0) {
        AudioSourceChannelInfo info(*getBufferMaxSize());
        if (inputs.size() > 1) {

            for (int i = 0; i < inputs.size(); ++i) {
                if (info.buffer == inputs.getUnchecked(i))
                    continue;
                
                for (int chan = 0; chan < info.buffer->getNumChannels(); ++chan)
                    if (chan < inputs.getUnchecked(i)->getNumChannels())
                        info.buffer->addFrom(chan, info.startSample, *inputs.getUnchecked(i), chan, 0, inputs.getUnchecked(i)->getNumSamples());
            }
        }
        auto newSource = std::make_unique<MemoryAudioSource>(*info.buffer, true);
        mainSource.setSource(newSource.get());
        mainBuffer.reset(newSource.release());
    }
    else {
        mainSource.setSource(nullptr);
        mainBuffer.release();
    }
}

AudioSampleBuffer* TracksAudioSource::getBufferMaxSize() {
    int maxSamples = -1;
    AudioSampleBuffer* res = nullptr;
    for (auto& in : inputs) {
        if (in->getNumSamples() > maxSamples) {
            res = in;
            maxSamples = in->getNumSamples();
        }
    }
    return res;
}
