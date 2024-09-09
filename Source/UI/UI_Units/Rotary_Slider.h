/*
  ==============================================================================

    Slider.h
    Created: 6 Sep 2019 7:11:44am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "ParameterList.h"
using namespace juce;

class RotarySlider
:   public Slider
{
public:
    
    RotarySlider(AudioProcessorValueTreeState& stateToControl,
                 int parameterName);
    
    ~RotarySlider();
    
    void setInterval();
    
private:
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotarySlider);
};
