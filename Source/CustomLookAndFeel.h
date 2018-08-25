//
//  CustomLookAndFeel.hpp
//  MaximilianTest - App
//
//  Created by Akash Murthy on 26/12/17.
//

#ifndef CustomLookAndFeel_hpp
#define CustomLookAndFeel_hpp

#include "../JuceLibraryCode/JuceHeader.h"


class LargeKnobLookAndFeel : public LookAndFeel_V4 {
    
public:
    void drawRotarySlider (
       Graphics& g,
       int x,
       int y,
       int width,
       int height,
       float sliderPosProportional,
       float rotaryStartAngle,
       float rotaryEndAngle,
       Slider& slider
   ) override;
    
private:
    void drawFromSVG (Graphics& g, int x, int y, int newWidth, int newHeight, AffineTransform affine);
};

class SmallKnobLookAndFeel : public LookAndFeel_V4 {

public:
    void drawRotarySlider (
                           Graphics& g,
                           int x,
                           int y,
                           int width,
                           int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           Slider& slider
                           ) override;
    
private:
    void drawFromSVG (Graphics& g, int x, int y, int newWidth, int newHeight, AffineTransform affine);
};

#endif /* CustomLookAndFeel_hpp */

