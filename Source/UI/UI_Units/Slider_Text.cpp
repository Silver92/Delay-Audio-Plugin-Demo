/*
  ==============================================================================

    Slider_Text.cpp
    Created: 24 Sep 2019 4:00:24pm
    Author:  Silver

  ==============================================================================
*/

#include "Slider_Text.h"

SliderText::SliderText()
:   mParameterID(-1),
    minRange(0.f),
    maxRange(1.f),
    unit("")
{
    setFont(Font(16.0f, Font::bold));
    setColour(Label::textColourId, Colours::black);
    setJustificationType(Justification::centred);
    setEditable(false, true, true);
}

SliderText::~SliderText()
{
    
}

void SliderText::setParameterID(int inParameterID)
{
    mParameterID = inParameterID;
}

void SliderText::setTextRange(float inMinVal, float inMaxVal)
{
    minRange = inMinVal;
    maxRange = inMaxVal;
}

void SliderText::setUnit(String inString)
{
    unit = inString;
}

int SliderText::getParameterID()
{
    return mParameterID;
}

float SliderText::getMinRange()
{
    return minRange;
}

float SliderText::getMaxRange()
{
    return maxRange;
}

String SliderText::getUnit()
{
    return unit;
}

TextEditor* SliderText::createEditorComponent()
{
    TextEditor* textEditor = new TextEditor();
    textEditor->setInputRestrictions(7, "0123456789.-");
    textEditor->setColour(ColourIds::backgroundColourId, Colours::black);
    textEditor->setJustification(Justification::centred);
    
    return textEditor;
}
