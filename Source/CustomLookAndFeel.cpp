//
//  CustomLookAndFeel.cpp
//  MaximilianTest - App
//
//  Created by Akash Murthy on 26/12/17.
//

#include "CustomLookAndFeel.h"

void LargeKnobLookAndFeel::drawRotarySlider (
       Graphics& g,
       int x,
       int y,
       int width,
       int height,
       float sliderPos,
       float rotaryStartAngle,
       float rotaryEndAngle,
       Slider& slider
) {
    
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    drawFromSVG (g, 0, 0, slider.getWidth(), slider.getHeight(),
                 AffineTransform::rotation (angle, slider.getWidth() / 2, slider.getWidth() / 2));
}

void LargeKnobLookAndFeel::drawFromSVG (Graphics& g, int x, int y, int newWidth,
                                     int newHeight, AffineTransform affine)
{
    ScopedPointer<XmlElement> svg (XmlDocument::parse (BinaryData::rslider_svg));
    
    if (svg == nullptr)
        jassert (false);
    
    ScopedPointer<Drawable> drawable;
    
    if (svg != nullptr)
    {
        drawable = Drawable::createFromSVG (*svg);
        drawable->setTransformToFit (Rectangle<float> (x, y, newWidth, newHeight), RectanglePlacement::stretchToFit);
        drawable->draw (g, 1.f, affine);
    }
}

void SmallKnobLookAndFeel::drawRotarySlider (
                                             Graphics& g,
                                             int x,
                                             int y,
                                             int width,
                                             int height,
                                             float sliderPos,
                                             float rotaryStartAngle,
                                             float rotaryEndAngle,
                                             Slider& slider
                                             ) {
    
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    drawFromSVG (g, 0, 0, slider.getWidth(), slider.getHeight(),
                 AffineTransform::rotation (angle, slider.getWidth() / 2, slider.getWidth() / 2));
}

void SmallKnobLookAndFeel::drawFromSVG (Graphics& g, int x, int y, int newWidth,
                                        int newHeight, AffineTransform affine)
{
    ScopedPointer<XmlElement> svg (XmlDocument::parse (BinaryData::rslider_white_svg));
    
    if (svg == nullptr)
        jassert (false);
    
    ScopedPointer<Drawable> drawable;
    
    if (svg != nullptr)
    {
        drawable = Drawable::createFromSVG (*svg);
        drawable->setTransformToFit (Rectangle<float> (x, y, newWidth, newHeight), RectanglePlacement::stretchToFit);
        drawable->draw (g, 1.f, affine);
    }
}
