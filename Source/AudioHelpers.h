/*
  ==============================================================================

    AudioHelpers.h
    Created: 6 Sep 2019 9:29:43am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define ParameterSmoothingCoeff 0.04
#define MeterSmoothingCoeff 0.1

const int maxBufferDelayScale = 4;

inline float linear_interp(float pos0, float pos1, float t)
{
    return (1 - t) * pos0 + t * pos1;
}

static inline float dBToNormalizedGain(float inValue)
{
    float inValuedB = Decibels::gainToDecibels(inValue + 0.00001f);
    inValuedB = (inValuedB + 96.0f) / 96.0f;
    
    return inValuedB;
    
}

inline float denormalize(float inValue)
{
    float absValue = fabs(inValue);
    
    if (absValue < 1e-15) {
        return  0.0f;
    } else {
        return inValue;
    }
}
