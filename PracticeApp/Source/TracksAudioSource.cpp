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

void TracksAudioSource::setOffset(int trackId, double offset) {
    if (trackId >= 0 && trackId < inputs.size() && offset >= 0) {
        DBG("OFFSET IN SEC = " << offset);
        int offsetInSamples = offset * sampleRate;
        DBG("OFFSET IN SAMP = " << offsetInSamples);
        inputs.getUnchecked(trackId)->setOffset(offsetInSamples);
        recalculateBuffer();
    }
    
}

void TracksAudioSource::recalculateBuffer() {
    DBG("SOLO IS " << soloId);
    if (soloId != -1) {
        TrackAudioBuffer resBuffer(inputs[soloId]->getNumChannels(), inputs[soloId]->getNumSamples() + inputs[soloId]->getOffset());
        resBuffer.clear();
        AudioSourceChannelInfo info(resBuffer);

        for (int chan = 0; chan < info.buffer->getNumChannels(); ++chan)
            if (chan < inputs.getUnchecked(soloId)->getNumChannels()) {
                DBG("OFFSET FOR " << soloId << " = " << inputs.getUnchecked(soloId)->getOffset());
                DBG("NUMSAMPLES FOR " << soloId << " = " << inputs.getUnchecked(soloId)->getNumSamples());
                info.buffer->addFrom(chan, inputs.getUnchecked(soloId)->getOffset(), *inputs.getUnchecked(soloId), chan, 0, inputs.getUnchecked(soloId)->getNumSamples());
            }

        auto newSource = std::make_unique<MemoryAudioSource>(*info.buffer, true);
        mainSource.setSource(newSource.get(), 0, nullptr, sampleRate, inputs[soloId]->getNumChannels());
        mainBuffer.reset(newSource.release());
        return;
    }

    DBG("CLEAR BIT: " << muteChannels.findNextClearBit(0));
    if (inputs.size() > 0 && muteChannels.findNextClearBit(0) < inputs.size()) {
        TrackAudioBuffer* exampleBuffer = getBufferMaxSize();
        TrackAudioBuffer resBuffer(exampleBuffer->getNumChannels(), exampleBuffer->getNumSamples() + exampleBuffer->getOffset());
        resBuffer.clear();
        AudioSourceChannelInfo info(resBuffer);
        for (int i = 0; i < inputs.size(); ++i) {
            if (/*exampleBuffer == inputs.getUnchecked(i) ||*/ muteChannels[i])
                continue;
                
            for (int chan = 0; chan < info.buffer->getNumChannels(); ++chan)
                if (chan < inputs.getUnchecked(i)->getNumChannels()) {
                    DBG("OFFSET FOR " << i << " = " << inputs.getUnchecked(i)->getOffset());
                    DBG("NUMSAMPLES FOR " << i << " = " << inputs.getUnchecked(i)->getNumSamples());
                    info.buffer->addFrom(chan, inputs.getUnchecked(i)->getOffset(), *inputs.getUnchecked(i), chan, 0, inputs.getUnchecked(i)->getNumSamples());
                }
        }
        info.buffer->setNotClear();
        
        
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
        if ((in->getNumSamples() + in->getOffset()) > maxSamples && !muteChannels[i]) {
            res = in;
            maxSamples = in->getNumSamples() + in->getOffset();
        }
    }
    return res;
}
