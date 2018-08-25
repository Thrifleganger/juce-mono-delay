/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "GUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GUI::GUI (MonoDelayAudioProcessor& p, AudioProcessorValueTreeState& valueTreeState)
    : AudioProcessorEditor (&p), valueTree(valueTreeState), processor (p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible(vuMeterInput = new MeterComponent(MeterComponent::MeterType::MeterVertical));
    addAndMakeVisible(vuMeterOutputLeft = new MeterComponent(MeterComponent::MeterType::MeterVertical));
    addAndMakeVisible(vuMeterOutputRight = new MeterComponent(MeterComponent::MeterType::MeterVertical));
    vuMeterInput->setDecay(50, 1);
    vuMeterOutputRight->setDecay(50, 1);
    vuMeterOutputLeft->setDecay(50, 1);
    //[/Constructor_pre]

    addAndMakeVisible (delayManualSlider = new Slider ("delayManualSlider"));
    delayManualSlider->setRange (30, 4000, 1);
    delayManualSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delayManualSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    delayManualSlider->addListener (this);
    delayManualSlider->setSkewFactor (0.7);

    addAndMakeVisible (feedbackSlider = new Slider ("feedbackSlider"));
    feedbackSlider->setRange (0, 100, 1);
    feedbackSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    feedbackSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    feedbackSlider->addListener (this);

    addAndMakeVisible (lowCutSlider = new Slider ("lowCutSlider"));
    lowCutSlider->setRange (20, 2000, 1);
    lowCutSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    lowCutSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lowCutSlider->addListener (this);

    addAndMakeVisible (highCutSlider = new Slider ("highCutSlider"));
    highCutSlider->setRange (500, 20000, 1);
    highCutSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    highCutSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    highCutSlider->addListener (this);

    addAndMakeVisible (mixSlider = new Slider ("mixSlider"));
    mixSlider->setRange (0, 100, 1);
    mixSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    mixSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    mixSlider->addListener (this);

    addAndMakeVisible (tapButton = new TextButton ("tapButton"));
    tapButton->setButtonText (TRANS("Tap"));
    tapButton->addListener (this);

    addAndMakeVisible (tempoSycnButton = new ToggleButton ("tempoSyncButton"));
    tempoSycnButton->setButtonText (String());
    tempoSycnButton->addListener (this);

    addAndMakeVisible (delaySyncSlider = new Slider ("delaySyncSlider"));
    delaySyncSlider->setRange (0, 10, 1);
    delaySyncSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delaySyncSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    delaySyncSlider->addListener (this);

    addAndMakeVisible (hostButton = new ToggleButton ("hostButton"));
    hostButton->setButtonText (String());
    hostButton->addListener (this);

    addAndMakeVisible (delayTypeCombo = new ComboBox ("delayTypeCombo"));
    delayTypeCombo->setEditableText (false);
    delayTypeCombo->setJustificationType (Justification::centredLeft);
    delayTypeCombo->setTextWhenNothingSelected (String());
    delayTypeCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    delayTypeCombo->addItem (TRANS("Digital"), 1);
    delayTypeCombo->addItem (TRANS("Ping Pong"), 2);
    delayTypeCombo->addItem (TRANS("Reverse"), 3);
    delayTypeCombo->addListener (this);

    addAndMakeVisible (tempoNumberBox = new Slider ("tempoNumberBox"));
    tempoNumberBox->setRange (1, 400, 1);
    tempoNumberBox->setSliderStyle (Slider::LinearBarVertical);
    tempoNumberBox->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    tempoNumberBox->setColour (Slider::backgroundColourId, Colour (0xff0e1214));
    tempoNumberBox->setColour (Slider::thumbColourId, Colour (0xff12181b));
    tempoNumberBox->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff1a2227));
    tempoNumberBox->setColour (Slider::textBoxTextColourId, Colour (0xff66e0ff));
    tempoNumberBox->setColour (Slider::textBoxBackgroundColourId, Colour (0xff112028));
    tempoNumberBox->setColour (Slider::textBoxHighlightColourId, Colour (0xff171f22));
    tempoNumberBox->setColour (Slider::textBoxOutlineColourId, Colour (0xff101719));
    tempoNumberBox->addListener (this);

    addAndMakeVisible (inputSlider = new Slider ("inputSlider"));
    inputSlider->setRange (-60, 6, 0.01);
    inputSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    inputSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    inputSlider->addListener (this);
    inputSlider->setSkewFactor (3);

    addAndMakeVisible (outputSlider = new Slider ("outputSlider"));
    outputSlider->setRange (-60, 6, 0.01);
    outputSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    outputSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    outputSlider->addListener (this);
    outputSlider->setSkewFactor (3);

    addAndMakeVisible (bypassButton = new ToggleButton ("bypassButton"));
    bypassButton->setButtonText (String());
    bypassButton->addListener (this);

    addAndMakeVisible (timeNumberBox = new Slider ("timeNumberBox"));
    timeNumberBox->setRange (30, 4000, 1);
    timeNumberBox->setSliderStyle (Slider::LinearBarVertical);
    timeNumberBox->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    timeNumberBox->setColour (Slider::backgroundColourId, Colour (0xff0e1214));
    timeNumberBox->setColour (Slider::thumbColourId, Colour (0xff12181b));
    timeNumberBox->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff1a2227));
    timeNumberBox->setColour (Slider::textBoxTextColourId, Colour (0xff66e0ff));
    timeNumberBox->setColour (Slider::textBoxBackgroundColourId, Colour (0xff112028));
    timeNumberBox->setColour (Slider::textBoxHighlightColourId, Colour (0xff171f22));
    timeNumberBox->setColour (Slider::textBoxOutlineColourId, Colour (0xff101719));
    timeNumberBox->addListener (this);

    addAndMakeVisible (saveButton = new TextButton ("saveButton"));
    saveButton->setButtonText (TRANS("Save"));
    saveButton->addListener (this);

    addAndMakeVisible (openButton = new TextButton ("openButton"));
    openButton->setButtonText (TRANS("Open"));
    openButton->addListener (this);

    addAndMakeVisible (performance = new ToggleButton ("performance"));
    performance->setButtonText (String());
    performance->addListener (this);


    //[UserPreSize]
    addParameterListenersToValueTree();
    addWidgetAttachmentsToValueTree();
    setValueListeners();
    setInitialWidgetValues();
    setDoubleClickResetFunctionality();
    initializeParametersInProcessor();
    setCursorHandlesOnHover();
    setTooltips();
    setDisplayPopups();
    setCustomSVGForSliders();
    initializeDrawings();
    hideImageMaskedComponents();
    addKeyListener(this);

    delayTypeCombo->setColour(ComboBox::textColourId, Colour (0xff66e0ff));
    //[/UserPreSize]

    setSize (820, 532);


    //[Constructor] You can add your own custom stuff here..
    startTimer(50);
    //[/Constructor]
}

