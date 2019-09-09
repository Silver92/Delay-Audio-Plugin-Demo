/*
  ==============================================================================

    FX_Panel.cpp
    Created: 8 Sep 2019 8:12:16pm
    Author:  Silver

  ==============================================================================
*/

#include "FX_Panel.h"

#include "Panel_Base.h"

FXPanel::FXPanel(MyDelayPluginAudioProcessor* inProcessor)
:   PanelBase(inProcessor)
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
    
    int x = SLIDER_POS_X;
    int y = SLIDER_POS_Y;
    
    RotarySlider* timeSLider = new RotarySlider(mProcessor->parameters,
                                                Parameter_DelayTime);
    timeSLider->setColour(Slider::thumbColourId, Colours::black);
    timeSLider->setBounds(x, y, SLIDER_SIZE, SLIDER_SIZE);
    addAndMakeVisible(timeSLider);
    mSliders.add(timeSLider);
    
    Label* timeLabel = new Label();
    timeLabel->setFont(Font(16.0f, Font::bold));
    timeLabel->setText("Delay Time", dontSendNotification);
    timeLabel->setColour(Label::textColourId, Colours::black);
    timeLabel->setJustificationType(Justification::centred);
    timeLabel->setBounds(x, y + SLIDER_SIZE * 0.9, SLIDER_SIZE, SLIDER_SIZE / 3);
    addAndMakeVisible(timeLabel);
    mLabels.add(timeLabel);
    
    x = x + SLIDER_SIZE + SLIDER_INTERVAL;
    
    RotarySlider* feedbackSlider = new RotarySlider(mProcessor->parameters,
                                                    Parameter_DelayFeedback);
    feedbackSlider->setColour(Slider::thumbColourId, Colours::black);
    feedbackSlider->setBounds(x, y, SLIDER_SIZE, SLIDER_SIZE);
    addAndMakeVisible(feedbackSlider);
    mSliders.add(feedbackSlider);
    
    Label* feedbackLabel = new Label();
    feedbackLabel->setFont(Font(16.0f, Font::bold));
    feedbackLabel->setText("Feedback", dontSendNotification);
    feedbackLabel->setColour(Label::textColourId, Colours::black);
    feedbackLabel->setJustificationType(Justification::centred);
    feedbackLabel->setBounds(x, y + SLIDER_SIZE * 0.9, SLIDER_SIZE, SLIDER_SIZE / 3);
    addAndMakeVisible(feedbackLabel);
    mLabels.add(feedbackLabel);
    
    x = SLIDER_POS_X;
    y = y + SLIDER_SIZE + SLIDER_INTERVAL;

    RotarySlider* wetdrySlider = new RotarySlider(mProcessor->parameters,
                                                  Parameter_DelayWetDry);
    wetdrySlider->setColour(Slider::thumbColourId, Colours::black);
    wetdrySlider->setBounds(x, y, SLIDER_SIZE, SLIDER_SIZE);
    addAndMakeVisible(wetdrySlider);
    mSliders.add(wetdrySlider);
    
    Label* wetdryLabel = new Label();
    wetdryLabel->setFont(Font(16.0f, Font::bold));
    wetdryLabel->setText("Wet/Dry", dontSendNotification);
    wetdryLabel->setColour(Label::textColourId, Colours::black);
    wetdryLabel->setJustificationType(Justification::centred);
    wetdryLabel->setBounds(x, y + SLIDER_SIZE * 0.9, SLIDER_SIZE, SLIDER_SIZE / 3);
    addAndMakeVisible(wetdryLabel);
    mLabels.add(wetdryLabel);
}

FXPanel::~FXPanel()
{
    
}
    
void FXPanel::paint(Graphics& g)
{
    
}

