/*
  ==============================================================================

    Slider_Text.h
    Created: 24 Sep 2019 4:00:24pm
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"

class SliderText
:   public Timer,
    public Label
{
public:
    
    SliderText(MyDelayPluginAudioProcessor* inProcessor);
    ~SliderText();
    
//    void paint(Graphics& g) override;
    void timerCallback() override;
    void setParameterID(int inParameterID);
    
private:
    int mParameterID;
    MyDelayPluginAudioProcessor* mProcessor;
};
