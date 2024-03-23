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
class JucepluginAudioProcessorEditor : public juce::AudioProcessorEditor,
                                       juce::Slider::Listener {
public:
  JucepluginAudioProcessorEditor(JucepluginAudioProcessor &);
  ~JucepluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

  void sliderValueChanged(juce::Slider *slider) override;

private:
  juce::Label mGainLabel;
  juce::Label mPitchLabel;

  juce::Label mKPLabel;
  juce::Label mKPDecayLabel;
  juce::Label mKPDelayLabel;
  juce::Label mKPWidthLabel;

  juce::Slider mGainSlider;
  juce::Slider mPitchSlider;

  juce::Slider mKPDecaySlider;
  juce::Slider mKPDelaySlider;
  juce::Slider mKPWidthSlider;

  juce::TextButton mKPStartButton;

  JucepluginAudioProcessor &audioProcessor;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JucepluginAudioProcessorEditor)
};