GUI::~GUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    delayManualSlider = nullptr;
    feedbackSlider = nullptr;
    lowCutSlider = nullptr;
    highCutSlider = nullptr;
    mixSlider = nullptr;
    tapButton = nullptr;
    tempoSycnButton = nullptr;
    delaySyncSlider = nullptr;
    hostButton = nullptr;
    delayTypeCombo = nullptr;
    tempoNumberBox = nullptr;
    inputSlider = nullptr;
    outputSlider = nullptr;
    bypassButton = nullptr;
    timeNumberBox = nullptr;
    saveButton = nullptr;
    openButton = nullptr;
    performance = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    vuMeterInput = nullptr;
    vuMeterOutputLeft = nullptr;
    vuMeterOutputRight = nullptr;
    background = nullptr;
    hostButton = nullptr;
    hostButtonPressed = nullptr;
    bypassSwitchOff = nullptr;
    bypassSwitchOn = nullptr;
    manualDelaySwitch = nullptr;
    syncedDelaySwitch = nullptr;
    timeManualGraduations = nullptr;
    timeSyncedGraduations = nullptr;
    performanceLowSwitch = nullptr;
    performanceHighSwitch = nullptr;
    ledOn = nullptr;
    ledOff = nullptr;
    meterGrill1 = nullptr;
    meterGrill2 = nullptr;
    meterGrill3 = nullptr;

    removeParameterListenersFromValueTree();
    //[/Destructor]
}

