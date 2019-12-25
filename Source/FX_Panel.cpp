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
    mTimeSliderTypeButton->setToggleState(index->getValue(), dontSendNotification);
    
    if (!mTimeSliderTypeButton->getToggleState()) {
        drawIntervalSlider(x, y, Parameter_DelayTime, 0.0f, 1.0f, "s");
        mTimeSliderTypeButton->setButtonText("Beat Mode");
        mTimeSliderTypeButton->setToggleState(true, dontSendNotification);
    } else {
        drawSlider(x, y, Parameter_DelayTime, 0.05f, 2.0f, "s");
        mTimeSliderTypeButton->setButtonText("Time Mode");
        mTimeSliderTypeButton->setToggleState(false, dontSendNotification);
    }
    
    mTimeSliderTypeButton->onClick = [this, x, y]{
        if (!mTimeSliderTypeButton->getToggleState()) {
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
            mTimeSliderTypeButton->setToggleState(true, dontSendNotification);
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
            mTimeSliderTypeButton->setToggleState(false, dontSendNotification);
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
    val = jmap(val, text->getMinRange(), text->getMaxRange());
    String tempString = (text->getParameterID() == Parameter_DelayTime) ?
    String(val, 2) : String(static_cast<int>(val));
    text->setText(tempString + text->getUnit(), dontSendNotification);
    text->setJustificationType(Justification::centred);
    
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
    mBeatSliderBox->setSelectedItemIndex(val * 13);
    
    //=================================================================================
    // Set up the right text and the values on each slider text and slider when the user
    // changes the sliders
    slider->onValueChange = [this, parameterIndex]{
        auto val = *(mProcessor->parameters.
        getRawParameterValue(ParameterID[parameterIndex]));
        mBeatSliderBox->setSelectedItemIndex(val * 13);
    };
    
    // Set up the right text and the values on each slider text and slider when the user
    // changes the slider text
    mBeatSliderBox->onChange = [this, slider]{
        auto currentVal = mBeatSliderBox->getSelectedItemIndex();
        slider->setValue(currentVal / 13.f);
    };
}
