/*
  ==============================================================================

    SynthSound.h
    Created: 23 Jan 2024 6:38:57pm
    Author:  ivanc

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int /*midiNoteNumber*/)
    {
        return true;
    }

    bool appliesToChannel (int /*midiChannel*/)
    {
        return true;
    }
};