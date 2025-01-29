/**
 * @file Box.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include <iostream>
#include "Box.h"
#include "Const.h"

/// The background image to use
const std::wstring BoxBackgroundImage = L"/box-background.png";

/// The foreground image to use
const std::wstring BoxForegroundImage = L"/box-foreground.png";

/// The lid image to use
const std::wstring BoxLidImage = L"/box-lid.png";

/// The horizontal scale for the lid when the angle is zero
const double LidZeroAngleScale = 0.02;

/// How long it takes to up the lid in seconds
const double LidOpeningTime = 0.25;

Box::Box(const std::wstring& imagesDir, int boxSize, int lidSize)
{
    mImageDirectory = imagesDir;
    mBoxSize = boxSize;
    mLidSize = lidSize;
    mLidAngle = 0; // Lid starts flat
    mLidOpening = false;
    mLidClosing = false;

    // Load images
    mBackground = std::make_shared<wxBitmap>(mImageDirectory + L"/box-background.png", wxBITMAP_TYPE_PNG);
    mForeground = std::make_shared<wxBitmap>(mImageDirectory + L"/box-foreground.png", wxBITMAP_TYPE_PNG);
    mLid = std::make_shared<wxBitmap>(mImageDirectory + L"/box-lid.png", wxBITMAP_TYPE_PNG);
}



/**
 * Draw the box
 * @param graphics Graphics context to draw on
 */
void Box::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!graphics) return;

    // Draw background
    graphics->DrawBitmap(*mBackground, mPosition.x - mBoxSize / 2, mPosition.y, mBoxSize, mBoxSize);

    // Draw lid
    graphics->PushState(); // Save the current transformation state

    // Translate to the hinge point (top-center of the box)
    graphics->Translate(mPosition.x - mLidSize / 2, mPosition.y);

    // Compute the scale factor based on the lid angle
    double scaleY = sin(mLidAngle);
    if (scaleY < 0.1) scaleY = 0.02; // Lid cannot have negative height
    if (scaleY > 1.0) scaleY = 1.0; // Maximum scale is 1 (full height)

    // Compute the current height of the lid
    double currentHeight = mLidSize * scaleY;

    // Draw the lid bitmap with the current height
    graphics->DrawBitmap(*mLid, 0, -currentHeight, mLidSize, currentHeight);

    graphics->PopState(); // Restore the previous transformation state

    // Draw foreground
    //graphics->DrawBitmap(*mForeground, mPosition.x - mBoxSize / 2, mPosition.y, mBoxSize, mBoxSize);
}


/**
 * Update the state of the box (e.g., opening the lid)
 * @param elapsedTime Time passed since the last update
 */
void Box::Update(double elapsedTime)
{
    const double lidOpeningSpeed = (Const::PI / 2) / (LidOpeningTime*100); // Speed to open in radians per second

    if (mLidOpening && mLidAngle < (Const::PI / 2)) // Open until 90 degrees
    {
        mLidAngle += elapsedTime * lidOpeningSpeed* 70;
        if (mLidAngle >= (Const::PI / 2))
        {
            mLidAngle = (Const::PI / 2); // Stop at 90 degrees
            mLidOpening = false;
        }
    }
    else if (mLidClosing && mLidAngle > 0) // Close until flat
    {
        mLidAngle -= elapsedTime * lidOpeningSpeed;
        if (mLidAngle <= 0)
        {
            mLidAngle = 0; // Stop at flat
            mLidClosing = false;
        }
    }
}

/**
 * Trigger the lid to open
 */
void Box::TriggerLidOpen()
{
    mLidOpening = true;
    mLidClosing = false;
}

/**
 * Trigger the lid to close
 */
void Box::TriggerLidClose()
{
    mLidClosing = true;
    mLidOpening = false;
}

/**
 * Handle a key press
 * @param event The key event
 */
void Box::OnKeyDown(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_SPACE) // Open lid with spacebar
    {
        TriggerLidOpen();
    }
    else if (event.GetKeyCode() == WXK_BACK) // Close lid with backspace
    {
        TriggerLidClose();
    }
}

void Box::DrawForeground(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!graphics) return;

    // Draw the box foreground
    graphics->DrawBitmap(*mForeground, mPosition.x - mBoxSize / 2, mPosition.y, mBoxSize, mBoxSize);
}

void Box::Reset()
{
    mLidClosing = true;
    mLidOpening = false;
    mLidAngle = 0;
}

