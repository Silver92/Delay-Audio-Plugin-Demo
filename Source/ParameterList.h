/*
  ==============================================================================

    ParameterList.h
    Created: 9 Sep 2019 10:06:27am
    Author:  Silver

  ==============================================================================
*/

#pragma once

enum Parameter
{
    Parameter_InputGain = 0,
    Parameter_DelayTime,
    Parameter_TimeSliderType,
    Parameter_DelayFeedback,
    Parameter_DelayDryWet,
    Parameter_OutputGain,
    Parameter_TotalNumParameters,
};

static String ParameterID [Parameter_TotalNumParameters] =
{
    "InputGain",
    "Time",
    "TimeSliderType",
    "Feedback",
    "DryWet",
    "OutputGain",
};


static String ParameterLabel [Parameter_TotalNumParameters] =
{
    "Input",
    "Time",
    "ChangeMode",
    "Feedback",
    "Dry/Wet",
    "Output",
};

static float ParameterDefaultVal [Parameter_TotalNumParameters] =
{
    0.5,
    0.0,
    0.0,
    0.0,
    0.0,
    0.5,
};
