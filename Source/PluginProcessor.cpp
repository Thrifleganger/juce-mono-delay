/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "GUI.h"


//==============================================================================
MonoDelayAudioProcessor::MonoDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, &undoManager)
#endif
{
    createAndAddValueTreeParameters();
    parameters.state = ValueTree(Identifier("MonoRepeater"));
}

MonoDelayAudioProcessor::~MonoDelayAudioProcessor()
{
}

//==============================================================================
const String MonoDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MonoDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MonoDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double MonoDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MonoDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MonoDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MonoDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String MonoDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void MonoDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MonoDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    this->sampleRate = sampleRate;
    initializeParameterSmoothening();
    
    customDelay = std::vector<CustomDelay>(2, CustomDelay(5, sampleRate));
    delTap = std::vector<CustomDelayTap>(2, CustomDelayTap());
    lowPassFilter = std::vector<IIRFilter>(2);
    highPassFilter = std::vector<IIRFilter>(2);
	
	highPassFilter[0].setCoefficients(IIRCoefficients::makeHighPass(sampleRate, lowCut.getNextValue()));
	highPassFilter[1].setCoefficients(IIRCoefficients::makeHighPass(sampleRate, lowCut.getNextValue()));
	lowPassFilter[0].setCoefficients(IIRCoefficients::makeLowPass(sampleRate, highCut.getNextValue()));
	lowPassFilter[1].setCoefficients(IIRCoefficients::makeLowPass(sampleRate, highCut.getNextValue()));
	
}

void MonoDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MonoDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MonoDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const float* const input = buffer.getReadPointer(0);
    float* const outputL = buffer.getWritePointer(0);
    float* const outputR = buffer.getWritePointer(1);
    
    buffer.applyGain(dbToAmp(inputGain));
    setInputLevel(linearToLog(buffer.getRMSLevel(0, 0, buffer.getNumSamples())));
    
    if(!bypass) {		
		if (getPlayHead() != nullptr) {
			getPlayHead()->getCurrentPosition(bpmInfo);
			hostBpm.setValue(bpmInfo.bpm);
		}		
        AudioSamplePair delayedSample, lowCutSample, highCutSample, mixedSample;
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            delayedSample = handleDelayTypes(sample, input, delayedSample);
            lowCutSample = processLowCut(delayedSample);
            highCutSample = processHighCut(lowCutSample);
            mixedSample = processMix(sample, input, highCutSample);
            outputL[sample] = mixedSample.left;
            outputR[sample] = mixedSample.right;
        }
    }
    buffer.applyGain(dbToAmp(outputGain));
    setOutputLeftLevel(linearToLog(buffer.getRMSLevel(0, 0, buffer.getNumSamples())));
    setOutputRightLevel(linearToLog(buffer.getRMSLevel(1, 0, buffer.getNumSamples())));
}

//==============================================================================
bool MonoDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MonoDelayAudioProcessor::createEditor()
{
    return new GUI (*this, parameters);
}

//==============================================================================
void MonoDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void MonoDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.state = ValueTree::fromXml (*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MonoDelayAudioProcessor();
}


void MonoDelayAudioProcessor::setDelayTime(const float delayTime) { this->delayTime.setValue(delayTime); }
void MonoDelayAudioProcessor::setFeedback(const float feedback) { this->feedback.setValue(feedback); }
void MonoDelayAudioProcessor::setLowCut(const float lowCut) { this->lowCut.setValue(lowCut); }
void MonoDelayAudioProcessor::setHighCut(const float highCut) { this->highCut.setValue(highCut); }
void MonoDelayAudioProcessor::setMix(const float mix) { this->mix.setValue(mix); }
void MonoDelayAudioProcessor::setInputGain(const float gain) { this->inputGain = gain; }
void MonoDelayAudioProcessor::setOutputGain(const float gain) { this->outputGain = gain; }
void MonoDelayAudioProcessor::setBypass(const bool state) { this->bypass = state; }
void MonoDelayAudioProcessor::setDelayType(const int type) { this->delayType = static_cast<DelayType>(type); }
void MonoDelayAudioProcessor::setInputLevel(const float level) { this->inputLevel = level; }
void MonoDelayAudioProcessor::setOutputLeftLevel(const float level) { this->outputLeftLevel = level; }
void MonoDelayAudioProcessor::setOutputRightLevel(const float level) { this->outputRightLevel = level; }

float MonoDelayAudioProcessor::getDelayTime() const { return this->delayTime.getTargetValue(); }
float MonoDelayAudioProcessor::getFeedback() const { return this->feedback.getTargetValue(); }
float MonoDelayAudioProcessor::getLowCut() const { return this->lowCut.getTargetValue(); }
float MonoDelayAudioProcessor::getHighCut() const { return this->highCut.getTargetValue(); }
float MonoDelayAudioProcessor::getMix() const { return this->mix.getTargetValue(); }
float MonoDelayAudioProcessor::getInputGain() const { return this->inputGain; }
float MonoDelayAudioProcessor::getOutputGain() const { return this->outputGain; }
bool MonoDelayAudioProcessor::getBypass() const { return this->bypass; }
int MonoDelayAudioProcessor::getDelayType() const { return static_cast<int>(this->delayType); }
float MonoDelayAudioProcessor::getInputLevel() const { return this->inputLevel; }
float MonoDelayAudioProcessor::getOutputLeftLevel() const { return this->outputLeftLevel; }
float MonoDelayAudioProcessor::getOutputRightLevel() const { return this->outputRightLevel; }

