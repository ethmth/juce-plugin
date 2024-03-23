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

  // Karplus-Strong Labels
  mKPLabel.setText("KARPLUS-STRONG", juce::dontSendNotification);
  addAndMakeVisible(mKPLabel);
  mKPDecayLabel.setText("Decay", juce::dontSendNotification);
  addAndMakeVisible(mKPDecayLabel);
  mKPDelayLabel.setText("Delay (ms)", juce::dontSendNotification);
  addAndMakeVisible(mKPDelayLabel);
  mKPWidthLabel.setText("Width (ms)", juce::dontSendNotification);
  addAndMakeVisible(mKPWidthLabel);

  // Karplus-Strong Sliders
  mKPDecaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
  mKPDecaySlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
  mKPDecaySlider.setRange(0.8f, 0.999f, 0.001f);
  mKPDecaySlider.setValue(0.9f);
  mKPDecaySlider.addListener(this);
  addAndMakeVisible(mKPDecaySlider);

  mKPDelaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
  mKPDelaySlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
  mKPDelaySlider.setRange(0.0f, 20.0f, 0.01f);
  mKPDelaySlider.setValue(10.0f);
  mKPDelaySlider.addListener(this);
  addAndMakeVisible(mKPDelaySlider);

  mKPWidthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
  mKPWidthSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
  mKPWidthSlider.setRange(0.0f, 20.0f, 0.01f);
  mKPWidthSlider.setValue(10.0f);
  mKPWidthSlider.addListener(this);
  addAndMakeVisible(mKPWidthSlider);

  mKPStartButton.setButtonText("PLAY KP");
  mKPStartButton.addListener(this);
  addAndMakeVisible(mKPStartButton);

  setSize(500, 400);
}

JucepluginAudioProcessorEditor::~JucepluginAudioProcessorEditor() {}

//==============================================================================
void JucepluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::black);
}

void JucepluginAudioProcessorEditor::resized() {
  mGainSlider.setBounds(25, getHeight() / 6 - 30, getWidth() / 2 - 50, 100);
  mPitchSlider.setBounds(3 * (getWidth() / 4) - 50, getHeight() / 6 - 40, 100,
                         80);

  mGainLabel.setBounds(25, 25, 100, 25);
  mPitchLabel.setBounds(getWidth() / 2, 25, 100, 25);

  mKPLabel.setBounds(25, (getHeight() / 3), 200, 25);
  mKPDecayLabel.setBounds(25, (getHeight() / 3) + 50, 100, 25);
  mKPDelayLabel.setBounds(25, (getHeight() / 3) + 100, 100, 25);
  mKPWidthLabel.setBounds(25, (getHeight() / 3) + 150, 100, 25);

  mKPDecaySlider.setBounds(150, (getHeight() / 3) + 50, 150, 25);
  mKPDelaySlider.setBounds(150, (getHeight() / 3) + 100, 150, 25);
  mKPWidthSlider.setBounds(150, (getHeight() / 3) + 150, 150, 25);

  mKPStartButton.setBounds(25, (getHeight() / 3) + 200, 150, 25);
}

void JucepluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
  if (slider == &mGainSlider) {
    audioProcessor.mGain = mGainSlider.getValue();
  } else if (slider == &mPitchSlider) {
    audioProcessor.mPitch = mPitchSlider.getValue();
  }
}

void JucepluginAudioProcessorEditor::buttonClicked(juce::Button *button) {
  if (button == &mKPStartButton) {
  }
}
