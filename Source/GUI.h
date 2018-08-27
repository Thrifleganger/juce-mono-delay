/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "TempoController.h"
#include "CustomLookAndFeel.h"
#include "MeterComponent.h"
#include "PluginProcessor.h"
#include "DefaultParameterValues.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GUI  : public AudioProcessorEditor,
             public ValueListener,
             public Timer,
             public KeyListener,
             public AudioProcessorValueTreeState::Listener,
             public Slider::Listener,
             public Button::Listener,
             public ComboBox::Listener
{
public:
    //==============================================================================
    GUI (MonoDelayAudioProcessor& p, AudioProcessorValueTreeState& valueTreeState);
    ~GUI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void valueChanged (Value& valueThatChanged) override;
    void paintOverChildren(Graphics& g) override;
    void parameterChanged(const String &parameterID, float newValue) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    AudioProcessorValueTreeState& valueTree;

    struct DefaultParameterValues{
        int defaultManualDelayTime = 700;
        float defaultFeedback = 80;
        int defaultLowCut = 200;
        int defaultHighCut = 10000;
        float defaultMix = 50;
        int defaultSyncedDelaySelection = 5;
        bool defaultTempoSyncSwitch = false;
        bool defaultHostSwitch = true;
        bool defaultBypassSwitch = false;
        float defaultInputGain = 0.0;
        float defaultOutputGain = 0.0;
        int defaultTempo = 120;
        int defaultDelayType = 1;
        bool defaultPerformance = true;
    };

    MonoDelayAudioProcessor& processor;
    TempoController tempoController;
    ScopedPointer<Logger> logger;
    DefaultParameterValues defaultParameterValues;

    void timerCallback() override;
    bool keyPressed(const KeyPress &key, Component *originatingComponent) override;
    void setInitialWidgetValues();
    void setDoubleClickResetFunctionality();
    void initializeParametersInProcessor();
    void setCursorHandlesOnHover();
    void setTooltips();
    void setDisplayPopups();
    void setValueListeners();
    void setCustomSVGForSliders();
    void initializeDrawings();
    void hideImageMaskedComponents();
    void addParameterListenersToValueTree();
    void addWidgetAttachmentsToValueTree();
    void removeParameterListenersFromValueTree();
	void resetDefaultValues();

	void unsetValueListeners();

    Value delayTime;
    Value bpm;
    Value isSynced;
    Value isBypassed;

    TooltipWindow tooltipWindow;
    LargeKnobLookAndFeel largeKnobLookAndFeel;
    SmallKnobLookAndFeel smallKnobLookAndFeel;

    ScopedPointer<Drawable> background;
    ScopedPointer<Drawable> hostButtonOff;
    ScopedPointer<Drawable> hostButtonPressed;
    ScopedPointer<Drawable> bypassSwitchOff;
    ScopedPointer<Drawable> bypassSwitchOn;
    ScopedPointer<Drawable> manualDelaySwitch;
    ScopedPointer<Drawable> syncedDelaySwitch;
    ScopedPointer<Drawable> timeManualGraduations;
    ScopedPointer<Drawable> timeSyncedGraduations;
    ScopedPointer<Drawable> ledOn;
    ScopedPointer<Drawable> ledOff;
    ScopedPointer<Drawable> meterGrill1;
    ScopedPointer<Drawable> meterGrill2;
    ScopedPointer<Drawable> meterGrill3;
    ScopedPointer<Drawable> performanceLowSwitch;
    ScopedPointer<Drawable> performanceHighSwitch;
    ScopedPointer<MeterComponent> vuMeterInput;
    ScopedPointer<MeterComponent> vuMeterOutputLeft;
    ScopedPointer<MeterComponent> vuMeterOutputRight;

    ScopedPointer<SliderAttachment> delayManualSliderAttachment;
    ScopedPointer<SliderAttachment> feedbackSliderAttachment;
    ScopedPointer<SliderAttachment> lowCutSliderAttachment;
    ScopedPointer<SliderAttachment> highCutSliderAttachment;
    ScopedPointer<SliderAttachment> mixSliderAttachment;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> delayManualSlider;
    std::unique_ptr<Slider> feedbackSlider;
    std::unique_ptr<Slider> lowCutSlider;
    std::unique_ptr<Slider> highCutSlider;
    std::unique_ptr<Slider> mixSlider;
    std::unique_ptr<TextButton> tapButton;
    std::unique_ptr<ToggleButton> tempoSycnButton;
    std::unique_ptr<Slider> delaySyncSlider;
    std::unique_ptr<ToggleButton> hostButton;
    std::unique_ptr<ComboBox> delayTypeCombo;
    std::unique_ptr<Slider> tempoNumberBox;
    std::unique_ptr<Slider> inputSlider;
    std::unique_ptr<Slider> outputSlider;
    std::unique_ptr<ToggleButton> bypassButton;
    std::unique_ptr<Slider> timeNumberBox;
    std::unique_ptr<TextButton> saveButton;
    std::unique_ptr<TextButton> openButton;
    std::unique_ptr<ToggleButton> performance;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
