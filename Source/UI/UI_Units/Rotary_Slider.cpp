/*
  ==============================================================================

    Slider.cpp
    Created: 6 Sep 2019 7:11:44am
    Author:  Silver

  ==============================================================================
*/

#include "Rotary_Slider.h"
#include "UIDemensions.h"

RotarySlider::RotarySlider(AudioProcessorValueTreeState& stateToControl,
                           int parameterName)
:   juce::Slider(ParameterLabel[parameterName])
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::NoTextBox, false, SLIDER_SIZE, SLIDER_SIZE / 3);
    setRange(0.0f, 1.0f, 0.001f);
    mAttachment.reset(
    new AudioProcessorValueTreeState::SliderAttachment(stateToControl,
                                                       MyParameterID[parameterName],
                                                       *this));
}

RotarySlider::~RotarySlider()
{
    
}

void RotarySlider::setInterval()
{
    setRange(0.0f, 1.0f, 1.f/ 13.f);
}
