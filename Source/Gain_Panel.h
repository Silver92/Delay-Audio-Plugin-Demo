/*
  ==============================================================================

    Gain_Panel.h
    Created: 6 Sep 2019 7:10:29am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "Panel_Base.h"
#include "Rotary_Slider.h"
#include "VU_Meter.h"

class GainPanel
:   public PanelBase
{
public:
    void extracted(MyDelayPluginAudioProcessor *inProcessor);
    
GainPanel(MyDelayPluginAudioProcessor* inProcessor, int inParameterID);
    ~GainPanel();
    
    void paint(Graphics& g) override;
    
private:
    
    void initSliderWithParameterID(int inParameterID);
    void initVUMeter(MyDelayPluginAudioProcessor *inProcessor, int inParameterID);
    
    std::unique_ptr<RotarySlider> mGainSlider;
    std::unique_ptr<Label> mGainLabel;
    std::unique_ptr<VUMeter> mVUMeter;
};
