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
  void setBlockSize(int);

  void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample,
                       int numSamples);

  void generateWhiteNoise(float *, int);
  void generateGainArray(float *, int);
  bool process(float *, int);

  void startNote();
  void stopNote();

  void playNote();

  void startKarplusStrong(double decay, double delay, double width);

private:
  const double PEAK_GAIN = 0.1f;

  double lastSampleRate;
  int blockSize;

  double delayTime;
  int readPtr;
  int writePtr;

  static const int bufferSize = 1024;
  float delayBuffer[bufferSize];

  double decay = 0.9f;
  double delay = 10.0f;
  double width = 10.0f;

  double gain = 0.0f;
  double gainDecay;
};