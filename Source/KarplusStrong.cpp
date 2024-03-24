/*
  ==============================================================================

    KarplusStrong.cpp
    Created: 23 Mar 2024 7:41:30pm
    Author:  e

  ==============================================================================
*/

#include "KarplusStrong.h"

KarplusStrong::KarplusStrong() {

  for (int i = 0; i < bufferSize; i++) {
    delayBuffer[i] = 0.0f;
  }

  readPtr = 0;
  writePtr = 0;
}

void KarplusStrong::setSampleRate(double sampleRate) {
  lastSampleRate = sampleRate;
}

void KarplusStrong::generateWhiteNoise(float *input, int inputSize) {
  for (int i = 0; i < inputSize; i++) {
    input[i] = ((float)rand() / (float)(RAND_MAX / 1.0f) * 2 - 1) * 0.5;
  }
}

bool KarplusStrong::process(float *output, int outputLength) {

  float input[1024];
  generateWhiteNoise(input, bufferSize);

  int delaySamples = floor((lastSampleRate * delay) / 1000);

  for (int i = 0; i < outputLength; i++) {
    output[i] = decay * delayBuffer[readPtr] + input[i];

    std::cout << "Sample rate is " << lastSampleRate << "\n";
    std::cout << "input[" << i << "] is " << input[i] << "\n";
    std::cout << "output[" << i << "] is " << output[i] << "\n";

    // a lazy lowpass filter
    if (i > 0) {
      delayBuffer[writePtr] = output[i] * 0.5 + output[i - 1] * 0.5;
    } else {
      delayBuffer[writePtr] = output[i];
    }

    writePtr = (writePtr + 1) % bufferSize;
    readPtr = writePtr - delaySamples;
    if (readPtr < 0) {
      readPtr = readPtr + bufferSize;
    }
  }

  return true;
}

void KarplusStrong::renderNextBlock(juce::AudioBuffer<float> &outputBuffer,
                                    int startSample, int numSamples) {
  // for (int sample = 0; sample < numSamples; ++sample) {
  //   double theWave = osc1.sinewave(440.0f) * level;

  //   for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
  //   {
  //     outputBuffer.addSample(channel, startSample, theWave);
  //   }

  //   ++startSample;
  // }

  // juce::AudioBuffer<float> delay_buffer = juce::AudioBuffer<float>(
  // outputBuffer.getNumChannels(), outputBuffer.getNumSamples());
  // delay_buffer.clear();
  // renderNextBlock(delay_buffer, 0, outputBuffer.getNumSamples());

  outputBuffer.clear();
  for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
    // auto *output = delay_buffer.getWritePointer(channel);
    auto *output = outputBuffer.getWritePointer(channel);

    // process(output, delay_buffer.getNumSamples());
    process(output, outputBuffer.getNumSamples());
  }
}

void KarplusStrong::startKarplusStrong(float newDecay, float newDelay,
                                       float newWidth) {
  decay = newDecay;
  delay = newDelay;
  width = newWidth;

  // level = 0.05;
}