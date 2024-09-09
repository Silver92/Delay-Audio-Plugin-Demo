/*
  ==============================================================================

    Panel_Base.cpp
    Created: 6 Sep 2019 7:09:55am
    Author:  Silver

  ==============================================================================
*/

#include "Panel_Base.h"

PanelBase::PanelBase(MyDelayPluginAudioProcessor* inProcessor)
:   mProcessor(inProcessor)
{
    
}

PanelBase::~PanelBase()
{
    
}

void PanelBase::paint (Graphics& g)
{
    g.setColour(Colours::whitesmoke);
    g.fillAll();
    
    g.setColour(Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight());
    
}
