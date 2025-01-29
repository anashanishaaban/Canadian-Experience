/**
 * @file Sparty.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include "Sparty.h"
#include "Box.h"

/// Speed of the pop-up animation
const double SpringWireSize = 2.0;

/// Speed of the pop-up animation
const double SpringWireMinSpacing = 0.5;

/// Speed of the pop-up animation
const int NumSpringLinks = 13;

/// Speed of the pop-up animation
const double SpartyPopupDuration = 25;

/// Speed of the pop-up animation
const wxColour SpringColor(220, 220, 220);

/**
 * Constructor
 * @param imagePath Path to the Sparty image
 * @param size Size of Sparty
 * @param compressedLength Compressed length of the spring
 */
Sparty::Sparty(const std::wstring& imagePath, double size, double compressedLength)
    : mSize(size), mCompressedLength(compressedLength)
{
    // Load the Sparty image
    mSpartyImage = std::make_shared<wxBitmap>(imagePath, wxBITMAP_TYPE_PNG);

    // Calculate the extended length (spring fully decompressed)
    mExtendedLength = mCompressedLength + mSize; // Sparty's size is added to the spring length

    // Initialize current length to compressed length
    mCurrentLength = mCompressedLength;
}

/**
 * Set the position of Sparty
 * @param position Position of Sparty
 */
void Sparty::SetPosition(const wxPoint& position)
{
    mPosition = position;
}

/**
 * Draw Sparty and the spring
 * @param graphics Graphics context to draw on
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!graphics) return;

    // Save the current graphics state
    graphics->PushState();

    // Move to Sparty's position
    graphics->Translate(mPosition.x, mPosition.y);

    // Draw the spring
    wxPen pen(SpringColor, SpringWireSize);
    graphics->SetPen(pen);

    DrawSpring(graphics, 0, -25, -mCurrentLength, 300 / 4, NumSpringLinks);

    // Draw Sparty image
    graphics->DrawBitmap(*mSpartyImage,
                         -mSize / 2,
                         -mCurrentLength - mSize,
                         mSize,
                         mSize);

    // Restore the previous graphics state
    graphics->PopState();

}

/**
 * Update Sparty's state
 * @param elapsed Time since the last update
 */
void Sparty::Update(double elapsed)
{
    if (mIsPoppingUp)
    {
        mPopupTime += elapsed * PopupSpeed; // Increase speed

        // Calculate the progress of the popup animation (0.0 to 1.0)
        double t = mPopupTime / SpartyPopupDuration;

        if (t >= 1.0)
        {
            t = 1.0;
            mIsPoppingUp = false;
        }

        // Ease-out effect using a smooth step function
        double smoothT = t * t * (3 - 2 * t);

        // Update the current length of the spring
        mCurrentLength = mCompressedLength + smoothT * (mExtendedLength - mCompressedLength);
    }
}

/**
 * Trigger the pop-up animation
 */
void Sparty::TriggerPopUp()
{
    if (!mIsPoppingUp)
    {
        mIsPoppingUp = true;
        mPopupTime = 0.0;

        // Reset current length to the starting y coordinate for animation
        mCurrentLength = mCompressedLength;
    }
}

/**
 * Draw a spring
 * @param graphics Graphics context to draw on
 * @param x X position of the spring
 * @param y Y position of the spring
 * @param length Length of the spring
 * @param width Width of the spring
 * @param numLinks Number of links in the spring
 */
void Sparty::DrawSpring(std::shared_ptr<wxGraphicsContext> graphics,

                        int x, int y, double length, double width, int numLinks)

{

    auto path = graphics->CreatePath();



    // We keep track of three locations, the bottom of which

    // is y1. First half-loop will be y1 to y3, second half-loop

    // will be y3 to y2.

    double y1 = y;

    double linkLength = length / numLinks;



    // Left and right X values

    double xR = x + width / 2;

    double xL = x - width / 2;



    path.MoveToPoint(x, y1);



    for(int i=0; i<numLinks; i++)

    {

        auto y2 = y1 + linkLength;

        auto y3 = y2 + linkLength / 2;



        path.AddCurveToPoint(xR, y1, xR, y3, x, y3);

        path.AddCurveToPoint(xL, y3, xL, y2, x, y2);



        y1 = y2;

    }



    graphics->StrokePath(path);

}

/**
 * Reset Sparty to its initial state
 */
void Sparty::Reset() {
    mIsPoppingUp = false;
    mPopupTime = 0.0;
    mCurrentLength = mCompressedLength;
}