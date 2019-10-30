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
:   public Label
{
public:
    
    SliderText();
    ~SliderText();
    
//    void paint(Graphics& g) override;
    void setParameterID(int inParameterID);
    void setTextRange(float inMinVal, float inMaxVal);
    void setUnit(String inString);
    int getParameterID();
    float getMinRange();
    float getMaxRange();
    String getUnit();
    
private:
    int mParameterID;
    float minRange;
    float maxRange;
    String unit;
};
