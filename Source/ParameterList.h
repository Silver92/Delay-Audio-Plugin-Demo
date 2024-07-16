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

static String MyParameterID [Parameter_TotalNumParameters] =
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

enum NoteType
{
    NoteType_1_16_Triplet = 0,
    NoteType_1_32_Dotted,
    NoteType_1_16,
    NoteType_1_8_Triplet,
    NoteType_1_16_Dotted,
    NoteType_1_8,
    NoteType_1_4_Triplet,
    NoteType_1_8_Dotted,
    NoteType_1_4,
    NoteType_1_2_Triplet,
    NoteType_1_4_Dotted,
    NoteType_1_2,
    NoteType_1_1_Triplet,
    NoteType_1_2_Dotted,
    NoteType_TotalNumNoteTypes
};

static String NoteTypeLabel [NoteType_TotalNumNoteTypes] =
{
    "1/16 Triplet",
    "1/32 Dotted",
    "1/16",
    "1/8 Triplet",
    "1/16 Dotted",
    "1/8",
    "1/4 Triplet",
    "1/8 Dotted",
    "1/4",
    "1/2 Triplet",
    "1/4 Dotted",
    "1/2",
    "1/1 Triplet",
    "1/2 Dotted"
};

static float NoteTypeValue [NoteType_TotalNumNoteTypes] =
{
    5.f,
    11.25f,
    15.f,
    10.f,
    22.5f,
    30.f,
    20.f,
    45.f,
    60.f,
    40.f,
    90.f,
    120.f,
    80.f,
    180.f
};
