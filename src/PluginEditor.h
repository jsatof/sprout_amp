#pragma once

#include <PluginProcessor.h>

class SproutAudioProcessorEditor final : public juce::AudioProcessorEditor {
public:
    explicit SproutAudioProcessorEditor(SproutAudioProcessor&);

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    SproutAudioProcessor &processor;

	juce::Slider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SproutAudioProcessorEditor)
};
