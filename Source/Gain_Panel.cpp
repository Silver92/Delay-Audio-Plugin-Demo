/*
  ==============================================================================

    Gain_Panel.cpp
    Created: 6 Sep 2019 7:10:29am
    Author:  Silver

  ==============================================================================
*/

#include "Gain_Panel.h"

GainPanel::GainPanel(MyDelayPluginAudioProcessor* inProcessor)
:   PanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH,
            GAIN_PANEL_HEIGHT);
}

GainPanel::~GainPanel()
{
    
}

void GainPanel::paint(Graphics& g)
{
    PanelBase::paint(g);
}
