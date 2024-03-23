/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
JucepluginAudioProcessorEditor::JucepluginAudioProcessorEditor(
    JucepluginAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {

  // Gain Slider
  mGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
  mGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 20);
  mGainSlider.setRange(-60.0f, 0.0f, 0.01f);
  mGainSlider.setValue(-6.0f);
  mGainSlider.addListener(this);
  addAndMakeVisible(mGainSlider);

  // Gain Label
  mGainLabel.setText("GAIN", juce::dontSendNotification);
  addAndMakeVisible(mGainLabel);

  // Pitch Slider
  mPitchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
  mPitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
  mPitchSlider.setRange(1, 2, 1);
  mPitchSlider.setValue(1);
  mPitchSlider.addListener(this);
  addAndMakeVisible(mPitchSlider);

  // Pitch Label
  mPitchLabel.setText("PITCH", juce::dontSendNotification);
  addAndMakeVisible(mPitchLabel);

  setSize(400, 300);
}

JucepluginAudioProcessorEditor::~JucepluginAudioProcessorEditor() {}

//==============================================================================
void JucepluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::black);
}

void JucepluginAudioProcessorEditor::resized() {
  // mGainSlider.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 75, 100, 150);

  // mGainSlider.setBounds(25, 25, 150, 100);
  // mPitchSlider.setBounds(225, 50, 100, 75);

  mGainSlider.setBounds(25, getHeight() / 4 - 50, getWidth() / 2 - 50, 100);
  mPitchSlider.setBounds(3 * (getWidth() / 4) - 50, getHeight() / 4 - 40, 100,
                         80);

  mGainLabel.setBounds(25, 25, 100, 25);
  mPitchLabel.setBounds(getWidth() / 2, 25, 100, 25);
}

void JucepluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
  if (slider == &mGainSlider) {
    audioProcessor.mGain = mGainSlider.getValue();
  }
}
