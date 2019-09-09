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
    
    mGainSlider.reset(new RotarySlider());
    mGainSlider->setColour(Slider::thumbColourId, Colours::black);
    mGainSlider->setBounds(25, SLIDER_POS_Y, SLIDER_SIZE, SLIDER_SIZE);
    addAndMakeVisible(mGainSlider.get());
    
    mGainLabel.reset(new Label());
    mGainLabel->setFont(Font(16.0f, Font::bold));
    mGainLabel->setText("Gain", dontSendNotification);
    mGainLabel->setColour(Label::textColourId, Colours::black);
    mGainLabel->setJustificationType(Justification::centred);
    mGainLabel->setBounds(25,
                          SLIDER_POS_Y + SLIDER_SIZE * 0.9,
                          SLIDER_SIZE,
                          SLIDER_SIZE / 3);
    addAndMakeVisible(mGainLabel.get());
    
}

GainPanel::~GainPanel()
{
    
}

void GainPanel::paint(Graphics& g)
{
    PanelBase::paint(g);
}
