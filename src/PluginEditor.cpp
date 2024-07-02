#include <PluginProcessor.h>
#include <PluginEditor.h>

SproutAudioProcessorEditor::SproutAudioProcessorEditor(SproutAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , processor(p)
{
    setSize(800, 600);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gainSlider.setNormalisableRange({-48.0, 0.0});
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    //gainSlider.addListener(this);
    //gainSlider.setValue(p.getGain());
    addAndMakeVisible(gainSlider);
}

void SproutAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::darkgrey);
}

void SproutAudioProcessorEditor::resized() {
	gainSlider.setBounds(getLocalBounds());
}
