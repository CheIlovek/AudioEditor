#include "EffectsProcessor.h"
//#include "TracksAudioSource.h"


EffectsProcessor::EffectsProcessor() 
{
}

EffectsProcessor::~EffectsProcessor()
{
}

void EffectsProcessor::makeReverb(TrackAudioBuffer& buffer, double sampleRate)
{

    reverb.setSampleRate(sampleRate);

    float* const firstChannel = buffer.getWritePointer(0, 0);

    if (buffer.getNumChannels() > 1)
    {
        reverb.processStereo(firstChannel,
            buffer.getWritePointer(1, 0),
            buffer.getNumSamples());
    }
    else
    {
        reverb.processMono(firstChannel, buffer.getNumSamples());
    }
}




