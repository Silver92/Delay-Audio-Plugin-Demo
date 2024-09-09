/*
  ==============================================================================

    ParameterButton.h
    Created: 21 Dec 2019 5:16:48pm
    Author:  Silver

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "ParameterList.h"
using namespace juce;

class ParameterButton
:   public TextButton
{
public:
    ParameterButton(AudioProcessorValueTreeState& stateControl, int parameterName);
    ~ParameterButton();
    
private:
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> mAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterButton);
};
