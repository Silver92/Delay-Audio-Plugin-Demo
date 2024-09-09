/*
  ==============================================================================

    VU_Meter.h
    Created: 6 Sep 2019 7:11:37am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include <juce_events/juce_events.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"
#include "UIDemensions.h"
using namespace juce;

class VUMeter
:   public Component,
    public Timer
{
public:
    VUMeter(MyDelayPluginAudioProcessor* inProcessor);
    ~VUMeter();
    
    void paint(Graphics& g) override;
    
    void timerCallback() override;
    
    void setParameterID(int inParameterID);
    
private:
    
    int mParameterID;
    
    float mCh0Level;
    float mCh1Level;
    
    MyDelayPluginAudioProcessor* mProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VUMeter);
};
