/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

//==============================================================================
/**
 */
class JucepluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  JucepluginAudioProcessorEditor(JucepluginAudioProcessor &);
  ~JucepluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

private:
  juce::Slider mGainSlider;

  JucepluginAudioProcessor &audioProcessor;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JucepluginAudioProcessorEditor)
};
