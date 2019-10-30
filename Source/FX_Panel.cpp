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
    
    //=================================================================================
    
    int x = SLIDER_POS_X;
    int y = SLIDER_POS_Y;
    
    drawSlider(x, y, Parameter_DelayTime);
    drawSliderLabel(x, y, Parameter_DelayTime);
    drawSliderText(x, y, Parameter_DelayTime, 0.05f, 2.0f, "s");
    
    //=================================================================================
    
    x = x + SLIDER_SIZE + SLIDER_INTERVAL;
    
    drawSlider(x, y, Parameter_DelayFeedback);
    drawSliderLabel(x, y, Parameter_DelayFeedback);
    drawSliderText(x, y, Parameter_DelayFeedback, 0.f, 100.f, "%");
    
    //=================================================================================
    
    x = SLIDER_POS_X;
    y = y + SLIDER_SIZE + SLIDER_INTERVAL;

    drawSlider(x, y, Parameter_DelayDryWet);
    drawSliderLabel(x, y, Parameter_DelayDryWet);
    drawSliderText(x, y, Parameter_DelayDryWet, 0.0f, 100.f, "%");
    
    //=================================================================================
    
    for (int i = 0; i < mSliders.size(); i++) {
        auto val = *(mProcessor->parameters.
        getRawParameterValue(ParameterID[mSliderTexts[i]->getParameterID()]));
        val = jmap(val, mSliderTexts[i]->getMinRange(), mSliderTexts[i]->getMaxRange());
        String tempString = (mSliderTexts[i]->getParameterID() == Parameter_DelayTime) ?
        String(val, 2) : String(static_cast<int>(val));
        mSliderTexts[i]->setText(tempString + mSliderTexts[i]->getUnit(), dontSendNotification);
        mSliderTexts[i]->setJustificationType(Justification::centred);
    
        mSliderTexts[i]->onTextChange = [this, i]{
            mSliders[i]->setValue(mSliderTexts[i]->getText().getDoubleValue());
        };
        mSliders[i]->onValueChange = [this, i]{
            auto val = *(mProcessor->parameters.
            getRawParameterValue(ParameterID[mSliderTexts[i]->getParameterID()]));
            val = jmap(val, mSliderTexts[i]->getMinRange(), mSliderTexts[i]->getMaxRange());
            String tempString = (mSliderTexts[i]->getParameterID() == Parameter_DelayTime) ?
            String(val, 2) : String(static_cast<int>(val));
            mSliderTexts[i]->setText(tempString + mSliderTexts[i]->getUnit(), dontSendNotification);
            mSliderTexts[i]->setJustificationType(Justification::centred);
        };
    }
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

void FXPanel::drawSliderText(int x, int y, int parameterIndex, float minRange, float maxRange, String inUnit) {
    SliderText* text = new SliderText();
    text->setParameterID(parameterIndex);
    text->setTextRange(minRange, maxRange);
    text->setUnit(inUnit);
    text->setFont(Font(23.0f));
    text->setBounds(x, y - SLIDER_SIZE * 0.32, SLIDER_SIZE, SLIDER_SIZE / 2);
    addAndMakeVisible(text);
    mSliderTexts.add(text);
}
