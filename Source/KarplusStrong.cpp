/*
  ==============================================================================

    KarplusStrong.cpp
    Created: 23 Mar 2024 7:41:30pm
    Author:  e

  ==============================================================================
*/

#include "KarplusStrong.h"
#include <iostream>

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

void KarplusStrong::setBlockSize(int newBlock) { blockSize = newBlock; }

void KarplusStrong::generateWhiteNoise(float *input, int inputSize) {
  for (int i = 0; i < inputSize; i++) {
    input[i] = ((float)rand() / (float)(RAND_MAX / 1.0f) * 2 - 1) * 0.5;
  }
}

void KarplusStrong::generateGainArray(float *input, int inputSize) {
  for (int i = 0; i < inputSize; i++) {
    input[i] = gain;
    if (gain > 0.00001f) {
      gain -= gainDecay;
    } else {
      gain = 0.0f;
    }
  }
}

bool KarplusStrong::process(float *output, int outputLength) {

  float input[1024];
  generateWhiteNoise(input, bufferSize);

  int delaySamples =
      floor((double)(lastSampleRate * delayTime) / (double)1000.0f);

  for (int i = 0; i < outputLength; i++) {
    output[i] = decay * delayBuffer[readPtr] + input[i];

    // std::cout << "Sample rate is " << lastSampleRate << "\n";
    // std::cout << "input[" << i << "] is " << input[i] << "\n";
    // std::cout << "output[" << i << "] is " << output[i] << "\n";

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

  float gains[outputBuffer.getNumSamples()];
  generateGainArray(gains, outputBuffer.getNumSamples());

  setBlockSize(outputBuffer.getNumSamples());
  outputBuffer.clear();
  for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
    auto *output = outputBuffer.getWritePointer(channel);
    process(output, outputBuffer.getNumSamples());

    for (int i = 0; i < outputBuffer.getNumSamples(); i++) {
      output[i] *= gains[i];
      if (gains[i] > 0.0000001f) {
        std::cout << "Gain is " << gains[i] << "\n";
        std::cout << "Output is " << output[i] << "\n";
      }
    }
  }
  // std::cout << "Gain is " << gain << "\n";
}

void KarplusStrong::playNote() {
  double newDelay =
      delay + ((1000 * (double)blockSize) / (double)lastSampleRate);
  delayTime = newDelay;

  std::cout << "new delay " << newDelay << "\n";

  double secondsUntilQuiet = (double)width / (double)1000.0f;
  double samplesUntilQuiet = lastSampleRate * secondsUntilQuiet;
  double blocksUntilQuiet = samplesUntilQuiet / blockSize;

  std::cout << "Sample rate is " << lastSampleRate;
  std::cout << secondsUntilQuiet << " seconds until quiet\n";
  std::cout << samplesUntilQuiet << " samples until quiet\n";
  std::cout << blocksUntilQuiet << " blocks until quiet\n";

  gainDecay = PEAK_GAIN / samplesUntilQuiet;
  gain = PEAK_GAIN;
}

void KarplusStrong::startKarplusStrong(double newDecay, double newDelay,
                                       double newWidth) {
  decay = (double)newDecay;
  delay = (double)newDelay;
  width = (double)newWidth;

  std::cout << "decay " << decay << "\n";
  std::cout << "delay " << delay << "\n";
  std::cout << "width " << width << "\n";
  playNote();
}