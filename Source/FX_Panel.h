/*
  ==============================================================================

    FX_Panel.h
    Created: 8 Sep 2019 8:12:16pm
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "Panel_Base.h"

class FXPanel
:   public PanelBase
{
public:
    FXPanel(MyDelayPluginAudioProcessor* inProcessor);
    ~FXPanel();
    
    void paint(Graphics& g) override;
    
private:
    
    OwnedArray<Slider> mSliders;
    OwnedArray<Label> mLabels;
};
