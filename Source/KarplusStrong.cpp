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

void KarplusStrong::setBlockSize(int newBlock) { blockSize = newBlock; }

void KarplusStrong::generateWhiteNoise(float *input, int inputSize) {

  for (int i = 0; i < inputSize; i++) {
    input[i] = ((float)rand() / (float)(RAND_MAX / 1.0f) * 2 - 1) * 0.5;
  }
}

void KarplusStrong::generateNoiseEnv(float *input, int inputSize) {

  float whitenoise[inputSize];
  generateWhiteNoise(whitenoise, inputSize);

  float gains[inputSize];
  generateGainArray(gains, inputSize);

  for (int i = 0; i < inputSize; i++) {
    input[i] = whitenoise[i] * gains[i];
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

bool KarplusStrong::process(float *output, int outputLength, float *input,
                            int inputLength) {

  int delaySamples =
      floor((double)(lastSampleRate * delayTime) / (double)1000.0f);

  for (int i = 0; i < outputLength; i++) {
    output[i] = decay * delayBuffer[readPtr] + input[i];

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

  float noiseenv[outputBuffer.getNumSamples()];
  generateNoiseEnv(noiseenv, outputBuffer.getNumSamples());

  setBlockSize(outputBuffer.getNumSamples());
  outputBuffer.clear();
  for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
    auto *output = outputBuffer.getWritePointer(channel);
    process(output, outputBuffer.getNumSamples(), noiseenv,
            outputBuffer.getNumSamples());

    for (int i = 0; i < outputBuffer.getNumSamples(); i++) {
      output[i] += noiseenv[i];
    }
  }
}

void KarplusStrong::playNote() {
  double newDelay =
      delay + ((1000 * (double)blockSize) / (double)lastSampleRate);
  delayTime = newDelay;

  double secondsUntilQuiet = (double)width / (double)1000.0f;
  double samplesUntilQuiet = lastSampleRate * secondsUntilQuiet;
  double blocksUntilQuiet = samplesUntilQuiet / blockSize;

  gainDecay = PEAK_GAIN / samplesUntilQuiet;
  gain = PEAK_GAIN;
}

void KarplusStrong::startKarplusStrong(double newDecay, double newDelay,
                                       double newWidth) {
  decay = (double)newDecay;
  delay = (double)newDelay;
  width = (double)newWidth;

  playNote();
}