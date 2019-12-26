/*
  ==============================================================================

    FX_Panel.cpp
    Created: 8 Sep 2019 8:12:16pm
    Author:  Silver

  ==============================================================================
*/

#include "FX_Panel.h"
#include "Panel_Base.h"

FXPanel::FXPanel(MyDelayPluginAudioProcessor* inProcessor)
:   PanelBase(inProcessor)
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
    
    //=================================================================================
    // Set up the positions of the UI components
    
    int x = SLIDER_POS_X;
    int y = SLIDER_POS_Y;
    
    mTimeSliderTypeButton.reset(
    new ParameterButton(mProcessor->parameters, Parameter_TimeSliderType));
    mTimeSliderTypeButton->setBounds(x + SLIDER_SIZE + SLIDER_INTERVAL,
                                     y - SLIDER_SIZE/5,
                                     SLIDER_SIZE,
                                     SLIDER_SIZE);
    
    auto index = mProcessor->getParameters().getUnchecked(Parameter_TimeSliderType);
    mTimeSliderTypeButton->setToggleState(index, dontSendNotification);
    
    if (!(index->getValue())) {
        drawIntervalSlider(x, y, Parameter_DelayTime, 0.0f, 1.0f, "s");
        mTimeSliderTypeButton->setButtonText("Beat Mode");
        mTimeSliderTypeButton->setToggleState(false, dontSendNotification);
    } else {
        drawSlider(x, y, Parameter_DelayTime, 0.05f, 2.0f, "s");
        mTimeSliderTypeButton->setButtonText("Time Mode");
        mTimeSliderTypeButton->setToggleState(true, dontSendNotification);
    }
    
    mTimeSliderTypeButton->onClick = [this, x, y]{
        if (mTimeSliderTypeButton->getToggleState()) {
            for (int i = 0; i < mSliders.size(); i++) {
                if (mSliders[i]->getName() ==
                    ParameterID[Parameter_DelayTime]) {
                    mSliders.remove(i);
                    mSliderTexts.remove(i);
                    mLabels.remove(i);
                }
            }
            drawIntervalSlider(x, y, Parameter_DelayTime, 0.0f, 1.0f, "s");
            mTimeSliderTypeButton->setButtonText("Beat Mode");
            mTimeSliderTypeButton->setToggleState(false, dontSendNotification);
        } else {
            for (int i = 0; i < mSliders.size(); i++) {
                if (mSliders[i]->getName() ==
                    ParameterID[Parameter_DelayTime]) {
                    mSliders.remove(i);
                    mBeatSliderBox.reset();
                    mLabels.remove(i);
                }
            }
            drawSlider(x, y, Parameter_DelayTime, 0.05f, 2.0f, "s");
            mTimeSliderTypeButton->setButtonText("Time Mode");
            mTimeSliderTypeButton->setToggleState(true, dontSendNotification);
        }
    };
    addAndMakeVisible(mTimeSliderTypeButton.get());
    
    //=================================================================================
    
    y = y + SLIDER_SIZE + SLIDER_INTERVAL;
    drawSlider(x, y, Parameter_DelayFeedback, 0.f, 100.f, "%");
    
    //=================================================================================
    
    x = x + SLIDER_SIZE + SLIDER_INTERVAL;
    drawSlider(x, y, Parameter_DelayDryWet, 0.0f, 100.f, "%");
    
}

FXPanel::~FXPanel()
{
    
}
    
void FXPanel::paint(Graphics& g)
{
    
}

