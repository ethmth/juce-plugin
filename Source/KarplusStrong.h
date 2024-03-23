/*
  ==============================================================================

    KarplusStrong.h
    Created: 23 Mar 2024 7:41:30pm
    Author:  e

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <maximilian.h>

class KarplusStrong {
public:
  KarplusStrong();

  void setSampleRate(double);

  void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample,
                       int numSamples);
  void startKarplusStrong(float decay, float delay, float width);

private:
  maxiOsc osc1;

  double lastSampleRate;

  static const int buffer_size = 1024;
  float delayBuffer[buffer_size];
  int readPtr = 0;
  int writePtr = 0;

  float gain = 0.9f;
  float delayTime = 10.0f;
};