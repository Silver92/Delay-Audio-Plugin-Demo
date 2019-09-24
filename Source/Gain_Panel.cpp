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
    
    initSliderWithParameterID(inProcessor, inParameterID);
    initVUMeter(inProcessor, inParameterID);
}

GainPanel::~GainPanel()
{
    
}

void GainPanel::paint(Graphics& g)
{
    PanelBase::paint(g);
}

void GainPanel::initSliderWithParameterID(MyDelayPluginAudioProcessor* inProcessor, int inParameterID)
{
    mGainSlider.reset(new RotarySlider(mProcessor->parameters, inParameterID));
    mGainSlider->setColour(Slider::thumbColourId, Colours::black);
    mGainSlider->setBounds(getWidth() * 0.5 - SLIDER_SIZE * 0.5,
                           SLIDER_POS_Y,
                           SLIDER_SIZE,
                           SLIDER_SIZE);
    addAndMakeVisible(mGainSlider.get());
    
    mGainLabel.reset(new Label());
    mGainLabel->setFont(Font(16.0f, Font::bold));
    mGainLabel->setText(ParameterLabel[inParameterID], dontSendNotification);
    mGainLabel->setColour(Label::textColourId, Colours::black);
    mGainLabel->setJustificationType(Justification::centred);
    mGainLabel->setBounds(getWidth() * 0.5 - SLIDER_SIZE * 0.5,
                          SLIDER_POS_Y + SLIDER_SIZE * 0.9,
                          SLIDER_SIZE,
                          SLIDER_SIZE / 3);
    addAndMakeVisible(mGainLabel.get());
    
    
    mSliderText.reset(new SliderText(inProcessor));
    mSliderText->setParameterID(inParameterID);
    mSliderText->setBounds(getWidth() * 0.5 - SLIDER_SIZE * 0.5,
                           SLIDER_POS_Y + SLIDER_SIZE / 4,
                           SLIDER_SIZE,
                           SLIDER_SIZE / 2);
    addAndMakeVisible(mSliderText.get());
}

void GainPanel::initVUMeter(MyDelayPluginAudioProcessor *inProcessor, int inParameterID)
{
    mVUMeter.reset(new VUMeter(inProcessor));
    mVUMeter->setBounds(getWidth() * 0.5 - VUMETER_WIDTH * 1.05,
                        SLIDER_POS_Y + SLIDER_SIZE * 1.3,
                        SLIDER_SIZE,
                        getHeight() * 0.4);
    addAndMakeVisible(mVUMeter.get());
    mVUMeter->setParameterID(inParameterID);
}
