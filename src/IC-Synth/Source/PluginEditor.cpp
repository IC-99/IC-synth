/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.0f, 2000.0f, 10.0f);
    attackSlider.setValue(200.0f);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50.0, 50.0);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.0f, 2000.0f, 10.0f);
    releaseSlider.setValue(200.0f);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50.0, 50.0);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);

    attackTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "attack", attackSlider);
    releaseTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "release", releaseSlider);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("IC-synth", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    attackSlider.setBounds(10, 10, 60, 250);
    releaseSlider.setBounds(70, 10, 130, 250);
}

void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &attackSlider) {
        audioProcessor.attackTime = attackSlider.getValue();
    }
    if (slider == &releaseSlider) {
        audioProcessor.releaseTime = releaseSlider.getValue();
    }
}