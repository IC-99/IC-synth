/*
  ==============================================================================

    SynthVoice.h
    Created: 23 Jan 2024 6:39:21pm
    Author:  ivanc

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
     
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        if (velocity == 0)
            clearCurrentNote();
    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {
        env1.setAttack(300);
        env1.setDecay(500);
        env1.setSustain(0.5);
        env1.setRelease(200);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.saw(frequency);
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            double filteredSound = filter1.lores(theSound, 3500, 0.1);

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, filteredSound);
            }
            ++startSample;
        }
    }

    void pitchWheelMoved(int newPitchWheelValue)
    {
        return;
    }

    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        return;
    }

private:
    double level;
    double frequency;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};