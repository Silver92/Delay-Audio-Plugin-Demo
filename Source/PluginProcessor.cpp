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
                       )
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
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        mInputGain[channel]->process(channelData,
                                     0.5f,
                                     channelData,
                                     buffer.getNumSamples());
        
        mDelay[channel]->process(channelData,
                                 0.5f,
                                 0.2f, // feedback
                                 0.5f,
                                 channelData,
                                 buffer.getNumSamples());
        
        mOutputGain[channel]->process(channelData,
                                     0.5f,
                                     channelData,
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
}

void MyDelayPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void MyDelayPluginAudioProcessor::initialization()
{
    for (int i = 0; i < inputChannels; i++) {
        mInputGain[i].reset(new Gain());
        mOutputGain[i].reset(new Gain());
        mDelay[i].reset(new Delay());
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyDelayPluginAudioProcessor();
}
