#pragma once
#include "SynthSound.h"
#include <JuceHeader.h>
#include <maximilian.h>

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

class SynthVoice : public juce::SynthesiserVoice {
public:
  bool canPlaySound(juce::SynthesiserSound *sound) {
    return dynamic_cast<SynthSound *>(sound) != nullptr;
  }

  void startNote(int midiNoteNumber, float velocity,
                 juce::SynthesiserSound *sound, int currentPitchWheelPosition) {
    level = 0.05;
  }

  void stopNote(float velocity, bool allowTailOff) { level = 0; }

  void pitchWheelMoved(int newPitchWheelValue) {}

  void controllerMoved(int controllerNumber, int newControllerValue) {}

  void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample,
                       int numSamples) {
    for (int sample = 0; sample < numSamples; ++sample) {
      double theWave = osc1.sinewave(440.0f) * level;

      for (int channel = 0; channel < outputBuffer.getNumChannels();
           ++channel) {
        outputBuffer.addSample(channel, startSample, theWave);
      }

      ++startSample;
    }
  }

  float decay;
  float delay;
  float width;

private:
  maxiOsc osc1;
  double level = 0;
};