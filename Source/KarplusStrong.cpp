/*
  ==============================================================================

    KarplusStrong.cpp
    Created: 23 Mar 2024 7:41:30pm
    Author:  e

  ==============================================================================
*/

#include "KarplusStrong.h"

KarplusStrong::KarplusStrong() {

  for (int i = 0; i < buffer_size; i++) {
    delayBuffer[i] = 0.0f;
  }

  readPtr = 0;
  writePtr = 0;
}

void KarplusStrong::setSampleRate(double sampleRate) {
  lastSampleRate = sampleRate;
}

void KarplusStrong::renderNextBlock(juce::AudioBuffer<float> &outputBuffer,
                                    int startSample, int numSamples) {
  for (int sample = 0; sample < numSamples; ++sample) {
    double theWave = osc1.sinewave(440.0f);

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
      outputBuffer.addSample(channel, startSample, theWave);
    }

    ++startSample;
  }
}

void KarplusStrong::startKarplusStrong(float decay, float delay, float width) {}