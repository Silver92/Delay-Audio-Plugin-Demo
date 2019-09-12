/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 12 Sep 2019 9:36:07am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

const Colour Colour_1 = Colour(105, 105, 105);
const Colour Colour_2 = Colour(0, 0, 0).withAlpha(0.0f);
const Colour Colour_3 = Colour(0, 0, 0).withAlpha(0.3f);
const Colour Colour_4 = Colour(0, 0, 0).withAlpha(0.6f);
const Colour Colour_5 = Colour(105, 105, 105).withAlpha(0.3f);
const Colour Colour_6 = Colour(0, 0, 0).withAlpha(0.8f);
const Colour Colour_7 = Colour(125, 125, 125);

const Font font_1 ("Helvetica Neue", 12.00f, Font::bold);
const Font font_2 ("Helvetica Neue", 22.00f, Font::bold);
const Font font_3 ("Helvetica Neue", 48.00f, Font::bold);

class MyLookAndFeel
:   public LookAndFeel_V4
{
public:
    MyLookAndFeel()
    {
        // Set button colours
        setColour(TextButton::buttonColourId, Colour_1);
        setColour(TextButton::textColourOnId, Colour_1);
        setColour(TextButton::textColourOffId, Colour_1);
    }
    
    ~MyLookAndFeel() {};
    
    /** buttons **/
    Font getTextButtonFont (TextButton&, int buttonHeight) override
    {
        return font_1;
    }
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        Colour fillColour;
        
        if (shouldDrawButtonAsDown) {
            fillColour = Colour_6;
        } else if (shouldDrawButtonAsHighlighted) {
            fillColour = Colour_3;
        } else {
            fillColour = Colour_5;
        }
        
        const float cornerSize = 6.0f;
        const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
        
        g.setColour(fillColour);
        g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
    }
    
private:
    
    Image mSliderImage;
};
