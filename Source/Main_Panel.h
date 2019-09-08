/*
  ==============================================================================

    Main_Panel.h
    Created: 6 Sep 2019 7:10:05am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "Panel_Base.h"
#include "Gain_Panel.h"

class MainPanel
:   public PanelBase
{
public:
    MainPanel(MyDelayPluginAudioProcessor* inProcessor);
    ~MainPanel();
private:
    
    std::unique_ptr<GainPanel> mInputGainPanel;
    std::unique_ptr<GainPanel> mOutputGainPanel;
};
