/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Gain.h"
#include "Delay.h"
#include "ParameterList.h"
#include "Preset_Manager.h"

//==============================================================================
/**
*/
class MyDelayPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MyDelayPluginAudioProcessor();
    ~MyDelayPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    float getInputGainMeterLevel (int inChannel);
    float getOutputGainMeterLevel (int inChannel);
    float getInputRMSGainMeterLevel (int inChannel);
    float getOutputRMSGainMeterLevel (int inChannel);
    
    AudioProcessorValueTreeState parameters;
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;

private:
    
    void initialization();
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    std::unique_ptr<Gain> mInputGain[2];
    std::unique_ptr<Gain> mOutputGain[2];
    float mInputGainRMS[2];
    float mOutputGainRMS[2];
    std::unique_ptr<Delay> mDelay[2];
    std::unique_ptr<PresetManager> mPresetManager;
    
    int inputChannels = getTotalNumInputChannels();    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyDelayPluginAudioProcessor)
};
