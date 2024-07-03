#include <PluginProcessor.h>
#include <PluginEditor.h>

SproutAudioProcessor::SproutAudioProcessor()
    : AudioProcessor(BusesProperties() // this plugin doesnt need midi input, also is not a synthesizer
                       .withInput("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
{}

using ParameterLayout = juce::AudioProcessorValueTreeState::ParameterLayout;
ParameterLayout SproutAudioProcessor::createParameterLayout() {
	ParameterLayout layout;

    // these default values should match the Editor values, these are loaded and set before the gui
    layout.add(std::make_unique<juce::AudioParameterFloat>("ampgain", "AmpGain", juce::NormalisableRange<float>(0.f, 5000.f), 0.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("ampblend", "AmpBlend", juce::NormalisableRange<float>(0.f, 5000.f), 0.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("ampvolume", "AmpVolume", juce::NormalisableRange<float>(0.f, 5000.f), 0.f));

    return layout;
}

juce::AudioProcessorValueTreeState &SproutAudioProcessor::getState() {
	return treeState;
}

const juce::String SproutAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool SproutAudioProcessor::acceptsMidi() const {
    return false;
}

bool SproutAudioProcessor::producesMidi() const {
    return false;
}

bool SproutAudioProcessor::isMidiEffect() const {
    return false;
}

double SproutAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int SproutAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SproutAudioProcessor::getCurrentProgram() {
    return 0;
}

void SproutAudioProcessor::setCurrentProgram(int index) {
    juce::ignoreUnused(index);
}

const juce::String SproutAudioProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void SproutAudioProcessor::changeProgramName(int index, const juce::String &newName) {
    juce::ignoreUnused(index, newName);
}

void SproutAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::ignoreUnused(sampleRate);
    juce::ignoreUnused(samplesPerBlock);
}

void SproutAudioProcessor::releaseResources() {}

bool SproutAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo()) {
        return false;
    }
    return true;
}

void SproutAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &) {
	mParam.gain = *treeState.getRawParameterValue("ampgain");
	mParam.volume = *treeState.getRawParameterValue("ampvolume");
	mParam.blend = *treeState.getRawParameterValue("ampblend");

	const int n_in_channels = getTotalNumInputChannels();
	const int n_out_channels = getTotalNumOutputChannels();

	for (int i = n_in_channels; i < n_out_channels; ++i) {
		buffer.clear(i, 0, buffer.getNumSamples());
	}

	for (int channel = 0; channel < n_in_channels; ++channel) {
		float *samples = buffer.getWritePointer(channel);
		for (int s = 0; s < buffer.getNumSamples(); ++s) {
			mParam.distortion_calc = (2.0 / juce::MathConstants<double>::pi) * atan(mParam.gain * samples[s]);
			samples[s] = mParam.volume * ((mParam.distortion_calc * -mParam.blend) + (samples[s] * (1.0 + mParam.blend)));
		}
	}
}

bool SproutAudioProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor* SproutAudioProcessor::createEditor() {
    return new SproutAudioProcessorEditor(*this);
}

// can use raw data, xml, or juce::ValueTree to load/store parameters
void SproutAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
	juce::MemoryOutputStream stream = {destData, false};
	treeState.state.writeToStream(stream);
}

void SproutAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
	juce::ValueTree tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
    if (tree.isValid()) {
		treeState.state = tree;
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new SproutAudioProcessor();
}