//==============================================================================
void GUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    {
        int x = 0, y = 0, width = 820, height = 532;
        //[UserPaintCustomArguments] Customize the painting arguments here..

        g.setColour (Colours::black);
        jassert (background != 0);
        if (background != 0)
            background->drawWithin (g, Rectangle<float> (x, y, width, height),
                                    RectanglePlacement::stretchToFit, 1.000f);
    }

    if(!hostButton->getToggleStateValue().getValue()) {
        {
            int x = 362, y = 76, width = 89, height = 40;
            g.setColour (Colours::black);
            jassert (hostButtonOff != 0);
            if (hostButtonOff != 0)
                hostButtonOff->drawWithin (g, Rectangle<float> (x, y, width, height),
                                           RectanglePlacement::stretchToFit, 1.000f);
        }
    } else {
        {
            int x = 362, y = 76, width = 89, height = 40;
            g.setColour (Colours::black);
            jassert (hostButtonPressed != 0);
            if (hostButtonPressed != 0)
                hostButtonPressed->drawWithin (g, Rectangle<float> (x, y, width, height),
                                               RectanglePlacement::stretchToFit, 1.000f);
        }
    }

    if(isBypassed.getValue()) {
        {
            int x = 24, y = 406, width = 40, height = 70;
            g.setColour (Colours::black);
            jassert (bypassSwitchOff != 0);
            if (bypassSwitchOff != 0)
                bypassSwitchOff->drawWithin (g, Rectangle<float> (x, y, width, height),
                                             RectanglePlacement::stretchToFit, 1.000f);
        }
        {
            int x = 14, y = 362, width = 61, height = 61;
            g.setColour (Colours::black);
            jassert (ledOff != 0);
            if (ledOff != 0)
                ledOff->drawWithin (g, Rectangle<float> (x, y, width, height),
                                    RectanglePlacement::stretchToFit, 1.000f);
        }
    } else {
        {
            int x = 24, y = 406, width = 40, height = 70;
            g.setColour (Colours::black);
            jassert (bypassSwitchOn != 0);
            if (bypassSwitchOn != 0)
                bypassSwitchOn->drawWithin (g, Rectangle<float> (x, y, width, height),
                                            RectanglePlacement::stretchToFit, 1.000f);
        }
        {
            int x = 14, y = 362, width = 61, height = 61;
            g.setColour (Colours::black);
            jassert (ledOn != 0);
            if (ledOn != 0)
                ledOn->drawWithin (g, Rectangle<float> (x, y, width, height),
                                   RectanglePlacement::stretchToFit, 1.000f);
        }
    }

    if(isSynced.getValue()) {
        {
            int x = 368, y = 32, width = 78, height = 47;
            g.setColour (Colours::black);
            jassert (syncedDelaySwitch != 0);
            if (syncedDelaySwitch != 0)
                syncedDelaySwitch->drawWithin (g, Rectangle<float> (x, y, width, height),
                                               RectanglePlacement::stretchToFit, 1.000f);
        }
        {
            int x = 122, y = 51, width = 158, height = 148;
            g.setColour (Colours::black);
            jassert (timeSyncedGraduations != 0);
            if (timeSyncedGraduations != 0)
                timeSyncedGraduations->drawWithin (g, Rectangle<float> (x, y, width, height),
                                                   RectanglePlacement::stretchToFit, 1.000f);
        }
    } else {
        {
            int x = 368, y = 32, width = 78, height = 47;
            g.setColour (Colours::black);
            jassert (manualDelaySwitch != 0);
            if (manualDelaySwitch != 0)
                manualDelaySwitch->drawWithin (g, Rectangle<float> (x, y, width, height),
                                               RectanglePlacement::stretchToFit, 1.000f);
        }
        {
            int x = 130, y = 80, width = 150, height = 123;
            g.setColour (Colours::black);
            jassert (timeManualGraduations != 0);
            if (timeManualGraduations != 0)
                timeManualGraduations->drawWithin (g, Rectangle<float> (x, y, width, height),
                                                   RectanglePlacement::stretchToFit, 1.000f);
        }
    }
    if(performance->getToggleStateValue().getValue()) {
        {
            int x = 546, y = 4, width = 48, height = 30;
            g.setColour (Colours::black);
            jassert (performanceHighSwitch != 0);
            if (performanceHighSwitch != 0)
                performanceHighSwitch->drawWithin (g, Rectangle<float> (x, y, width, height),
                                               RectanglePlacement::stretchToFit, 1.000f);
        }
    } else {
        {
            int x = 546, y = 4, width = 48, height = 30;
            g.setColour (Colours::black);
            jassert (performanceLowSwitch != 0);
            if (performanceLowSwitch != 0)
                performanceLowSwitch->drawWithin (g, Rectangle<float> (x, y, width, height),
                                               RectanglePlacement::stretchToFit, 1.000f);
        }
    }
    {
        g.setColour(Colour (0xff101719));
        g.fillRect(tempoNumberBox->getBounds());
        g.fillRect(timeNumberBox->getBounds());
    }

    //[/UserPaint]
}

void GUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    vuMeterInput->setBounds(46, 54, 22, 213);
    vuMeterOutputLeft->setBounds(738, 54, 22, 218);
    vuMeterOutputRight->setBounds(764, 54, 21, 217);
    //[/UserPreResize]

    delayManualSlider->setBounds (148, 90, 106, 106);
    feedbackSlider->setBounds (551, 98, 106, 106);
    lowCutSlider->setBounds (150, 342, 104, 104);
    highCutSlider->setBounds (551, 338, 104, 104);
    mixSlider->setBounds (360, 377, 92, 92);
    tapButton->setBounds (376, 124, 63, 64);
    tempoSycnButton->setBounds (372, 44, 64, 25);
    delaySyncSlider->setBounds (148, 90, 106, 106);
    hostButton->setBounds (368, 82, 73, 25);
    delayTypeCombo->setBounds (354, 300, 106, 27);
    tempoNumberBox->setBounds (418, 226, 40, 20);
    inputSlider->setBounds (32, 292, 36, 36);
    outputSlider->setBounds (744, 292, 36, 36);
    bypassButton->setBounds (20, 424, 48, 48);
    timeNumberBox->setBounds (356, 226, 40, 20);
    saveButton->setBounds (706, 6, 80, 26);
    openButton->setBounds (620, 6, 80, 26);
    performance->setBounds (546, 4, 48, 30);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == delayManualSlider)
    {
        //[UserSliderCode_delayManualSlider] -- add your slider handling code here..
        delayTime.setValue(sliderThatWasMoved->getValue());
        //[/UserSliderCode_delayManualSlider]
    }
    else if (sliderThatWasMoved == feedbackSlider)
    {
        //[UserSliderCode_feedbackSlider] -- add your slider handling code here..
        processor.setFeedback(sliderThatWasMoved->getValue()/100.0);
        //[/UserSliderCode_feedbackSlider]
    }
    else if (sliderThatWasMoved == lowCutSlider)
    {
        //[UserSliderCode_lowCutSlider] -- add your slider handling code here..
        processor.setLowCut(sliderThatWasMoved->getValue());
        //[/UserSliderCode_lowCutSlider]
    }
    else if (sliderThatWasMoved == highCutSlider)
    {
        //[UserSliderCode_highCutSlider] -- add your slider handling code here..
        processor.setHighCut(sliderThatWasMoved->getValue());
        //[/UserSliderCode_highCutSlider]
    }
    else if (sliderThatWasMoved == mixSlider)
    {
        //[UserSliderCode_mixSlider] -- add your slider handling code here..
        processor.setMix(sliderThatWasMoved->getValue()/100.0);
        //[/UserSliderCode_mixSlider]
    }
    else if (sliderThatWasMoved == delaySyncSlider)
    {
        //[UserSliderCode_delaySyncSlider] -- add your slider handling code here..
        if(isSynced.getValue()) {
            delayTime.setValue(jlimit(30, 4000,
              tempoController.generateTimeInMillisFromTimeSelection(sliderThatWasMoved->getValue())));
        }
        //[/UserSliderCode_delaySyncSlider]
    }
    else if (sliderThatWasMoved == tempoNumberBox)
    {
        //[UserSliderCode_tempoNumberBox] -- add your slider handling code here..
        bpm.setValue(sliderThatWasMoved->getValue());
        //[/UserSliderCode_tempoNumberBox]
    }
    else if (sliderThatWasMoved == inputSlider)
    {
        //[UserSliderCode_inputSlider] -- add your slider handling code here..
        processor.setInputGain(sliderThatWasMoved->getValue());
        //[/UserSliderCode_inputSlider]
    }
    else if (sliderThatWasMoved == outputSlider)
    {
        //[UserSliderCode_outputSlider] -- add your slider handling code here..
        processor.setOutputGain(sliderThatWasMoved->getValue());
        //[/UserSliderCode_outputSlider]
    }
    else if (sliderThatWasMoved == timeNumberBox)
    {
        //[UserSliderCode_timeNumberBox] -- add your slider handling code here..
        delayTime.setValue(sliderThatWasMoved->getValue());
        //[/UserSliderCode_timeNumberBox]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void GUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tapButton)
    {
        //[UserButtonCode_tapButton] -- add your button handler code here..
        isSynced = true;
        bpm = tempoController.generateBpmFromTapTempo();
        //[/UserButtonCode_tapButton]
    }
    else if (buttonThatWasClicked == tempoSycnButton)
    {
        //[UserButtonCode_tempoSycnButton] -- add your button handler code here..
        isSynced = !static_cast<bool>(buttonThatWasClicked->getToggleStateValue().getValue());
        //[/UserButtonCode_tempoSycnButton]
    }
    else if (buttonThatWasClicked == hostButton)
    {
        //[UserButtonCode_hostButton] -- add your button handler code here..
        logger->writeToLog(buttonThatWasClicked->getToggleStateValue().getValue());
        if(buttonThatWasClicked->getToggleStateValue().getValue()) {
            bpm = tempoController.hostBpm;
        }
        //[/UserButtonCode_hostButton]
    }
    else if (buttonThatWasClicked == bypassButton)
    {
        //[UserButtonCode_bypassButton] -- add your button handler code here..
        isBypassed = buttonThatWasClicked->getToggleStateValue().getValue();
        //[/UserButtonCode_bypassButton]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
        String filepath = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName()
                        + String("/Tilt/MonoRepeater");
        FileChooser chooser("Save preset", File(filepath), "*.preset");
        if(chooser.browseForFileToSave(true)) {
            File file(chooser.getResult());
            if(file.existsAsFile())
                file.moveToTrash();
            FileOutputStream stream(file);
            ScopedPointer<XmlElement> xml(valueTree.state.createXml());
            xml->writeToStream(stream, String::empty);
        }
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == openButton)
    {
        //[UserButtonCode_openButton] -- add your button handler code here..
        String filepath = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName()
                        + String("/Tilt/MonoRepeater");
        FileChooser chooser("Open preset", File(filepath), "*.preset");
        if(chooser.browseForFileToOpen()) {
            XmlDocument xmlDoc(File(chooser.getResult()));
            ScopedPointer<XmlElement> xml = xmlDoc.getDocumentElement();
            if(xml) {
                ValueTree presetState (ValueTree::fromXml(*xml));
                logger->writeToLog(presetState.getType().toString());
                if(presetState.getType().toString() == "MonoRepeater")
                    valueTree.state = presetState;
            }
        }
        //[/UserButtonCode_openButton]
    }
    else if (buttonThatWasClicked == performance)
    {
        //[UserButtonCode_performance] -- add your button handler code here..
        repaint();
        //[/UserButtonCode_performance]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void GUI::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == delayTypeCombo)
    {
        //[UserComboBoxCode_delayTypeCombo] -- add your combo box handling code here..
        processor.setDelayType(comboBoxThatHasChanged->getSelectedId());
        //[/UserComboBoxCode_delayTypeCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void GUI::valueChanged(Value& valueThatChanged) {

    if(valueThatChanged.refersToSameSourceAs(delayTime)) {
        processor.setDelayTime(valueThatChanged.getValue());
        timeNumberBox->setValue(valueThatChanged.getValue(), dontSendNotification);
        delayManualSlider->setValue(valueThatChanged.getValue(), dontSendNotification);
    }

    if(valueThatChanged.refersToSameSourceAs(bpm)) {
        tempoController.bpm = valueThatChanged.getValue();
        tempoNumberBox->setValue(valueThatChanged.getValue(), dontSendNotification);
        if(isSynced.getValue()) {
            delayTime = tempoController.generateTimeInMillisFromTimeSelection(delaySyncSlider->getValue());
        }
        if(hostButton->getToggleStateValue().getValue()) {
            hostButton->triggerClick();
        }
    }

    if(valueThatChanged.refersToSameSourceAs(isSynced)) {
        if(valueThatChanged.getValue()) {
            delaySyncSlider->setEnabled(true);
            delaySyncSlider->setVisible(true);
            delayManualSlider->setEnabled(false);
            delayManualSlider->setVisible(false);
            tempoSycnButton->setToggleState(false, dontSendNotification);
            delayTime = tempoController.generateTimeInMillisFromTimeSelection(delaySyncSlider->getValue());
        } else {
            delaySyncSlider->setEnabled(false);
            delaySyncSlider->setVisible(false);
            delayManualSlider->setEnabled(true);
            delayManualSlider->setVisible(true);
            tempoSycnButton->setToggleState(true, dontSendNotification);
        }
        repaint();
    }

    if(valueThatChanged.refersToSameSourceAs(isBypassed)) {
        processor.setBypass(valueThatChanged.getValue());
        repaint();
    }
}

bool GUI::keyPressed(const KeyPress &key, Component *originatingComponent) {
    if(key == KeyPress::spaceKey) {
        tapButton->triggerClick();
    }
    return true;
}

void GUI::timerCallback() {
    if(performance->getToggleStateValue().getValue()) {
        vuMeterInput->setValue(1 * processor.getInputLevel());
        vuMeterOutputLeft->setValue(1 * processor.getOutputLeftLevel());
        vuMeterOutputRight->setValue(1 * processor.getOutputRightLevel());
    } else {
        vuMeterInput->setValue(0);
        vuMeterOutputLeft->setValue(0);
        vuMeterOutputRight->setValue(0);
    }
}

void GUI::paintOverChildren(Graphics& g) {
    {
        int x = 9, y = 18, width = 95, height = 284;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        jassert (meterGrill1 != 0);
        if (meterGrill1 != 0)
            meterGrill1->drawWithin (g, Rectangle<float> (x, y, width, height),
                                     RectanglePlacement::stretchToFit, 1.000f);
    }
    {
        int x = 702, y = 18, width = 94, height = 290;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        jassert (meterGrill2 != 0);
        if (meterGrill2 != 0)
            meterGrill2->drawWithin (g, Rectangle<float> (x, y, width, height),
                                     RectanglePlacement::stretchToFit, 1.000f);
    }
    {
        int x = 728, y = 18, width = 92, height = 290;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        jassert (meterGrill3 != 0);
        if (meterGrill3 != 0)
            meterGrill3->drawWithin (g, Rectangle<float> (x, y, width, height),
                                     RectanglePlacement::stretchToFit, 1.000f);
    }
}

void GUI::setInitialWidgetValues() {
    delayManualSlider->setValue(defaultParameterValues.defaultManualDelayTime);
    feedbackSlider->setValue(defaultParameterValues.defaultFeedback);
    lowCutSlider->setValue(defaultParameterValues.defaultLowCut);
    highCutSlider->setValue(defaultParameterValues.defaultHighCut);
    mixSlider->setValue(defaultParameterValues.defaultMix);
    inputSlider->setValue(defaultParameterValues.defaultInputGain);
    outputSlider->setValue(defaultParameterValues.defaultOutputGain);
    delaySyncSlider->setValue(defaultParameterValues.defaultSyncedDelaySelection);
    bpm.setValue(defaultParameterValues.defaultTempo);
    delayTime.setValue(defaultParameterValues.defaultManualDelayTime);
    isSynced = !defaultParameterValues.defaultTempoSyncSwitch;
    tempoSycnButton->setToggleState(defaultParameterValues.defaultTempoSyncSwitch, dontSendNotification);
    hostButton->setToggleState(defaultParameterValues.defaultHostSwitch, sendNotification);
    bypassButton->setToggleState(defaultParameterValues.defaultBypassSwitch, dontSendNotification);
    isBypassed = defaultParameterValues.defaultBypassSwitch;
    delayTypeCombo->setSelectedId(defaultParameterValues.defaultDelayType);
    timeNumberBox->setValue(defaultParameterValues.defaultManualDelayTime);
    tempoNumberBox->setValue(defaultParameterValues.defaultTempo);
    performance->setToggleState(defaultParameterValues.defaultPerformance, dontSendNotification);
}

void GUI::setDoubleClickResetFunctionality() {
    delayManualSlider->setDoubleClickReturnValue(true, defaultParameterValues.defaultManualDelayTime);
    feedbackSlider->setDoubleClickReturnValue(true, defaultParameterValues.defaultFeedback);
    lowCutSlider->setDoubleClickReturnValue(true, defaultParameterValues.defaultLowCut);
    highCutSlider->setDoubleClickReturnValue(true, defaultParameterValues.defaultHighCut);
    mixSlider->setDoubleClickReturnValue(true, defaultParameterValues.defaultMix);
    inputSlider->setDoubleClickReturnValue(true, defaultParameterValues.defaultInputGain);
    outputSlider->setDoubleClickReturnValue(true, defaultParameterValues.defaultOutputGain);
    delaySyncSlider->setDoubleClickReturnValue(true, defaultParameterValues.defaultSyncedDelaySelection);
    timeNumberBox->setVelocityBasedMode(true);
    tempoNumberBox->setVelocityBasedMode(true);
}

void GUI::initializeParametersInProcessor() {
    processor.setDelayTime(defaultParameterValues.defaultManualDelayTime);
    processor.setFeedback(defaultParameterValues.defaultFeedback/100.0);
    processor.setLowCut(defaultParameterValues.defaultLowCut);
    processor.setHighCut(defaultParameterValues.defaultHighCut);
    processor.setMix(defaultParameterValues.defaultMix/100.0);
    processor.setInputGain(defaultParameterValues.defaultInputGain);
    processor.setOutputGain(defaultParameterValues.defaultOutputGain);
    processor.setBypass(defaultParameterValues.defaultBypassSwitch);
}

void GUI::setCursorHandlesOnHover() {
    delayManualSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    delaySyncSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    feedbackSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    lowCutSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    highCutSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    mixSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    inputSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    outputSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    tempoSycnButton->setMouseCursor(MouseCursor::PointingHandCursor);
    hostButton->setMouseCursor(MouseCursor::PointingHandCursor);
    tapButton->setMouseCursor(MouseCursor::PointingHandCursor);
    bypassButton->setMouseCursor(MouseCursor::PointingHandCursor);
    delayTypeCombo->setMouseCursor(MouseCursor::PointingHandCursor);
    timeNumberBox->setMouseCursor(MouseCursor::PointingHandCursor);
    tempoNumberBox->setMouseCursor(MouseCursor::PointingHandCursor);
    openButton->setMouseCursor(MouseCursor::PointingHandCursor);
    saveButton->setMouseCursor(MouseCursor::PointingHandCursor);
    performance->setMouseCursor(MouseCursor::PointingHandCursor);
}

void GUI::setTooltips() {
    performance->setTooltip("This is a tooltip");
}

void GUI::setDisplayPopups() {
    delayManualSlider->setPopupDisplayEnabled(true, true, this);
    delayManualSlider->setTextValueSuffix(" ms");

    feedbackSlider->setPopupDisplayEnabled(true, true, this);
    feedbackSlider->setTextValueSuffix(" %");

    highCutSlider->setPopupDisplayEnabled(true, true, this);
    highCutSlider->setTextValueSuffix(" Hz");

    lowCutSlider->setPopupDisplayEnabled(true, true, this);
    lowCutSlider->setTextValueSuffix(" Hz");

    mixSlider->setPopupDisplayEnabled(true, true, this);
    mixSlider->setTextValueSuffix(" %");

    inputSlider->setPopupDisplayEnabled(true, true, this);
    inputSlider->setTextValueSuffix(" db");

    outputSlider->setPopupDisplayEnabled(true, true, this);
    outputSlider->setTextValueSuffix(" db");
}

void GUI::setValueListeners() {
    delayTime.addListener(this);
    bpm.addListener(this);
    isSynced.addListener(this);
    isBypassed.addListener(this);
}

void GUI::setCustomSVGForSliders() {
    delayManualSlider->setLookAndFeel(&largeKnobLookAndFeel);
    delaySyncSlider->setLookAndFeel(&largeKnobLookAndFeel);
    feedbackSlider->setLookAndFeel(&largeKnobLookAndFeel);
    lowCutSlider->setLookAndFeel(&largeKnobLookAndFeel);
    highCutSlider->setLookAndFeel(&largeKnobLookAndFeel);
    mixSlider->setLookAndFeel(&largeKnobLookAndFeel);
    inputSlider->setLookAndFeel(&smallKnobLookAndFeel);
    outputSlider->setLookAndFeel(&smallKnobLookAndFeel);
}

void GUI::initializeDrawings() {
    background = Drawable::createFromImageData (BinaryData::MonoDelay_png, BinaryData::MonoDelay_pngSize);
    hostButtonOff = Drawable::createFromImageData (BinaryData::HostButton_png, BinaryData::HostButton_pngSize);
    hostButtonPressed = Drawable::createFromImageData (BinaryData::HostButtonPressed_png, BinaryData::HostButtonPressed_pngSize);
    bypassSwitchOff = Drawable::createFromImageData (BinaryData::Switch_position_2_png, BinaryData::Switch_position_2_pngSize);
    bypassSwitchOn = Drawable::createFromImageData (BinaryData::Switch_position_1_png, BinaryData::Switch_position_1_pngSize);
    manualDelaySwitch = Drawable::createFromImageData (BinaryData::Switch_side_1_png, BinaryData::Switch_side_1_pngSize);
    syncedDelaySwitch = Drawable::createFromImageData (BinaryData::Switch_side_2_png, BinaryData::Switch_side_2_pngSize);
    timeManualGraduations = Drawable::createFromImageData (BinaryData::TimeManual_png, BinaryData::TimeManual_pngSize);
    timeSyncedGraduations = Drawable::createFromImageData (BinaryData::TimeSync_png, BinaryData::TimeSync_pngSize);
    ledOn = Drawable::createFromImageData (BinaryData::LED_on_png, BinaryData::LED_on_pngSize);
    ledOff = Drawable::createFromImageData (BinaryData::LED_off_png, BinaryData::LED_off_pngSize);
    meterGrill1 = Drawable::createFromImageData (BinaryData::MeterGrill_png, BinaryData::MeterGrill_pngSize);
    meterGrill2 = Drawable::createFromImageData (BinaryData::MeterGrill_png, BinaryData::MeterGrill_pngSize);
    meterGrill3 = Drawable::createFromImageData (BinaryData::MeterGrill_png, BinaryData::MeterGrill_pngSize);
    performanceHighSwitch = Drawable::createFromImageData (BinaryData::Switch_side_1_png, BinaryData::Switch_side_1_pngSize);
    performanceLowSwitch = Drawable::createFromImageData (BinaryData::Switch_side_2_png, BinaryData::Switch_side_2_pngSize);
}

void GUI::hideImageMaskedComponents() {
    tempoSycnButton->setAlpha(0);
    hostButton->setAlpha(0);
    tapButton->setAlpha(0);
    bypassButton->setAlpha(0);
    performance->setAlpha(0);
}

void GUI::addParameterListenersToValueTree() {
    valueTree.addParameterListener("delayTime", this);
    valueTree.addParameterListener("feedback", this);
    valueTree.addParameterListener("lowCut", this);
    valueTree.addParameterListener("highCut", this);
    valueTree.addParameterListener("mix", this);
}

void GUI::removeParameterListenersFromValueTree() {
    valueTree.removeParameterListener("delayTime", this);
    valueTree.removeParameterListener("feedback", this);
    valueTree.removeParameterListener("lowCut", this);
    valueTree.removeParameterListener("highCut", this);
    valueTree.removeParameterListener("mix", this);
}


void GUI::addWidgetAttachmentsToValueTree() {
    delayManualSliderAttachment = new SliderAttachment(valueTree, "delayTime", *delayManualSlider);
    feedbackSliderAttachment = new SliderAttachment(valueTree, "feedback", *feedbackSlider);
    lowCutSliderAttachment = new SliderAttachment(valueTree, "lowCut", *lowCutSlider);
    highCutSliderAttachment = new SliderAttachment(valueTree, "highCut", *highCutSlider);
    mixSliderAttachment = new SliderAttachment(valueTree, "mix", *mixSlider);

}

void GUI::parameterChanged(const String &parameterID, float newValue) {
    if(String("delayTime").equalsIgnoreCase(parameterID)) {
        processor.setDelayTime(newValue);
    }
    if(String("feedback").equalsIgnoreCase(parameterID)) {
        processor.setFeedback(newValue/100.0f);
    }
    if(String("lowCut").equalsIgnoreCase(parameterID)) {
        processor.setLowCut(newValue);
    }
    if(String("highCut").equalsIgnoreCase(parameterID)) {
        processor.setHighCut(newValue);
    }
    if(String("mix").equalsIgnoreCase(parameterID)) {
        processor.setMix(newValue/100.0f);
    }

}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GUI" componentName="" parentClasses="public AudioProcessorEditor, public ValueListener, public Timer, public KeyListener, public AudioProcessorValueTreeState::Listener"
                 constructorParams="MonoDelayAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; valueTreeState"
                 variableInitialisers="AudioProcessorEditor (&amp;p), valueTree(valueTreeState), processor (p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="820" initialHeight="532">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="delayManualSlider" id="b8e378e1c3c3e2b8" memberName="delayManualSlider"
          virtualName="" explicitFocusOrder="0" pos="148 90 106 106" min="30"
          max="4000" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.69999999999999995559"
          needsCallback="1"/>
  <SLIDER name="feedbackSlider" id="6c5e92cf26f63c8" memberName="feedbackSlider"
          virtualName="" explicitFocusOrder="0" pos="551 98 106 106" min="0"
          max="100" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="lowCutSlider" id="9ff1212179ee864c" memberName="lowCutSlider"
          virtualName="" explicitFocusOrder="0" pos="150 342 104 104" min="20"
          max="2000" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="highCutSlider" id="791167b72de44ea3" memberName="highCutSlider"
          virtualName="" explicitFocusOrder="0" pos="551 338 104 104" min="500"
          max="20000" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="mixSlider" id="3db3e6b642af78d0" memberName="mixSlider"
          virtualName="" explicitFocusOrder="0" pos="360 377 92 92" min="0"
          max="100" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TEXTBUTTON name="tapButton" id="cb18ec5dc03fe671" memberName="tapButton"
              virtualName="" explicitFocusOrder="0" pos="376 124 63 64" buttonText="Tap"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="tempoSyncButton" id="4ba7333253143d2c" memberName="tempoSycnButton"
                virtualName="" explicitFocusOrder="0" pos="372 44 64 25" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="delaySyncSlider" id="36d7aeadd94813ed" memberName="delaySyncSlider"
          virtualName="" explicitFocusOrder="0" pos="148 90 106 106" min="0"
          max="10" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TOGGLEBUTTON name="hostButton" id="32ba96947a67f67" memberName="hostButton"
                virtualName="" explicitFocusOrder="0" pos="368 82 73 25" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="delayTypeCombo" id="dff6e15bf579cb62" memberName="delayTypeCombo"
            virtualName="" explicitFocusOrder="0" pos="354 300 106 27" editable="0"
            layout="33" items="Digital&#10;Ping Pong&#10;Reverse" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <SLIDER name="tempoNumberBox" id="2d608151cd509631" memberName="tempoNumberBox"
          virtualName="" explicitFocusOrder="0" pos="418 226 40 20" bkgcol="ff0e1214"
          thumbcol="ff12181b" rotaryslideroutline="ff1a2227" textboxtext="ff66e0ff"
          textboxbkgd="ff112028" textboxhighlight="ff171f22" textboxoutline="ff101719"
          min="1" max="400" int="1" style="LinearBarVertical" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="inputSlider" id="57c22f00ac0b1b62" memberName="inputSlider"
          virtualName="" explicitFocusOrder="0" pos="32 292 36 36" min="-60"
          max="6" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="3" needsCallback="1"/>
  <SLIDER name="outputSlider" id="6627a14743990eba" memberName="outputSlider"
          virtualName="" explicitFocusOrder="0" pos="744 292 36 36" min="-60"
          max="6" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="3" needsCallback="1"/>
  <TOGGLEBUTTON name="bypassButton" id="f38b829114906620" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="20 424 48 48" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="timeNumberBox" id="408f5682666bb34" memberName="timeNumberBox"
          virtualName="" explicitFocusOrder="0" pos="356 226 40 20" bkgcol="ff0e1214"
          thumbcol="ff12181b" rotaryslideroutline="ff1a2227" textboxtext="ff66e0ff"
          textboxbkgd="ff112028" textboxhighlight="ff171f22" textboxoutline="ff101719"
          min="30" max="4000" int="1" style="LinearBarVertical" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TEXTBUTTON name="saveButton" id="7a64a143363493d5" memberName="saveButton"
              virtualName="" explicitFocusOrder="0" pos="706 6 80 26" buttonText="Save"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="openButton" id="f902f658793b38ff" memberName="openButton"
              virtualName="" explicitFocusOrder="0" pos="620 6 80 26" buttonText="Open"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="performance" id="772dd1dd736bf73c" memberName="performance"
                virtualName="" explicitFocusOrder="0" pos="546 4 48 30" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
