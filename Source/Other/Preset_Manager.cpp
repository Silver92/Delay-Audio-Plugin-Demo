/*
  ==============================================================================

    Preset_Manager.cpp
    Created: 6 Sep 2019 7:12:23am
    Author:  Silver

  ==============================================================================
*/

#include "Preset_Manager.h"

#if JUCE_WINDOWS
static const String directorySeparator = "\\";
#elif JUCE_MAC
static const String directorySeparator = "/";
#endif

PresetManager::PresetManager(AudioProcessor* inProcessor)
:   mCurrentPresetName("Unititled"),
    mProcessor(inProcessor),
    mCurrentPresetIsSaved(false)
{
    createStoringPath();
    storeLocalPreset();
}

void PresetManager::createStoringPath() {
    const String pluginName = (String) mProcessor->getName();
    mPresetDirectory =
    (File::getSpecialLocation(File::userApplicationDataDirectory)).getFullPathName() +
    directorySeparator + "Audio" + directorySeparator + "Presets" + directorySeparator +
    "Silver" + directorySeparator + pluginName;
    
    if (!File(mPresetDirectory).exists()) {
        File(mPresetDirectory).createDirectory();
    }
}

void PresetManager::storeLocalPreset()
{
    mLocalPresets.clear();
    
    for (DirectoryIterator di (File(mPresetDirectory),
                               false,
                               "*"+(String)PRESET_FILE_EXTENSION,
                               File::TypesOfFileToFind::findFiles); di.next();)
    {
        File preset = di.getFile();
        mLocalPresets.add(preset);
    }
}

PresetManager::~PresetManager()
{
    
}

void PresetManager::getXmlForPreset(XmlElement* inElement)
{
    auto& parameters = mProcessor->getParameters();
    const int numParameters = parameters.size();
    
    for (int i = 0; i < numParameters; i++) {
        AudioProcessorParameterWithID* parameter =
        (AudioProcessorParameterWithID*) parameters.getUnchecked(i);
        
        inElement->setAttribute(parameter->paramID,
                                parameter->getValue());
    }
}

void PresetManager::loadPresetForXml(XmlElement* inElement)
{
    mCurrentPresetXml = inElement;
    
    auto& parameters = mProcessor->getParameters();
    const int numParameters = parameters.size();
    
    auto numAttributes = mCurrentPresetXml->getNumAttributes();
    
    for (int i = 0; i < numAttributes; i++) {
        const String name = mCurrentPresetXml->getAttributeName(i);
        const float value = mCurrentPresetXml->getDoubleAttribute(name);
        
        for (int j = 0; j < numParameters; j++) {
            AudioProcessorParameterWithID* parameter =
            (AudioProcessorParameterWithID*) parameters.getUnchecked(j);
            
            if (parameter->paramID == name) {
                parameter->setValueNotifyingHost(value);
            }
        }
    }
}


void PresetManager::createNewPreset()
{
    auto parameters = mProcessor->getParameters();
    const int numParameters = parameters.size();
    
    for (int i = 0; i < numParameters; i++) {
        parameters.getUnchecked(i)->
        setValueNotifyingHost(parameters.getUnchecked(i)->getDefaultValue());
    }
    
    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";
}

void PresetManager::savePreset()
{
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    mCurrentlyLoadedPreset.deleteFile();
    mCurrentlyLoadedPreset.appendData(destinationData.getData(),
                                      destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
}

void PresetManager::saveAsPreset(String inPresetName)
{
    File presetFile = File(mPresetDirectory + directorySeparator + inPresetName + PRESET_FILE_EXTENSION);
    
    if (!presetFile.exists()) {
        presetFile.create();
    } else {
        presetFile.deleteFile();
    }
    
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    presetFile.appendData(destinationData.getData(),
                          destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
    mCurrentPresetName = inPresetName;
    
    mLocalPresets.add(presetFile);
}

void PresetManager::loadPreset(int inPresetIndex)
{
    mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];
    
    MemoryBlock presetBinary;
    
    if (mCurrentlyLoadedPreset.loadFileAsData(presetBinary)) {
        mCurrentPresetIsSaved = true;
        mCurrentPresetName = getPresetName(inPresetIndex);
        mProcessor->setStateInformation(presetBinary.getData(),
                                        (int)presetBinary.getSize());
    }
}


int PresetManager::getNumberOfPresets()
{
    return mLocalPresets.size();
}

String PresetManager::getPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

String PresetManager::getCurrentPresetName()
{
    return mCurrentPresetName;
}

bool PresetManager::IsCurrentPresetSaved()
{
    return mCurrentPresetIsSaved;
}
