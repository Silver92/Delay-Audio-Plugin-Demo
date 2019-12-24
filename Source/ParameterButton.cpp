/*
  ==============================================================================

    ParameterButton.cpp
    Created: 21 Dec 2019 5:16:48pm
    Author:  Silver

  ==============================================================================
*/

#include "ParameterButton.h"

ParameterButton::ParameterButton(AudioProcessorValueTreeState& stateControl, const String& parameterID)
:   juce::TextButton(parameterID)
{
    mAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(stateControl, parameterID, *this));
    buttonState = false;
}

ParameterButton::~ParameterButton()
{
    
}

void ParameterButton::setButtonState(bool inState)
{
    buttonState = inState;
}

bool ParameterButton::getButtonState()
{
    return buttonState;
}
