/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <maximilian.h>

//==============================================================================
/**
 */
class JucepluginAudioProcessor : public juce::AudioProcessor {
public:
  //==============================================================================
  JucepluginAudioProcessor();
  ~JucepluginAudioProcessor() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

  float mGain{-6.0};
  int mPitch{0};

  void ksRenderNextBlock(juce::AudioBuffer<float> &outputBuffer,
                         int startSample, int numSamples);
  void startKarplusStrong(float decay, float delay, float width);

private:
  maxiOsc osc1;

  double lastSampleRate;

  bool karplusPlaying = false;
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JucepluginAudioProcessor)
};

class FeedbackDelayProcessor {
public:
  FeedbackDelayProcessor() {
    for (int i = 0; i < buffer_size; i++) {
      delayBuffer[i] = 0.0f;
    }

    readPtr = 0;
    writePtr = 0;
  }

private:
  static const int buffer_size = 1024;

  float delayBuffer[buffer_size];
  int readPtr = 0;
  int writePtr = 0;

  float gain = 0.9f;
  float delayTime = 10.0f;
};
