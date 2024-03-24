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

  void generateWhiteNoise(float *, int);
  bool process(float *, int);

  void startKarplusStrong(float decay, float delay, float width);

private:
  double lastSampleRate;

  int readPtr;
  int writePtr;

  float decay = 0.9f;
  float delay = 10.0f;
  float width = 10.0f;

  static const int bufferSize = 1024;
  float delayBuffer[bufferSize];

  // float level = 0;
};