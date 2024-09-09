/*
  ==============================================================================

    Panel_Base.h
    Created: 6 Sep 2019 7:09:55am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "UIDemensions.h"
#include "ParameterList.h"

class PanelBase
:   public Component
{
public:
    PanelBase(MyDelayPluginAudioProcessor* inProcessor);
    ~PanelBase();
    
    void paint (Graphics& g) override;
    
protected:
    
    MyDelayPluginAudioProcessor* mProcessor;
};
