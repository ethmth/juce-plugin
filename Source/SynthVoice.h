#pragma once
#include "SynthSound.h"
#include <JuceHeader.h>

class SynthVoice : public juce::SynthesiserVoice {
public:
  bool canPlaySound(juce::SynthesiserSound *sound) {
    return dynamic_cast<SynthSound *>(sound) != nullptr;
  }

  void startNote(int midiNoteNumber, float velocity,
                 juce::SynthesiserSound *sound, int currentPitchWheelPosition) {
    std::cout << midiNoteNumber << std::endl;
  }

  void stopNote(float velocity, bool allowTailOff) { velocity = 0; }

  void pitchWheelMoved(int newPitchWheelValue) {}

  void controllerMoved(int controllerNumber, int newControllerValue) {}

  void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample,
                       int numSamples) {
    for (int sample = 0; sample < numSamples; ++sample) {
      for (int channel = 0; channel < outputBuffer.getNumChannels();
           ++channel) {
        outputBuffer.addSample(channel, startSample, 0);
      }

      ++startSample;
    }
  }

private:
};