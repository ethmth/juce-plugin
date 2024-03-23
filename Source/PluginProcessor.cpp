/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
JucepluginAudioProcessor::JucepluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(
          BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
      )
#endif
{
}

JucepluginAudioProcessor::~JucepluginAudioProcessor() {}

//==============================================================================
const juce::String JucepluginAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool JucepluginAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool JucepluginAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool JucepluginAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double JucepluginAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int JucepluginAudioProcessor::getNumPrograms() {
  return 1; // NB: some hosts don't cope very well if you tell them there are 0
            // programs, so this should be at least 1, even if you're not really
            // implementing programs.
}

int JucepluginAudioProcessor::getCurrentProgram() { return 0; }

void JucepluginAudioProcessor::setCurrentProgram(int index) {}

const juce::String JucepluginAudioProcessor::getProgramName(int index) {
  return {};
}

void JucepluginAudioProcessor::changeProgramName(int index,
                                                 const juce::String &newName) {}

//==============================================================================
void JucepluginAudioProcessor::prepareToPlay(double sampleRate,
                                             int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
}

void JucepluginAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JucepluginAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
  juce::ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void JucepluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                            juce::MidiBuffer &midiMessages) {
  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  for (int channel = 0; channel < totalNumInputChannels; ++channel) {
    auto *channelData = buffer.getWritePointer(channel);

    // // =========== Karplus Strong ===================

    // // Generate White Noise
    // float white_noise[buffer.getNumSamples()];
    // for (int i = 0; i < buffer.getNumSamples(); i++) {
    //   white_noise[i] = rand() * 2 - 1;

    //   // a lazy lowpass filter
    //   if (i > 0) {
    //     white_noise[i] = white_noise[i] * 0.5 + white_noise[i - 1] * 0.5;
    //   }
    // }

    // ================= Pitch Processing ===================
    if (mPitch > 0) {
      const int sample_jump = pow(2, mPitch);
      const int buff_size = buffer.getNumSamples() / sample_jump;

      float buff[buff_size];

      for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        if (sample % sample_jump == 0) {
          buff[sample / sample_jump] = channelData[sample];
        }
      }

      for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        if (sample % sample_jump == 0) {
          channelData[sample] = buff[sample % buff_size];
        }
      }

    } else if (mPitch < 0) {
      const int sample_jump = pow(2, mPitch * -1);
      float cur_val = 0.0f;

      for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        if (sample % sample_jump == 0) {
          cur_val = channelData[sample];
        } else {
          channelData[sample] = cur_val;
        }
      }
    }

    // =========== Gain Processing =====================
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
      channelData[sample] *= juce::Decibels::decibelsToGain(mGain);
    }
  }
}

//==============================================================================
bool JucepluginAudioProcessor::hasEditor() const {
  return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *JucepluginAudioProcessor::createEditor() {
  return new JucepluginAudioProcessorEditor(*this);
}

//==============================================================================
void JucepluginAudioProcessor::getStateInformation(
    juce::MemoryBlock &destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
}

void JucepluginAudioProcessor::setStateInformation(const void *data,
                                                   int sizeInBytes) {
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new JucepluginAudioProcessor();
}
