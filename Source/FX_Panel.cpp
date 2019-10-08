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
    
    drawSlider(x, y, Parameter_DelayTime);
    drawSliderLabel(x, y, Parameter_DelayTime);
    drawSliderText(inProcessor, x, y, Parameter_DelayTime);
    
    x = x + SLIDER_SIZE + SLIDER_INTERVAL;
    //=================================================================================
    
    drawSlider(x, y, Parameter_DelayFeedback);
    drawSliderLabel(x, y, Parameter_DelayFeedback);
    drawSliderText(inProcessor, x, y, Parameter_DelayFeedback);
    
    x = SLIDER_POS_X;
    y = y + SLIDER_SIZE + SLIDER_INTERVAL;
    //=================================================================================

    drawSlider(x, y, Parameter_DelayDryWet);
    drawSliderLabel(x, y, Parameter_DelayDryWet);
    drawSliderText(inProcessor, x, y, Parameter_DelayDryWet);
}

FXPanel::~FXPanel()
{
    
}
    
void FXPanel::paint(Graphics& g)
{
    
}

void FXPanel::drawSlider(int x, int y, int parameterIndex) {
    RotarySlider* slider = new RotarySlider(mProcessor->parameters,
                                                  parameterIndex);
    slider->setColour(Slider::thumbColourId, Colours::black);
    slider->setBounds(x, y, SLIDER_SIZE, SLIDER_SIZE);
    addAndMakeVisible(slider);
    mSliders.add(slider);
}

void FXPanel::drawSliderLabel(int x, int y, int parameterIndex) {
    Label* label = new Label();
    label->setFont(Font(18.0f));
    label->setText(ParameterLabel[parameterIndex], dontSendNotification);
    label->setColour(Label::textColourId, Colours::black);
    label->setJustificationType(Justification::centred);
    label->setBounds(x, y - SLIDER_SIZE * 0.55, SLIDER_SIZE, SLIDER_SIZE / 2);
    addAndMakeVisible(label);
    mLabels.add(label);
}

void FXPanel::drawSliderText(MyDelayPluginAudioProcessor *inProcessor, int x, int y, int parameterIndex) {
    SliderText* text = new SliderText(inProcessor);
    text->setParameterID(parameterIndex);
    text->setFont(Font(23.0f));
    text->setBounds(x, y - SLIDER_SIZE * 0.32, SLIDER_SIZE, SLIDER_SIZE / 2);
    addAndMakeVisible(text);
    mSliderTexts.add(text);
}
