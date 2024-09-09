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
    
    //=================================================================================
    mGainLabel.reset(new Label());
    mGainLabel->setFont(Font(18.0f));
    mGainLabel->setText(ParameterLabel[inParameterID], dontSendNotification);
    mGainLabel->setColour(Label::textColourId, Colours::black);
    mGainLabel->setJustificationType(Justification::centred);
    mGainLabel->setBounds(getWidth() * 0.5 - SLIDER_SIZE * 0.5,
                          SLIDER_POS_Y - SLIDER_SIZE * 0.55,
                          SLIDER_SIZE,
                          SLIDER_SIZE / 2);
    addAndMakeVisible(mGainLabel.get());
    
    //=================================================================================
    mSliderText.reset(new SliderText());
    mSliderText->setParameterID(inParameterID);
    mSliderText->setTextRange(-18.f, 18.f);
    mSliderText->setUnit("dB");
    mSliderText->setFont(23.0f);
    mSliderText->setBounds(getWidth() * 0.5 - SLIDER_SIZE * 0.4,
                           SLIDER_POS_Y - SLIDER_SIZE / 4 + 5,
                           SLIDER_SIZE * 0.8,
                           SLIDER_SIZE / 4);
    addAndMakeVisible(mSliderText.get());
    
    //=================================================================================
    auto val = (mProcessor->parameters.
    getRawParameterValue(MyParameterID[mSliderText->getParameterID()]))->load();
    val = jmap<float>(val, mSliderText->getMinRange(), mSliderText->getMaxRange());
    mSliderText->setText(String(val, 1) + mSliderText->getUnit(), dontSendNotification);
    mSliderText->setJustificationType(Justification::centred);
    
    //=================================================================================
    mSliderText->onTextChange = [this]{
        auto maxVal = mSliderText->getMaxRange();
        auto minVal = mSliderText->getMinRange();
        auto currentVal = mSliderText->getText().getFloatValue();
        if      (currentVal >= maxVal) {
            mSliderText->setText(String(maxVal, 1) +
            mSliderText->getUnit(),
            dontSendNotification);
        }
        else if (currentVal <= minVal) {
            mSliderText->setText(String(minVal, 1) +
            mSliderText->getUnit(),
            dontSendNotification);
        }
        else {
            currentVal = jmap(currentVal,
            minVal,
            maxVal,
            static_cast<float>(mGainSlider->getMinimum()),
            static_cast<float>(mGainSlider->getMaximum()));
        }
        
        if (mGainSlider->getValue() == currentVal) {
            auto tempVal = jmap(currentVal,
                                static_cast<float>(mGainSlider->getMinimum()),
                                static_cast<float>(mGainSlider->getMaximum()),
                                minVal,
                                maxVal);
            mSliderText->setText(String(tempVal, 1) +
            mSliderText->getUnit(),
            dontSendNotification);
        }
            
        mGainSlider->setValue(currentVal);
    };
    
    //=================================================================================
    mGainSlider->onValueChange = [this]{
        auto val = (mProcessor->parameters.
        getRawParameterValue(MyParameterID[mSliderText->getParameterID()]))->load();
        val = jmap<float>(val, mSliderText->getMinRange(), mSliderText->getMaxRange());
        mSliderText->setText(String(val, 1) + mSliderText->getUnit(), dontSendNotification);
        mSliderText->setJustificationType(Justification::centred);
    };
}

void GainPanel::initVUMeter(MyDelayPluginAudioProcessor *inProcessor, int inParameterID)
{
    mVUMeter.reset(new VUMeter(inProcessor));
    mVUMeter->setBounds(getWidth() * 0.5 - VUMETER_WIDTH * 1.05,
                        SLIDER_POS_Y + SLIDER_SIZE, 
                        SLIDER_SIZE,
                        getHeight() * 0.4);
    addAndMakeVisible(mVUMeter.get());
    mVUMeter->setParameterID(inParameterID);
}
