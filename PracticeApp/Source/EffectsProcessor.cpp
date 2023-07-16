#include "EffectsProcessor.h"
//#include "TracksAudioSource.h"


EffectsProcessor::EffectsProcessor() 
{
}

EffectsProcessor::~EffectsProcessor()
{
}

void EffectsProcessor::makeReverb(std::function<void()> updateBufferAndActivateHistory, TrackAudioBuffer& buffer, double sampleRate, int startSamp, int len)
{
    if (len == -1)
        len = buffer.getNumSamples();
    reverb.setSampleRate(sampleRate);

    reverbWindowComponent.getApllyButton()->onClick = [this, updateBufferAndActivateHistory, &buffer, sampleRate, startSamp, len] 
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
        updateBufferAndActivateHistory();
    };

    DialogWindow::showDialog(RussianText::reverberation.c_str(), &reverbWindowComponent, NULL,
                                ProjectColours::ReverbWindow::dialogWindowBackground, true);
    reverbWindowComponent.setSize(600, 600);
}