void FXPanel::drawSlider(int x,
                         int y,
                         int parameterIndex,
                         float minRange,
                         float maxRange,
                         String inUnit)
{
    drawSliderLabel(x, y, parameterIndex);
    
    // Draw the slider
    RotarySlider* slider = new RotarySlider(mProcessor->parameters, parameterIndex);
    slider->setColour(Slider::thumbColourId, Colours::black);
    slider->setBounds(x, y, SLIDER_SIZE, SLIDER_SIZE);
    addAndMakeVisible(slider);
    mSliders.add(slider);
    
    // Draw the slider text
    SliderText* text = new SliderText();
    text->setParameterID(parameterIndex);
    text->setTextRange(minRange, maxRange);
    text->setUnit(inUnit);
    text->setFont(Font(23.0f));
    text->setBounds(x + SLIDER_SIZE * 0.1,
                    y - SLIDER_SIZE / 4 + 5,
                    SLIDER_SIZE * 0.8,
                    SLIDER_SIZE / 4);
    addAndMakeVisible(text);
    mSliderTexts.add(text);
    
    // Denote the default values
    auto val = *(mProcessor->parameters.
    getRawParameterValue(ParameterID[text->getParameterID()]));
    auto timeSliderType = mProcessor->getParameters().
    getUnchecked(Parameter_TimeSliderType)->getValue();
    
    std::cout << "parameter index " << parameterIndex << std::endl;
    std::cout << "parameter value in processor " << timeSliderType<< std::endl;
    
    if (parameterIndex == Parameter_DelayTime && !timeSliderType)
    {
        std::cout << "slider val = " << val << std::endl;
        std::cout << "slider val = " << static_cast<int>(val * (NoteType_TotalNumNoteTypes - 1 )) << std::endl;
        val = NoteTypeValue[static_cast<int>(val * (NoteType_TotalNumNoteTypes - 1))]
                    / (mProcessor->currentPositionInfo.bpm);
        std::cout << "slider val = " << val << std::endl;
        val = jlimit(0.05f, 2.0f, val);
        std::cout << "slider val = " << val << std::endl;
        String tempString = String(val, 2);
        text->setText(tempString + text->getUnit(), dontSendNotification);
        text->setJustificationType(Justification::centred);
        
        val = jmap(val, 0.05f, 2.0f, 0.f, 1.f);
        std::cout << "slider val = " << val << std::endl;
        slider->setValue(val);
    }
    else
    {
        val = jmap(val, text->getMinRange(), text->getMaxRange());
        String tempString = (text->getParameterID() == Parameter_DelayTime) ?
        String(val, 2) : String(static_cast<int>(val));
        text->setText(tempString + text->getUnit(), dontSendNotification);
        text->setJustificationType(Justification::centred);
    }
    
    // Set up the right text and the values on each slider text and slider when the user
    // changes the slider text
    text->onTextChange = [slider, text]{
        auto maxVal = text->getMaxRange();
        auto minVal = text->getMinRange();
        auto currentVal = text->getText().getFloatValue();
        if (currentVal >= maxVal) {
            text->setText(String(maxVal, 2) +
                          text->getUnit(),
                          dontSendNotification);
        }
        else if (currentVal <= minVal) {
            text->setText(String(minVal, 2) +
                          text->getUnit(),
                          dontSendNotification);
        }
        else {
            currentVal = jmap(currentVal,
                              minVal,
                              maxVal,
                              static_cast<float>(slider->getMinimum()),
                              static_cast<float>(slider->getMaximum()));
        }
        
        if (slider->getValue() == currentVal) {
            auto tempVal = jmap(currentVal,
                                static_cast<float>(slider->getMinimum()),
                                static_cast<float>(slider->getMaximum()),
                                minVal,
                                maxVal);
            String tempString = (text->getParameterID() == Parameter_DelayTime) ?
                                String(tempVal, 2) : String(static_cast<int>(tempVal));
            text->setText(tempString + text->getUnit(), dontSendNotification);
        }
        
        slider->setValue(currentVal);
    };
    
    //=================================================================================
    // Set up the right text and the values on each slider text and slider when the user
    // changes the sliders
    slider->onValueChange = [this, text]{
        auto val = *(mProcessor->parameters.
        getRawParameterValue(ParameterID[text->getParameterID()]));
        val = jmap(val,
                   text->getMinRange(),
                   text->getMaxRange());
        String tempString = (text->getParameterID() == Parameter_DelayTime) ?
        String(val, 2) : String(static_cast<int>(val));
        text->setText(tempString + text->getUnit(), dontSendNotification);
        text->setJustificationType(Justification::centred);
    };
}

