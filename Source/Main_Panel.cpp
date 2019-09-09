/*
  ==============================================================================

    Main_Panel.cpp
    Created: 6 Sep 2019 7:10:05am
    Author:  Silver

  ==============================================================================
*/

#include "Main_Panel.h"

MainPanel::MainPanel(MyDelayPluginAudioProcessor* inProcessor)
: PanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    
    mInputGainPanel.reset(new GainPanel(inProcessor));
    mInputGainPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mInputGainPanel.get());
    
    mFXPanel.reset(new FXPanel(inProcessor));
    mFXPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, 0);
    addAndMakeVisible(mFXPanel.get());
    
    mOutputGainPanel.reset(new GainPanel(inProcessor));
    mOutputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH, 0);
    addAndMakeVisible(mOutputGainPanel.get());
}

MainPanel::~MainPanel()
{
    
}
