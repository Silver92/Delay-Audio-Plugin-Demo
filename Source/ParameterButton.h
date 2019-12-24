/*
  ==============================================================================

    ParameterButton.h
    Created: 21 Dec 2019 5:16:48pm
    Author:  Silver

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class ParameterButton
:   public TextButton
{
public:
    ParameterButton(AudioProcessorValueTreeState& stateControl, const String& parameterID);
    ~ParameterButton();
    
    void setButtonState(bool inState);
    bool getButtonState();
    
private:
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> mAttachment;
    bool buttonState;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterButton);
};
