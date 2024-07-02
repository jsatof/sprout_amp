#include <PluginProcessor.h>
#include <PluginEditor.h>

SproutAudioProcessor::SproutAudioProcessor()
    : AudioProcessor(BusesProperties() // this plugin doesnt need midi input, also is not a synthesizer
                       .withInput("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , treeState(*this, nullptr, "PARAMETERS", {
    		// these default values should match the Editor values, these are loaded and set before the gui
    		std::make_unique<juce::AudioParameterFloat>("gain", "Gain", juce::NormalisableRange<float>(0.f, 5000.f), 0.f),
    })
{
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

void SproutAudioProcessor::changeProgramName(int index, const juce::String& newName) {
    juce::ignoreUnused(index, newName);
}

void SproutAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::ignoreUnused(sampleRate);
    juce::ignoreUnused(samplesPerBlock);
}

void SproutAudioProcessor::releaseResources() {}

bool SproutAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo()) {
        return false;
    }
    return true;
}

void SproutAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    buffer.clear();
    juce::ignoreUnused(midiMessages);
}

bool SproutAudioProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor* SproutAudioProcessor::createEditor() {
    return new SproutAudioProcessorEditor(*this);
}

void SproutAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
    auto xml = std::unique_ptr<juce::XmlElement>(new juce::XmlElement("exampleSynthesizer"));
    //xml->setAttribute("gain", double(*gain));
    //xml->setAttribute("invertPhase", *invertPhase);
    copyXmlToBinary(*xml, destData);
}

void SproutAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    auto xml = std::unique_ptr<juce::XmlElement>(getXmlFromBinary(data, sizeInBytes));
    if (xml.get()) {
        if (xml->hasTagName("exampleSynthesizer")) {
        }
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new SproutAudioProcessor();
}
