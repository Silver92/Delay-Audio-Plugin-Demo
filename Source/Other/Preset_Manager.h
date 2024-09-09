/*
  ==============================================================================

    Preset_Manager.h
    Created: 6 Sep 2019 7:12:23am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
using namespace juce;
#define PRESET_FILE_EXTENSION ".kpf"

class PresetManager
{
public:
    
    void extracted();
    
PresetManager(AudioProcessor* inProcessor);
    ~PresetManager();
    
    void getXmlForPreset(XmlElement* inElement);
    
    void loadPresetForXml(XmlElement* inElement);
    
    
    void createNewPreset();
    
    void savePreset();
    
    void saveAsPreset(String inPresetName);
    
    void loadPreset(int inPresetIndex);
    
    
    int getNumberOfPresets();
    
    String getPresetName(int inPresetIndex);
    
    String getCurrentPresetName();
    
    bool IsCurrentPresetSaved();
    
private:
    
    void createStoringPath();
    void storeLocalPreset();
    
    String mCurrentPresetName;
    String mPresetDirectory;
    
    File mCurrentlyLoadedPreset;
    Array<File> mLocalPresets;
    
    AudioProcessor* mProcessor;
    
    XmlElement* mCurrentPresetXml;
    
    bool mCurrentPresetIsSaved;
};
