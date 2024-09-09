/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "UIDemensions.h"

//==============================================================================
MyDelayPluginAudioProcessorEditor::MyDelayPluginAudioProcessorEditor (MyDelayPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    mLookAndFeel = std::make_unique<MyLookAndFeel>();
    setLookAndFeel(mLookAndFeel.get());
    LookAndFeel::setDefaultLookAndFeel(mLookAndFeel.get());

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (MAIN_PANEL_WIDTH,
             MAIN_PANEL_HEIGHT);
    
    mMainPanel.reset(new MainPanel(&processor));
    addAndMakeVisible(mMainPanel.get());
    
}

MyDelayPluginAudioProcessorEditor::~MyDelayPluginAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
    LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void MyDelayPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
}

void MyDelayPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
