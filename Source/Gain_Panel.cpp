/*
  ==============================================================================

    Gain_Panel.cpp
    Created: 6 Sep 2019 7:10:29am
    Author:  Silver

  ==============================================================================
*/

#include "Gain_Panel.h"

GainPanel::GainPanel(MyDelayPluginAudioProcessor* inProcessor, int inParameterID)
:   PanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH,
            GAIN_PANEL_HEIGHT);
    
    initWithParameterID(inParameterID);
    
}

GainPanel::~GainPanel()
{
    
}

void GainPanel::paint(Graphics& g)
{
    PanelBase::paint(g);
}

void GainPanel::initWithParameterID(int inParameterID)
{
    mGainSlider.reset(new RotarySlider(mProcessor->parameters, inParameterID));
    mGainSlider->setColour(Slider::thumbColourId, Colours::black);
    mGainSlider->setBounds(25, SLIDER_POS_Y, SLIDER_SIZE, SLIDER_SIZE);
    addAndMakeVisible(mGainSlider.get());
    
    mGainLabel.reset(new Label());
    mGainLabel->setFont(Font(16.0f, Font::bold));
    mGainLabel->setText(ParameterLabel[inParameterID], dontSendNotification);
    mGainLabel->setColour(Label::textColourId, Colours::black);
    mGainLabel->setJustificationType(Justification::centred);
    mGainLabel->setBounds(25,
                          SLIDER_POS_Y + SLIDER_SIZE * 0.9,
                          SLIDER_SIZE,
                          SLIDER_SIZE / 3);
    addAndMakeVisible(mGainLabel.get());
}
