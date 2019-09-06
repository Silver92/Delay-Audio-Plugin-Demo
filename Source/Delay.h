/*
  ==============================================================================

    Delay.h
    Created: 6 Sep 2019 7:09:22am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "AudioHelpers.h"
#include <vector>

class Delay
{
public:
    Delay();
    ~Delay();
    
    void setSampleRate(double inSampleRate);
    
    void reset();
    
    void process(float* inChannnel,
                 float inTime,
                 float inFeedback,
                 float inWetRatio,
                 float* outChannel,
                 int SampleNumToRender);
private:
    
    double getInterpolatedSample(double inDelayTimeInSamples);
    
    double mSampleRate;
    int maxBufferDelaySize;
    float mTimeSmoothed;
    int mDelayIndex;
    
    std::vector<double> mBuffer;
};
