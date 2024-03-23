#pragma once
#include "SynthSound.h"
#include <JuceHeader.h>

class SynthVoice : public juce::SynthesiserVoice {
public:
  bool canPlaySound(juce::SynthesiserSound *sound) { return true; }

  void startNote(int midiNoteNumber, float velocity,
                 juce::SynthesiserSound *sound, int currentPitchWheelPosition) {

  }

  void stopNote(float velocity, bool allowTailOff) {}

  void pitchWheelMoved(int newPitchWheelValue) {}

  void controllerMoved(int controllerNumber, int newControllerValue) {}

  void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample,
                       int numSamples) {}

private:
};