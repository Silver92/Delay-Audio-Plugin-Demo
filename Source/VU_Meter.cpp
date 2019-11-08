/*
  ==============================================================================

    VU_Meter.cpp
    Created: 6 Sep 2019 7:11:37am
    Author:  Silver

  ==============================================================================
*/

#include "VU_Meter.h"
#include "MyLookAndFeel.h"

VUMeter::VUMeter(MyDelayPluginAudioProcessor* inProcessor)
:   mParameterID(-1),
    mCh0Level(0),
    mCh1Level(0),
    mProcessor(inProcessor)
{
    
}

VUMeter::~VUMeter()
{
    
}

void VUMeter::paint(Graphics& g)
{
    g.setColour(Colour_6);
    g.fillRect(0, 0, VUMETER_WIDTH, getHeight());
    g.fillRect(VUMETER_WIDTH * 1.1, 0, VUMETER_WIDTH, getHeight());
    
    int ch0Fill = getHeight() - (getHeight() * mCh0Level);
    int ch1Fill = getHeight() - (getHeight() * mCh1Level);
    
    if (ch0Fill < 0) { ch0Fill = 0; }
    if (ch1Fill < 0) { ch1Fill = 0; }
    
    g.setColour(Colour_7);
    g.fillRect(0, ch0Fill, VUMETER_WIDTH, getHeight());
    g.fillRect(VUMETER_WIDTH * 1.1, ch1Fill, VUMETER_WIDTH, getHeight());
}

void VUMeter::timerCallback()
{
    float updatedCh0Level = 0.0f;
    float updatedCh1Level = 0.0f;
    
    switch (mParameterID) {
            
        case Parameter_InputGain:
            updatedCh0Level = mProcessor->getInputRMSGainMeterLevel(0);
            updatedCh1Level = mProcessor->getInputRMSGainMeterLevel(1);
            break;
            
        case Parameter_OutputGain:
            updatedCh0Level = mProcessor->getOutputRMSGainMeterLevel(0);
            updatedCh1Level = mProcessor->getOutputRMSGainMeterLevel(1);
            break;
            
    }
    
    if (updatedCh0Level > mCh0Level) {
        mCh0Level = updatedCh0Level;
    } else {
        mCh0Level = MeterSmoothingCoeff * (mCh0Level - updatedCh0Level) + updatedCh0Level;
    }

    if (updatedCh1Level > mCh1Level) {
        mCh1Level = updatedCh1Level;
    } else {
        mCh1Level = MeterSmoothingCoeff * (mCh1Level - updatedCh1Level) + updatedCh1Level;
    }
    
    mCh0Level = denormalize(mCh0Level);
    mCh1Level = denormalize(mCh1Level);
    
    if (mCh0Level && mCh1Level) { repaint(); }
}

void VUMeter::setParameterID(int inParameterID)
{
    mParameterID = inParameterID;
    
    startTimerHz(1000);
}
