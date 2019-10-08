/*
  ==============================================================================

    Slider_Text.cpp
    Created: 24 Sep 2019 4:00:24pm
    Author:  Silver

  ==============================================================================
*/

#include "Slider_Text.h"

SliderText::SliderText(MyDelayPluginAudioProcessor* inProcessor)
:   mParameterID(-1),
    mProcessor(inProcessor)
{
    setFont(Font(16.0f, Font::bold));
    setColour(Label::textColourId, Colours::black);
    setJustificationType(Justification::centred);
    setEditable(false, true, true);
}

SliderText::~SliderText()
{
    
}

//void SliderText::paint(Graphics& g)
//{
//    g.setColour(Colours::black);
//    g.drawRect(0, 0, getWidth(), getHeight());
//}

void SliderText::timerCallback()
{
    auto val = *(mProcessor->parameters.
                 getRawParameterValue(ParameterID[mParameterID]));
    setText(String(val).substring(0, 4), dontSendNotification);
    setJustificationType(Justification::centred);
}

void SliderText::setParameterID(int inParameterID)
{
    mParameterID = inParameterID;
    startTimer(10);
}
