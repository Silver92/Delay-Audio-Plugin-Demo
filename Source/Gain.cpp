/*
  ==============================================================================

    Gain.cpp
    Created: 6 Sep 2019 7:09:14am
    Author:  Silver

  ==============================================================================
*/

#include "Gain.h"
#include "JuceHeader.h"

Gain::Gain()
{
    
} 

Gain::~Gain()
{
    
}

void Gain::process(float* inChannel,
             float inGain,
             float* outChannel,
             int sampleNumToRender)
{
    float dBinGain = jmap(inGain, 0.0f, 1.0f, -18.0f, 18.0f);
    dBinGain = Decibels::decibelsToGain(dBinGain, -18.0f);
    
    for (int sample = 0; sample < sampleNumToRender; sample++) {
        outChannel[sample] = inChannel[sample] * dBinGain;
    }
}
