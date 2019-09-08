/*
  ==============================================================================

    Gain_Panel.h
    Created: 6 Sep 2019 7:10:29am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "Panel_Base.h"

class GainPanel
:   public PanelBase
{
public:
    GainPanel(MyDelayPluginAudioProcessor* inProcessor);
    ~GainPanel();
    
    void paint(Graphics& g) override;
    
private:
    
private:
};
