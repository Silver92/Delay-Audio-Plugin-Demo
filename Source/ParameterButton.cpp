/*
  ==============================================================================

    ParameterButton.cpp
    Created: 21 Dec 2019 5:16:48pm
    Author:  Silver

  ==============================================================================
*/

#include "ParameterButton.h"

ParameterButton::ParameterButton(AudioProcessorValueTreeState& stateControl, int parameterName)
:   juce::TextButton(ParameterLabel[parameterName])
{
    mAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(stateControl,
                                                                         MyParameterID[parameterName],
                                                                         *this));
}

ParameterButton::~ParameterButton()
{
    
}
