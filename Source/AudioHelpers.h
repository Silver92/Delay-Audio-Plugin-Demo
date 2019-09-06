/*
  ==============================================================================

    AudioHelpers.h
    Created: 6 Sep 2019 9:29:43am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#define ParameterSmoothingCoeff 0.04

const int maxBufferDelayScale = 4;

inline float linear_interp(float pos0, float pos1, float t)
{
    return (1 - t) * pos0 + t * pos1;
}
