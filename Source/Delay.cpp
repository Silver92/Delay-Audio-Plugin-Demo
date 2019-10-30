/*
  ==============================================================================

    Delay.cpp
    Created: 6 Sep 2019 7:09:22am
    Author:  Silver

  ==============================================================================
*/

#include "Delay.h"

#include "JuceHeader.h"

Delay::Delay()
:   mSampleRate(-1),
    maxBufferDelaySize(0),
    mTimeSmoothed(0),
    mDelayIndex(0)
{
    
}

Delay::~Delay()
{
    
}

void Delay::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
    maxBufferDelaySize = mSampleRate * maxBufferDelayScale;
    mBuffer.resize(maxBufferDelaySize, 0);
}

void Delay::reset()
{ 
    mTimeSmoothed = 0.0f;
    mBuffer.clear();
}

void Delay::process(float* inChannnel,
                    float inTime,
                    float inFeedback,
                    float inWetRatio,
                    float* outChannel,
                    int SampleNumToRender)
{
    const float wet = inWetRatio;
    const float dry = 1.0f - wet;
    float feedbackMapped = jmap(inFeedback, 0.0f, 1.0f, 0.0f, 0.95f);
    float inTimeMapped = jmap(inTime, 0.0f, 1.0f, 0.05f, 2.0f);
    
    for (int i = 0; i < SampleNumToRender; i++) {
        
        mTimeSmoothed = mTimeSmoothed - ParameterSmoothingCoeff * (mTimeSmoothed - inTimeMapped);
        
        const double delayTimeInSamples = (mTimeSmoothed * mSampleRate);
        
        double readPosition = (double)mDelayIndex - delayTimeInSamples;
        if (readPosition < 0.0f) {
            readPosition += maxBufferDelaySize;
        }
        
        const double sampleVal = getInterpolatedSample(readPosition);
        
        // Don't exchange the store and output order in case the inChannel and
        // the outChannel are same.
        mBuffer[mDelayIndex] = (inChannnel[i] + sampleVal) * feedbackMapped;
        outChannel[i] = (inChannnel[i] * dry + sampleVal * wet);
        
        mDelayIndex++;
        if (mDelayIndex >= maxBufferDelaySize) {
            mDelayIndex -= maxBufferDelaySize;
        }
    }
}

double Delay::getInterpolatedSample(double inDelayTimeInSamples)
{
    
    int index0 = (int)inDelayTimeInSamples;
    if (index0 < 0) {
        index0 += maxBufferDelaySize;
    }
    int index1 = (int)inDelayTimeInSamples + 1;
    if (index1 >= maxBufferDelaySize) {
        index1 -= maxBufferDelaySize;
    }
    
    const float sample_y0 = mBuffer[index0];
    const float sample_y1 = mBuffer[index1];
    const float t = inDelayTimeInSamples - index0;
    
    double outSample = linear_interp(sample_y0, sample_y1, t);
    
    return outSample;
}
