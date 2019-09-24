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
    timeLabel->setText(ParameterLabel[Parameter_DelayTime], dontSendNotification);
    timeLabel->setColour(Label::textColourId, Colours::black);
    timeLabel->setJustificationType(Justification::centred);
    timeLabel->setBounds(x, y + SLIDER_SIZE * 0.9, SLIDER_SIZE, SLIDER_SIZE / 3);
    addAndMakeVisible(timeLabel);
    mLabels.add(timeLabel);
    
    SliderText* timeText = new SliderText(inProcessor);
    timeText->setParameterID(Parameter_DelayTime);
    timeText->setBounds(x, y + SLIDER_SIZE / 4, SLIDER_SIZE, SLIDER_SIZE / 2);
    addAndMakeVisible(timeText);
    mSliderTexts.add(timeText);
    
    x = x + SLIDER_SIZE + SLIDER_INTERVAL;
    //=================================================================================
    
    RotarySlider* feedbackSlider = new RotarySlider(mProcessor->parameters,
                                                    Parameter_DelayFeedback);
    feedbackSlider->setColour(Slider::thumbColourId, Colours::black);
    feedbackSlider->setBounds(x, y, SLIDER_SIZE, SLIDER_SIZE);
    addAndMakeVisible(feedbackSlider);
    mSliders.add(feedbackSlider);
    
    Label* feedbackLabel = new Label();
    feedbackLabel->setFont(Font(16.0f, Font::bold));
    feedbackLabel->setText(ParameterLabel[Parameter_DelayFeedback], dontSendNotification);
    feedbackLabel->setColour(Label::textColourId, Colours::black);
    feedbackLabel->setJustificationType(Justification::centred);
    feedbackLabel->setBounds(x, y + SLIDER_SIZE * 0.9, SLIDER_SIZE, SLIDER_SIZE / 3);
    addAndMakeVisible(feedbackLabel);
    mLabels.add(feedbackLabel);
    
    SliderText* feedbackText = new SliderText(inProcessor);
    feedbackText->setParameterID(Parameter_DelayFeedback);
    feedbackText->setBounds(x, y + SLIDER_SIZE / 4, SLIDER_SIZE, SLIDER_SIZE / 2);
    addAndMakeVisible(feedbackText);
    mSliderTexts.add(feedbackText);
    
    x = SLIDER_POS_X;
    y = y + SLIDER_SIZE + SLIDER_INTERVAL;
    //=================================================================================

    RotarySlider* drywetSlider = new RotarySlider(mProcessor->parameters,
                                                  Parameter_DelayDryWet);
    drywetSlider->setColour(Slider::thumbColourId, Colours::black);
    drywetSlider->setBounds(x, y, SLIDER_SIZE, SLIDER_SIZE);
    addAndMakeVisible(drywetSlider);
    mSliders.add(drywetSlider);
    
    Label* drywetLabel = new Label();
    drywetLabel->setFont(Font(16.0f, Font::bold));
    drywetLabel->setText(ParameterLabel[Parameter_DelayDryWet], dontSendNotification);
    drywetLabel->setColour(Label::textColourId, Colours::black);
    drywetLabel->setJustificationType(Justification::centred);
    drywetLabel->setBounds(x, y + SLIDER_SIZE * 0.9, SLIDER_SIZE, SLIDER_SIZE / 3);
    addAndMakeVisible(drywetLabel);
    mLabels.add(drywetLabel);
    
    SliderText* drywetText = new SliderText(inProcessor);
    drywetText->setParameterID(Parameter_DelayDryWet);
    drywetText->setBounds(x, y + SLIDER_SIZE / 4, SLIDER_SIZE, SLIDER_SIZE / 2);
    addAndMakeVisible(drywetText);
    mSliderTexts.add(drywetText);
}

FXPanel::~FXPanel()
{
    
}
    
void FXPanel::paint(Graphics& g)
{
    
}