void FXPanel::drawSliderLabel(int x, int y, int parameterIndex) {
    Label* label = new Label();
    label->setFont(Font(18.0f));
    label->setText(ParameterLabel[parameterIndex], dontSendNotification);
    label->setColour(Label::textColourId, Colours::black);
    label->setJustificationType(Justification::centred);
    label->setBounds(x, y - SLIDER_SIZE * 0.55, SLIDER_SIZE, SLIDER_SIZE / 2);
    addAndMakeVisible(label);
    mLabels.add(label);
}

void FXPanel::drawIntervalSlider(int x, int y, int parameterIndex, float minRange,
                                 float maxRange, String inUnit)
{
    drawSliderLabel(x, y, parameterIndex);
    
    // Draw the slider
    RotarySlider* slider = new RotarySlider(mProcessor->parameters,
                                                  parameterIndex);
    slider->setColour(Slider::thumbColourId, Colours::black);
    slider->setBounds(x, y, SLIDER_SIZE, SLIDER_SIZE);
    slider->setInterval();
    addAndMakeVisible(slider);
    mSliders.add(slider);
    
    // Draw the slider text
    mBeatSliderBox.reset(new ComboBox());
    mBeatSliderBox->setBounds(x + SLIDER_SIZE * 0.1,
                              y - SLIDER_SIZE / 4 + 5,
                              SLIDER_SIZE * 0.8,
                              SLIDER_SIZE / 4);
    for (int i = 0; i < NoteType_TotalNumNoteTypes; i++) {
        mBeatSliderBox->addItem(NoteTypeLabel[i], i+1);
    }
    addAndMakeVisible(mBeatSliderBox.get());
    
    // Denote the default values
    auto val = *(mProcessor->parameters.
    getRawParameterValue(ParameterID[parameterIndex]));
    auto timeSliderType = mProcessor->getParameters().
    getUnchecked(Parameter_TimeSliderType)->getValue();
    
    std::cout << "parameter index " << parameterIndex << std::endl;
    std::cout << "parameter value in processor " << timeSliderType<< std::endl;
    
    if (timeSliderType)
    {
        // refresh the slider and text according to the input
        std::cout << "val " << val << std::endl;
        val = jmap(val, 0.f, 1.f, 0.05f, 2.f);
        val = val * (mProcessor->currentPositionInfo.bpm);
        std::cout << "val " << val << std::endl;
        float minimum = 10000;
        int index = 0;
        auto tmp = 0;
        for (int i = 0; i < NoteType_TotalNumNoteTypes; i++) {
            tmp = abs(val - NoteTypeValue[i]);
            std::cout << "difference = " << tmp << std::endl;
            if (tmp < minimum) {
                index = i;
                minimum = tmp;
            }
        }
        mBeatSliderBox->setSelectedItemIndex(index);
        slider->setValue(index / static_cast<float> (NoteType_TotalNumNoteTypes - 1));
    }
    else
    {
        mBeatSliderBox->setSelectedItemIndex(val * static_cast<float> (NoteType_TotalNumNoteTypes - 1));
    }
    
    //=================================================================================
    // Set up the right text and the values on each slider text and slider when the user
    // changes the sliders
    slider->onValueChange = [this, parameterIndex]{
        auto val = *(mProcessor->parameters.
        getRawParameterValue(ParameterID[parameterIndex]));
        mBeatSliderBox->setSelectedItemIndex(val * (NoteType_TotalNumNoteTypes - 1));
    };
    
    // Set up the right text and the values on each slider text and slider when the user
    // changes the slider text
    mBeatSliderBox->onChange = [this, slider]{
        auto currentVal = mBeatSliderBox->getSelectedItemIndex();
        slider->setValue(currentVal / static_cast<float> (NoteType_TotalNumNoteTypes - 1));
    };
}
