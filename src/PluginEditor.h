#pragma once

#include <PluginProcessor.h>


class SproutAudioProcessorEditor final : public juce::AudioProcessorEditor {
public:
    explicit SproutAudioProcessorEditor(SproutAudioProcessor &);

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    SproutAudioProcessor &processor;

	juce::Slider gainSlider;
	juce::Slider blendSlider;
	juce::Slider volumeSlider;

	using JuceSliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
	JuceSliderAttachment gainSliderAttachment;
	JuceSliderAttachment blendSliderAttachment;
	JuceSliderAttachment volumeSliderAttachment;

	juce::Label gainLabel;
	juce::Label blendLabel;
	juce::Label volumeLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SproutAudioProcessorEditor)
};
