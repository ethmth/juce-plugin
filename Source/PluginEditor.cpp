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
  mGainSlider.setRange(0.0f, 1.0f, 0.05f);
  mGainSlider.setValue(0.5f);
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
