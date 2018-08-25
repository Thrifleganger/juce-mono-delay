/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Delay.h"


//==============================================================================
/**
*/
class MonoDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MonoDelayAudioProcessor();
    ~MonoDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void setDelayTime(const float delayTime);
    void setFeedback(const float feedback);
    void setLowCut(const float lowCut);
    void setHighCut(const float highCut);
    void setMix(const float mix);
    void setInputGain(const float gain);
    void setOutputGain(const float gain);
    void setBypass(const bool state);
    void setDelayType(const int type);
    void setInputLevel(const float level);
    void setOutputLeftLevel(const float level);
    void setOutputRightLevel(const float level);
    
    float getDelayTime() const;
    float getFeedback() const;
    float getLowCut() const;
    float getHighCut() const;
    float getMix() const;
    float getInputGain() const;
    float getOutputGain() const;
    bool getBypass() const;
    int getDelayType() const;
    float getInputLevel() const;
    float getOutputLeftLevel() const;
    float getOutputRightLevel() const;
    
    enum class DelayType {
        DIGITAL = 1, PING_PONG, REVERSE
    };
    
    class AudioSamplePair {
    public:
        float left{};
        float right{};
    };

private:
    AudioProcessorValueTreeState parameters;
    UndoManager undoManager;
    
    std::vector<CustomDelay> customDelay;
    std::vector<CustomDelayTap> delTap;
    std::vector<IIRFilter> lowPassFilter;
    std::vector<IIRFilter> highPassFilter;
    
    // Data values
    LinearSmoothedValue<float> delayTime;
    LinearSmoothedValue<float> feedback;
    LinearSmoothedValue<float> lowCut;
    LinearSmoothedValue<float> highCut;
    LinearSmoothedValue<float> mix;
    float inputGain;
    float outputGain;
    float inputLevel;
    float outputLeftLevel;
    float outputRightLevel;
    
    DelayType delayType;
    bool bypass;
    
    float sampleRate;
    
    void initializeParameterSmoothening();
    float ampToDb(const float amplitude);
    float dbToAmp(const float db);
    float linearToLog(const float amplitude);
    void createAndAddValueTreeParameters();
    AudioSamplePair handleDelayTypes(const int sample, const float* input, AudioSamplePair& pair);
    AudioSamplePair processLowCut(const AudioSamplePair& input);
    AudioSamplePair processHighCut(const AudioSamplePair& input);
    AudioSamplePair processMix(const int sample, const float* input, const AudioSamplePair& signalToBeMixed);
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonoDelayAudioProcessor)
};
