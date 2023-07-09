#include "TracksAudioSource.h";

TracksAudioSource::TracksAudioSource()
    : currentSampleRate(0.0), bufferSizeExpected(0) {
    mainSource.addChangeListener(this);
}

TracksAudioSource::~TracksAudioSource() {
    removeAllInputs();
}

//==============================================================================
void TracksAudioSource::addInputSource(TrackAudioBuffer* input) {
    if (input != nullptr && !inputs.contains(input)) {
        double localRate;
        int localBufferSize;
        {
            const ScopedLock sl(lock);
            localRate = currentSampleRate;
            localBufferSize = bufferSizeExpected;
        }
        const ScopedLock sl(lock);
        muteChannels.insertBit(inputs.size(), false);
        inputs.add(input);
        
        recalculateBuffer();
    }
}

void TracksAudioSource::addInputSource(juce::File file, AudioFormatManager* formatManager) {
    
    if (file != juce::File{}) {
        auto* reader = formatManager->createReaderFor(file);
        if (reader != nullptr) {
            auto buffer = new TrackAudioBuffer(reader->numChannels, reader->lengthInSamples);
            AudioSourceChannelInfo info(*buffer);
            reader->read(buffer, 0, reader->lengthInSamples, 0, true, true);
            addInputSource(buffer);
        }
        delete reader;
    }
}

void TracksAudioSource::setInputSource(int index, TrackAudioBuffer* newInput) {
    inputs.set(index, newInput, true);
    recalculateBuffer();
}

void TracksAudioSource::removeInputSource(TrackAudioBuffer* const input) {
    if (input != nullptr) {
        {
            const ScopedLock sl(lock);
            const int index = inputs.indexOf(input);

            if (index < 0)
                return;

            inputs.remove(index);
            if (soloId == index) {
                soloId = -1;
            }
            muteChannels.shiftBits(-1, index);
            recalculateBuffer();
        }

    }

}

void TracksAudioSource::removeInputSource(int index) {
    inputs.remove(index);
}

TrackAudioBuffer* TracksAudioSource::getBuffer(int index) {
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

void TracksAudioSource::setSampleRate(double rate) {
    sampleRate = rate;
}

double TracksAudioSource::getSampleRate() {
    return sampleRate;
}

void TracksAudioSource::unmuteTrack(int trackId) {
    if (trackId >= 0 && trackId < inputs.size() && muteChannels[trackId]) {
        muteChannels.clearBit(trackId);
        recalculateBuffer();
    }
        
}

void TracksAudioSource::muteTrack(int trackId) {
    if (trackId >= 0 && trackId < inputs.size() && !muteChannels[trackId]) {
        muteChannels.setBit(trackId);
        recalculateBuffer();
    }
        
}

void TracksAudioSource::soloTrack(int trackId) {
    if (trackId >= 0 && trackId < inputs.size() && trackId != soloId) {
        soloId = trackId;
        recalculateBuffer();
    }
}

void TracksAudioSource::recalculateBuffer() {
    if (soloId != -1) {
        auto newSource = std::make_unique<MemoryAudioSource>(*inputs[soloId], true);
        mainSource.setSource(newSource.get(), 0, nullptr, sampleRate, inputs[soloId]->getNumChannels());
        mainBuffer.reset(newSource.release());
    }

    DBG("CLEAR BIT: " << muteChannels.findNextClearBit(0));
    if (inputs.size() > 0 && muteChannels.findNextClearBit(0) < inputs.size()) {
        TrackAudioBuffer* exampleBuffer = getBufferMaxSize();
        TrackAudioBuffer resBuffer(*exampleBuffer);
        // TODO: Дорожки перезаписываются, нужно тут создать ещё один буффер
        AudioSourceChannelInfo info(resBuffer);
        if (inputs.size() > 1) {
            for (int i = 0; i < inputs.size(); ++i) {
                if (exampleBuffer == inputs.getUnchecked(i) || muteChannels[i])
                    continue;
                
                for (int chan = 0; chan < info.buffer->getNumChannels(); ++chan)
                    if (chan < inputs.getUnchecked(i)->getNumChannels())
                        info.buffer->addFrom(chan, 0, *inputs.getUnchecked(i), chan, 0, inputs.getUnchecked(i)->getNumSamples());
            }
        } 
        auto newSource = std::make_unique<MemoryAudioSource>(*info.buffer, true);
        mainSource.setSource(newSource.get(),0,nullptr,sampleRate,info.buffer->getNumChannels());
        mainBuffer.reset(newSource.release());
    }
    else {
        mainSource.setSource(nullptr);
        mainBuffer.reset();
    }
}

TrackAudioBuffer* TracksAudioSource::getBufferMaxSize() {
    int maxSamples = -1;
    TrackAudioBuffer* res = nullptr;
    for (int i = 0; i < inputs.size(); i++) {
        auto in = inputs[i];
        if (in->getNumSamples() > maxSamples && !muteChannels[i]) {
            res = in;
            maxSamples = in->getNumSamples();
        }
    }
    return res;
}
