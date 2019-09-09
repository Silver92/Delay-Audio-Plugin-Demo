/*
  ==============================================================================

    Slider.cpp
    Created: 6 Sep 2019 7:11:44am
    Author:  Silver

  ==============================================================================
*/

#include "Rotary_Slider.h"

RotarySlider::RotarySlider()
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    setRange(0.0f, 1.0f, 0.001f);
}

RotarySlider::~RotarySlider()
{
    
}
