/*
  ==============================================================================

    FX_Panel.h
    Created: 8 Sep 2019 8:12:16pm
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "Panel_Base.h"
#include "Rotary_Slider.h"
#include "Slider_Text.h"

class FXPanel
:   public PanelBase
{
public:
    
    FXPanel(MyDelayPluginAudioProcessor* inProcessor);
    ~FXPanel();
    
    void paint(Graphics& g) override;
    
    void drawSlider(int x, int y, int parameterIndex);
    void drawSliderLabel(int x, int y, int parameterIndex);
    void drawSliderText(int x, int y, int parameterIndex, float minRange, float maxRange, String inUnit);
    
private:
    
    OwnedArray<RotarySlider> mSliders;
    OwnedArray<Label> mLabels;
    OwnedArray<SliderText> mSliderTexts;
};
