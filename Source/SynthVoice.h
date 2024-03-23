#pragma once
#include "SynthSound.h"
#include <JuceHeader.h>
#include <maximilian.h>

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

private:
  maxiOsc osc1;
  double level = 0;
};