void MonoDelayAudioProcessor::initializeParameterSmoothening() {
    delayTime.reset(sampleRate, 1);
    feedback.reset(sampleRate, 0.2);
    lowCut.reset(sampleRate, 0.2);
    highCut.reset(sampleRate, 0.2);
    mix.reset(sampleRate, 0.2);
}

MonoDelayAudioProcessor::AudioSamplePair MonoDelayAudioProcessor::handleDelayTypes(const int sample, const float* input, AudioSamplePair& pair) {
    
    
    float feedback = this->feedback.getNextValue();
    float delayTime = this->delayTime.getNextValue();
    switch (delayType) {
        case DelayType::DIGITAL: {
            pair.left = delTap[0].tap(customDelay[0], delayTime * sampleRate * 0.001);
            customDelay[0].writeToDelayBuffer(input[sample] + (pair.left * feedback));
            
            pair.right = delTap[1].tap(customDelay[1], delayTime * sampleRate * 0.001);
            customDelay[1].writeToDelayBuffer(input[sample] + (pair.right * feedback));
        }
            break;
        case DelayType::PING_PONG: {
            pair.left = delTap[0].tap(customDelay[0], delayTime * sampleRate * 0.001);
            customDelay[0].writeToDelayBuffer(input[sample] + (pair.right * feedback));
            
            pair.right = delTap[1].tap(customDelay[1], delayTime * sampleRate * 0.001);
            customDelay[1].writeToDelayBuffer(pair.left * feedback);
            break;
        }
        default:
            break;
    }
    return pair;
}

MonoDelayAudioProcessor::AudioSamplePair MonoDelayAudioProcessor::processLowCut(const MonoDelayAudioProcessor::AudioSamplePair &input) {

    AudioSamplePair output;
    if(lowCut.isSmoothing()) {
        highPassFilter[0].setCoefficients(IIRCoefficients::makeHighPass(sampleRate, lowCut.getNextValue()));
        highPassFilter[1].setCoefficients(IIRCoefficients::makeHighPass(sampleRate, lowCut.getNextValue()));
    }
    output.left = lowPassFilter[0].processSingleSampleRaw(input.left);
    output.right = lowPassFilter[1].processSingleSampleRaw(input.right);
    return output;
}

MonoDelayAudioProcessor::AudioSamplePair MonoDelayAudioProcessor::processHighCut(const MonoDelayAudioProcessor::AudioSamplePair &input) {

    AudioSamplePair output;
    if(highCut.isSmoothing()) {
        lowPassFilter[0].setCoefficients(IIRCoefficients::makeLowPass(sampleRate, highCut.getNextValue()));
        lowPassFilter[1].setCoefficients(IIRCoefficients::makeLowPass(sampleRate, highCut.getNextValue()));
    }
    output.left = highPassFilter[0].processSingleSampleRaw(input.left);
    output.right = highPassFilter[1].processSingleSampleRaw(input.right);
    return output;
}

MonoDelayAudioProcessor::AudioSamplePair MonoDelayAudioProcessor::processMix(const int sample, const float* input, const MonoDelayAudioProcessor::AudioSamplePair &signalToBeMixed) {
    
    AudioSamplePair output;
    float currentMixValue = mix.getNextValue();
    output.left = (input[sample] * (1 - currentMixValue)) + (signalToBeMixed.left * currentMixValue);
    output.right = (input[sample] * (1 - currentMixValue)) + (signalToBeMixed.right * currentMixValue);
    return output;
}

float MonoDelayAudioProcessor::ampToDb(const float amplitude) {
    return 10 * log10(amplitude);
}

float MonoDelayAudioProcessor::dbToAmp(const float db) {
    return pow(10.0, db/20.0);
}

float MonoDelayAudioProcessor::linearToLog(const float amplitude) {
    return (43 - fabs(ampToDb(amplitude)))/43.0;
}

void MonoDelayAudioProcessor::createAndAddValueTreeParameters() {
    parameters.createAndAddParameter("delayTime",
                                     "Delay Time",
                                     "ms",
                                     NormalisableRange<float>(30.0f, 4000.0f, 1.0f),
                                     700.0f,
                                     [](float value) -> String { return String(value); },
                                     [](const String& text) -> float { return text.getFloatValue(); }
                                     );
    parameters.createAndAddParameter("feedback",
                                     "Feedback",
                                     "%",
                                     NormalisableRange<float>(0.0f, 100.0f, 1.0f),
                                     80.0f,
                                     [](float value) -> String { return String(value); },
                                     [](const String& text) -> float { return text.getFloatValue(); }
                                     );
    parameters.createAndAddParameter("lowCut",
                                     "Low cut",
                                     "Hz",
                                     NormalisableRange<float>(20.0f, 2000.0f, 1.0f),
                                     200.0f,
                                     [](float value) -> String { return String(value); },
                                     [](const String& text) -> float { return text.getFloatValue(); }
                                     );
    parameters.createAndAddParameter("highCut",
                                     "High cut",
                                     "Hz",
                                     NormalisableRange<float>(500.0f, 20000.0f, 1.0f),
                                     10000.0f,
                                     [](float value) -> String { return String(value); },
                                     [](const String& text) -> float { return text.getFloatValue(); }
                                     );
    parameters.createAndAddParameter("mix",
                                     "Mix",
                                     "%",
                                     NormalisableRange<float>(0.0f, 100.0f, 1.0f),
                                     50.0f,
                                     [](float value) -> String { return String(value); },
                                     [](const String& text) -> float { return text.getFloatValue(); }
                                     );
}
