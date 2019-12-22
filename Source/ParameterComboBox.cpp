/*
  ==============================================================================

    ParameterComboBox.cpp
    Created: 21 Dec 2019 5:16:48pm
    Author:  Silver

  ==============================================================================
*/

#include "ParameterComboBox.h"

ParameterComboBox::ParameterComboBox(AudioProcessorValueTreeState& stateControl, const String& parameterID)
:   juce::ComboBox(parameterID)
{
    mAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(stateControl, parameterID, *this));
}

ParameterComboBox::~ParameterComboBox()
{
    
}
