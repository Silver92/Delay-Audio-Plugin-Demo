/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyDelayPluginAudioProcessor::MyDelayPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        parameters(*this,                               /** reference to processor **/
                   nullptr,                             /** null pointer to undoManager **/
                   juce::Identifier("Parameters"),      /** valueTree identifier **/
                   createParameterLayout())             /** initialize parameters **/
#endif
{
    initialization();
}

MyDelayPluginAudioProcessor::~MyDelayPluginAudioProcessor()
{
}

//==============================================================================
const String MyDelayPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyDelayPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyDelayPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyDelayPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyDelayPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyDelayPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyDelayPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyDelayPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String MyDelayPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyDelayPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MyDelayPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < inputChannels; i++) {
        mDelay[i]->setSampleRate(sampleRate);
    }
}

void MyDelayPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    for (int i = 0; i < inputChannels; i++) {
        mDelay[i]->reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyDelayPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MyDelayPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    playHead = this->getPlayHead();
    playHead->getCurrentPosition(currentPositionInfo);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        auto inputGain = *parameters.getRawParameterValue(ParameterID[Parameter_InputGain]);
        auto delayTime = *parameters.getRawParameterValue(ParameterID[Parameter_DelayTime]);
        auto delayType = *parameters.getRawParameterValue(ParameterID[Parameter_TimeSliderType]);
        auto delayFeedback = *parameters.getRawParameterValue(ParameterID[Parameter_DelayFeedback]);
        auto delayDryWet = *parameters.getRawParameterValue(ParameterID[Parameter_DelayDryWet]);
        auto outputGain = *parameters.getRawParameterValue(ParameterID[Parameter_OutputGain]);
        
        mInputGain[channel]->process(channelData,
                                     inputGain,
                                     channelData,
                                     buffer.getNumSamples());
        
        mInputGainRMS[channel] = buffer.getRMSLevel(channel,
                                                    channelData[0],
                                                    buffer.getNumSamples());
        
        if (delayType) {
            delayTime = NoteTypeValue[static_cast<int>(delayTime * (NoteType_TotalNumNoteTypes - 1))]
                        / currentPositionInfo.bpm;
            delayTime = jlimit(0.05f, 2.0f, delayTime);
        }
        else {
            delayTime = jmap(delayTime, 0.0f, 1.0f, 0.05f, 2.0f);
        }
        
        mDelay[channel]->process(channelData,
                                 delayTime,
                                 delayFeedback,
                                 delayDryWet,
                                 channelData,
                                 buffer.getNumSamples());
        
        mOutputGain[channel]->process(channelData,
                                      outputGain,
                                      channelData,
                                      buffer.getNumSamples());
        
        mOutputGainRMS[channel] = buffer.getRMSLevel(channel,
                                               channelData[0],
                                               buffer.getNumSamples());

    }
}

//==============================================================================
bool MyDelayPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MyDelayPluginAudioProcessor::createEditor()
{
    return new MyDelayPluginAudioProcessorEditor (*this);
}

//==============================================================================
void MyDelayPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    XmlElement preset("StateInfo");
    XmlElement* presetBody = new XmlElement("Preset");
    
    mPresetManager->getXmlForPreset(presetBody);
    preset.addChildElement(presetBody);
    copyXmlToBinary(preset, destData);
}

void MyDelayPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<XmlElement> xmlState = getXmlFromBinary(data, sizeInBytes);
    
    if (xmlState) {
        forEachXmlChildElement(*xmlState, subChild) {
            mPresetManager->loadPresetForXml(subChild);
        }
    } else {
        jassertfalse;
    }
}

//==============================================================================
float MyDelayPluginAudioProcessor::getInputGainMeterLevel (int inChannel)
{
    const float normalizeddB = dBToNormalizedGain(mInputGain[inChannel]->getMeterLevel());
    return normalizeddB;
}

float MyDelayPluginAudioProcessor::getOutputGainMeterLevel (int inChannel)
{
    const float normalizeddB = dBToNormalizedGain(mOutputGain[inChannel]->getMeterLevel());
    return normalizeddB;
}

float MyDelayPluginAudioProcessor::getInputRMSGainMeterLevel(int inChannel)
{
    const float normalizeddB = dBToNormalizedGain(mInputGainRMS[inChannel]);
    return normalizeddB;
}

float MyDelayPluginAudioProcessor::getOutputRMSGainMeterLevel (int inChannel)
{
    const float normalizeddB = dBToNormalizedGain(mOutputGainRMS[inChannel]);
    return normalizeddB;
}

void MyDelayPluginAudioProcessor::initialization()
{
    for (int i = 0; i < inputChannels; i++) {
        mInputGain[i].reset(new Gain());
        mOutputGain[i].reset(new Gain());
        mDelay[i].reset(new Delay());
    }
    
    mPresetManager.reset(new PresetManager(this));
}

AudioProcessorValueTreeState::ParameterLayout MyDelayPluginAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<AudioParameterFloat>> params;
    using mParameter = AudioProcessorValueTreeState::Parameter;
    
    for (int i = 0; i < Parameter_TotalNumParameters; i++){
        params.push_back(std::make_unique<mParameter>(ParameterID[i],                           /**Parameter ID*/
                                                      ParameterID[i],                           /**Parameter Name*/
                                                      ParameterLabel[i],                        /**labelText*/
                                                      NormalisableRange<float>(0.0f, 1.0f),
                                                      ParameterDefaultVal[i],
                                                      nullptr,
                                                      nullptr));
    }
    
    return {params.begin(), params.end()};
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyDelayPluginAudioProcessor();
}
