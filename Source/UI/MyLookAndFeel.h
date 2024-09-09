/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 12 Sep 2019 9:36:07am
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
using namespace juce;

const Colour Colour_1 = Colour(105, 105, 105);
const Colour Colour_2 = Colour(0, 0, 0).withAlpha(0.0f);
const Colour Colour_3 = Colour(0, 0, 0).withAlpha(0.3f);
const Colour Colour_4 = Colour(0, 0, 0).withAlpha(0.6f);
const Colour Colour_5 = Colour(105, 105, 105).withAlpha(0.3f);
const Colour Colour_6 = Colour(0, 0, 0).withAlpha(0.8f);
const Colour Colour_7 = Colour(125, 125, 125);

//const Font font_1 ("Helvetica Neue", 12.00f, Font::bold);
//const Font font_2 ("Helvetica Neue", 22.00f, Font::bold);
//const Font font_3 ("Helvetica Neue", 48.00f, Font::bold);

const Font font_1(12.00f, Font::bold);
const Font font_2(22.00f, Font::bold);
const Font font_3(48.00f, Font::bold);

class MyLookAndFeel
	: public LookAndFeel_V4
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

	/** comboBoxes **/
    //  Font getLabelFont(Label& label) override
    //  {
    //      return font_1;
    //  }

	void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
		bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
		const String& text, const String& shortcutKeyText,
		const Drawable* icon, const Colour* textColour) override
	{
		juce::Rectangle<int> r(area);

		Colour fillColour = isHighlighted ? Colour_5 : Colour_4;
		g.setColour(fillColour);
		g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1);

		Colour myTextColour = isTicked ? Colour_7 : Colour_1;
		g.setColour(myTextColour);
        g.setFont(font_1);
        
        r.setLeft(10);
        r.setY(1);
        g.drawFittedText(text, r, Justification::left, 1);
    }
    
    void drawComboBox (Graphics& g, int width, int height, bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH,
                       ComboBox& box) override
    {
        const float cornerSize = 3.0f;
        const juce::Rectangle<int> boxBounds (0, 0, width, height);
        
        g.setColour(Colour_3);
        g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);
        
        juce::Rectangle<int> arrow (width - 30, 0, 20, height);
        
        Path path;
        
        path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
        path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
        path.lineTo(arrow.toFloat().getRight() - 3.0f, arrow.toFloat().getCentreY() - 2.0f);
        
        Colour arrowColour = box.findColour(ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
        g.setColour(arrowColour);
        g.strokePath(path, PathStrokeType(2.0f));
    }
    
    /** buttons **/
    //Font getTextButtonFont (TextButton&, int buttonHeight) override
    //{
    //    return font_1;
    //}
    
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

};
