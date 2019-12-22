/*
  ==============================================================================

    ParameterComboBox.h
    Created: 21 Dec 2019 5:16:48pm
    Author:  Silver

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class ParameterComboBox
:   public ComboBox
{
public:
    ParameterComboBox(AudioProcessorValueTreeState& stateControl, const String& parameterID);
    ~ParameterComboBox();
private:
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterComboBox);
};
