/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

#include "Main_Panel.h"
#include "MyLookAndFeel.h"

//==============================================================================
/**
*/
class MyDelayPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    MyDelayPluginAudioProcessorEditor (MyDelayPluginAudioProcessor&);
    ~MyDelayPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MyDelayPluginAudioProcessor& processor;
    
    std::unique_ptr<MainPanel> mMainPanel;
    std::unique_ptr<MyLookAndFeel> mLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyDelayPluginAudioProcessorEditor)
};
