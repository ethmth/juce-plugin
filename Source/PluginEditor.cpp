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
  mGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
  mGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
  mGainSlider.setRange(-60.0f, 0.0f, 0.01f);
  mGainSlider.setValue(-6.0f);
  mGainSlider.addListener(this);
  addAndMakeVisible(mGainSlider);

  setSize(400, 300);
}

JucepluginAudioProcessorEditor::~JucepluginAudioProcessorEditor() {}

//==============================================================================
void JucepluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::black);
}

void JucepluginAudioProcessorEditor::resized() {
  mGainSlider.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 75, 100, 150);
}

void JucepluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
  if (slider == &mGainSlider) {
    audioProcessor.mGain = mGainSlider.getValue();
  }
}
