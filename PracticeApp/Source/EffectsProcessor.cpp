#include "EffectsProcessor.h"
//#include "TracksAudioSource.h"


EffectsProcessor::EffectsProcessor() 
{
}

EffectsProcessor::~EffectsProcessor()
{
}

void EffectsProcessor::makeReverb(TrackAudioBuffer& buffer, double sampleRate, int startSamp, int len) {
    reverb.setSampleRate(sampleRate);

    reverbWindowComponent.setSize(390, 280);

    DialogWindow::showDialog("Reverberation", &reverbWindowComponent, NULL, 
                                ProjectColours::DialogWindow::dialogWindowBackground, true);

    reverb.setParameters(reverbWindowComponent.getParameters());

    float* const firstChannel = buffer.getWritePointer(0, startSamp);

    if (buffer.getNumChannels() > 1) {
        reverb.processStereo(firstChannel,
            buffer.getWritePointer(1, startSamp),
            len);
    }
    else {
        reverb.processMono(firstChannel, len);
    }
}

void EffectsProcessor::makeReverb(TrackAudioBuffer& buffer, double sampleRate)
{
    makeReverb(buffer, sampleRate, 0, buffer.getNumSamples());
}




