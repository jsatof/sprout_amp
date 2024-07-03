#include <PluginProcessor.h>
#include <PluginEditor.h>

SproutAudioProcessorEditor::SproutAudioProcessorEditor(SproutAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , processor(p)
    , gainSliderAttachment(p.getState(), "ampgain", gainSlider)
    , blendSliderAttachment(p.getState(), "ampblend", blendSlider)
    , volumeSliderAttachment(p.getState(), "ampvolume", volumeSlider)
{
    setSize(800, 600);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setNormalisableRange({ 0.0, 10.0 });
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setValue(1.0);
    addAndMakeVisible(gainSlider);

	gainLabel.setText("Gain", juce::dontSendNotification);
	gainLabel.attachToComponent(&gainSlider, true);
	gainLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	gainLabel.setJustificationType(juce::Justification::bottomRight);
    addAndMakeVisible(gainLabel);

    blendSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    blendSlider.setNormalisableRange({ 0.0, 1.0 });
    blendSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    blendSlider.setValue(0.0);
    addAndMakeVisible(blendSlider);

	blendLabel.setText("Mix", juce::dontSendNotification);
	blendLabel.attachToComponent(&blendSlider, true);
	blendLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	blendLabel.setJustificationType(juce::Justification::bottomRight);
    addAndMakeVisible(blendLabel);

    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumeSlider.setNormalisableRange({ -48.0, 0.0 });
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    volumeSlider.setValue(-6.0);
    addAndMakeVisible(volumeSlider);

	volumeLabel.setText("Volume", juce::dontSendNotification);
	volumeLabel.attachToComponent(&volumeSlider, true);
	volumeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	volumeLabel.setJustificationType(juce::Justification::bottomRight);
    addAndMakeVisible(blendLabel);

}

void SproutAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::darkgrey);
}

void SproutAudioProcessorEditor::resized() {
	const int margin = 10;
	const int dim = 130;

	gainSlider.setBounds(margin, margin, dim, dim);
	blendSlider.setBounds(gainSlider.getRight() + margin, margin, dim, dim);
	volumeSlider.setBounds(blendSlider.getRight() + margin, margin, dim, dim);
}
