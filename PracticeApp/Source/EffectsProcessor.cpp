#include "EffectsProcessor.h"
//#include "TracksAudioSource.h"


EffectsProcessor::EffectsProcessor() 
{
}

EffectsProcessor::~EffectsProcessor()
{
}

void EffectsProcessor::makeReverb(std::function<void()> updateBuffer, TrackAudioBuffer& buffer, double sampleRate, int startSamp, int len)
{
    if (len == -1)
        len = buffer.getNumSamples();
    reverb.setSampleRate(sampleRate);

    reverbWindowComponent.getApllyButton()->onClick = [this, updateBuffer, &buffer, sampleRate, startSamp, len] 
    {
        reverbWindowComponent.updateParameters();
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
        updateBuffer();
    };

    DialogWindow::showDialog("Reverberation", &reverbWindowComponent, NULL, 
                                ProjectColours::DialogWindow::dialogWindowBackground, true, false);
    reverbWindowComponent.setSize(500, 500);
}



