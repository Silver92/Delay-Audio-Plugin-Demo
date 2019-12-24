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
    // Set up the positions of the UI components
    
    int x = SLIDER_POS_X;
    int y = SLIDER_POS_Y;
    
//    SetTimeSlider(mTimeSliderStyle);
    
    mTimeSliderTypeButton.reset(
    new ParameterButton(mProcessor->parameters, ParameterID[Parameter_TimeSliderType]));
    mTimeSliderTypeButton->setBounds(x + SLIDER_SIZE + SLIDER_INTERVAL,
                                     y - SLIDER_SIZE/5,
                                     SLIDER_SIZE,
                                     SLIDER_SIZE);
    auto index = mProcessor->getParameters().getUnchecked(Parameter_TimeSliderType);
    mTimeSliderTypeButton->setButtonState(index->getValue());
    mTimeSliderTypeButton->onClick = [this, x, y]{
        
        if (mTimeSliderTypeButton->getButtonState()) {
            // Delete the previous button
            if (!mSliders.isEmpty()) {
                for (int i = 0; i < mSliders.size(); i++) {
                    if (mSliders[i]->getName() ==
                        ParameterID[Parameter_DelayTime]) {
                        
                    }
                }
            }
            
        } else {
            // Delete the previous button
            if (!mSliders.isEmpty()) {
                for (int i = 0; i < mSliders.size(); i++) {
                    if (mSliders[i]->getName() ==
                        ParameterID[Parameter_DelayTime]) {
                        mSliders.remove(i);
                        mSliderTexts.remove(i);
                    }
                }
            }
            drawSlider(x, y, Parameter_DelayTime);
            drawSliderText(x, y, Parameter_DelayTime, 0.05f, 2.0f, "s");
        }
    };
    addAndMakeVisible(mTimeSliderTypeButton.get());
    drawSliderLabel(x, y, Parameter_DelayTime);
    
    //=================================================================================
    
    y = y + SLIDER_SIZE + SLIDER_INTERVAL;
    
    drawSlider(x, y, Parameter_DelayFeedback);
    drawSliderLabel(x, y, Parameter_DelayFeedback);
    drawSliderText(x, y, Parameter_DelayFeedback, 0.f, 100.f, "%");
    
    //=================================================================================
    
    x = x + SLIDER_SIZE + SLIDER_INTERVAL;

    drawSlider(x, y, Parameter_DelayDryWet);
    drawSliderLabel(x, y, Parameter_DelayDryWet);
    drawSliderText(x, y, Parameter_DelayDryWet, 0.0f, 100.f, "%");
    
    //=================================================================================
    
    // Make the interactions between sliders and slider texts
    for (int i = 0; i < mSliders.size(); i++)
    {
        auto val = *(mProcessor->parameters.
        getRawParameterValue(ParameterID[mSliderTexts[i]->getParameterID()]));
        val = jmap(val, mSliderTexts[i]->getMinRange(), mSliderTexts[i]->getMaxRange());
        String tempString = (mSliderTexts[i]->getParameterID() == Parameter_DelayTime) ?
        String(val, 2) : String(static_cast<int>(val));
        mSliderTexts[i]->setText(tempString + mSliderTexts[i]->getUnit(), dontSendNotification);
        mSliderTexts[i]->setJustificationType(Justification::centred);
    
        //=================================================================================
        // Set up the right text and the values on each slider text and slider when the user
        // changes the slider text
        mSliderTexts[i]->onTextChange = [this, i]{
            auto maxVal = mSliderTexts[i]->getMaxRange();
            auto minVal = mSliderTexts[i]->getMinRange();
            auto currentVal = mSliderTexts[i]->getText().getFloatValue();
            if (currentVal >= maxVal) {
                mSliderTexts[i]->setText(String(maxVal, 2) +
                mSliderTexts[i]->getUnit(),
                dontSendNotification);
            }
            else if (currentVal <= minVal) {
                mSliderTexts[i]->setText(String(minVal, 2) +
                mSliderTexts[i]->getUnit(),
                dontSendNotification);
            }
            else {
                currentVal = jmap(currentVal,
                minVal,
                maxVal,
                static_cast<float>(mSliders[i]->getMinimum()),
                static_cast<float>(mSliders[i]->getMaximum()));
            }
            
            if (mSliders[i]->getValue() == currentVal) {
                auto tempVal = jmap(currentVal,
                                    static_cast<float>(mSliders[i]->getMinimum()),
                                    static_cast<float>(mSliders[i]->getMaximum()),
                                    minVal,
                                    maxVal);
                String tempString = (mSliderTexts[i]->getParameterID() == Parameter_DelayTime) ?
                String(tempVal, 2) : String(static_cast<int>(tempVal));
                mSliderTexts[i]->setText(tempString +
                                         mSliderTexts[i]->getUnit(),
                                         dontSendNotification);
            }
            
            mSliders[i]->setValue(currentVal);
        };
        
        //=================================================================================
        // Set up the right text and the values on each slider text and slider when the user
        // changes the sliders
        mSliders[i]->onValueChange = [this, i]{
            auto val = *(mProcessor->parameters.
            getRawParameterValue(ParameterID[mSliderTexts[i]->getParameterID()]));
            val = jmap(val,
                       mSliderTexts[i]->getMinRange(),
                       mSliderTexts[i]->getMaxRange());
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
    text->setBounds(x + SLIDER_SIZE * 0.1,
                    y - SLIDER_SIZE / 4 + 5,
                    SLIDER_SIZE * 0.8,
                    SLIDER_SIZE / 4);
    addAndMakeVisible(text);
    mSliderTexts.add(text);
}

void FXPanel::SetTimeSlider(TimeSliderStyle inStyle) {
    
    mTimeSliderStyle = inStyle;
    int x = SLIDER_POS_X;
    int y = SLIDER_POS_Y;
    
    // clean the slider and slider text vectors
    
    
    switch (inStyle) {
        case (TimeSliderStyle_Time):{
            drawSlider(x, y, Parameter_DelayTime);
            drawSliderLabel(x, y, Parameter_DelayTime);
            drawSliderText(x, y, Parameter_DelayTime, 0.05f, 2.0f, "s");
        }break;
        case (TimeSliderStyle_Beat):{
            
        }break;
        default:
        case (TimeSliderStyle_TotalNumStyles): {
            jassertfalse;
        }break;
    }
}
