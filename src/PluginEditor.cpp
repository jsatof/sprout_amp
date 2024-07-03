#include <PluginProcessor.h>
#include <PluginEditor.h>

SproutAudioProcessorEditor::SproutAudioProcessorEditor(SproutAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , processor(p)
    , gainSliderAttachment(p.getState(), "ampgain", gainSlider)
    , blendSliderAttachment(p.getState(), "ampblend", blendSlider)
    , volumeSliderAttachment(p.getState(), "ampvolume", volumeSlider)
    , ampBypassButton("Amp Bypass")
{
    setSize(800, 600);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setNormalisableRange({ 0.5, 10.0 });
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setValue(5.0);
    addAndMakeVisible(gainSlider);

	gainLabel.setText("Gain", juce::dontSendNotification);
	gainLabel.attachToComponent(&gainSlider, true);
	gainLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	gainLabel.setJustificationType(juce::Justification::centredBottom);
    addAndMakeVisible(gainLabel);

    blendSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    blendSlider.setNormalisableRange({ 1.0, 10.0 });
    blendSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    blendSlider.setValue(5.0);
    addAndMakeVisible(blendSlider);

	blendLabel.setText("Mix", juce::dontSendNotification);
	blendLabel.attachToComponent(&blendSlider, true);
	blendLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	blendLabel.setJustificationType(juce::Justification::centredBottom);
    addAndMakeVisible(blendLabel);

    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumeSlider.setNormalisableRange({ -12.0, 6.0 });
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    volumeSlider.setValue(0.0);
    addAndMakeVisible(volumeSlider);

	volumeLabel.setText("Volume", juce::dontSendNotification);
	volumeLabel.attachToComponent(&volumeSlider, true);
	volumeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	volumeLabel.setJustificationType(juce::Justification::centredBottom);
    addAndMakeVisible(blendLabel);

	ampBypassButton.setTooltip("Disable processing for the pre amp");
	ampBypassButton.onClick = [&]() {
			p.setAmpBypass(ampBypassButton.getState() == juce::Button::ButtonState::buttonDown);
	};
    addAndMakeVisible(ampBypassButton);
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

	ampBypassButton.setBounds(getLocalBounds().getWidth() - 100, 0, 100, 50);
}
