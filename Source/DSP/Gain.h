/*
  ==============================================================================

    Gain.h
    Created: 6 Sep 2019 7:09:14am
    Author:  Silver

  ==============================================================================
*/

#pragma once

class Gain
{
public:
    Gain();
    ~Gain();
    
    void process(float* inChannel,
                 float inGain,
                 float* outChannel,
                 int sampleNumToRender);
    
    float getMeterLevel();
private:
    float mOutputSmoothed;
};
