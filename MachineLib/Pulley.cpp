/**
 * @file Pulley.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include "Pulley.h"
#include <wx/graphics.h>
#include <wx/colour.h>
#include <wx/pen.h>
#include <wx/brush.h>
#include <wx/wx.h>

/// Constants for pulley appearance
const double PulleyHubWidth = 3;        // How wide the hub is on each side of the pulley
const double PulleyBeltDepth = 3;       // How deep the belt is into the pulley
/// The color of the pulley
const wxColour PulleyColor = wxColour(205, 250, 5);

/// Constants for pulley hub appearance
const wxColour PulleyHubLineColor = wxColour(139, 168, 7);

/// The width of the lines on the pulley hub
const int PulleyHubLineWidth = 4;
/// The divisor used to determine the number of lines on the pulley hub
const double PulleyHubLineCountDiviser = 6.0;
const double BeltThickness = 2.0;      // Thickness of the belt

/// The color of the belt
const wxColour BeltColor = *wxBLACK;

/**
 * Constructor
 * @param radius Radius of the pulley
 * @param initialRotation Initial rotation (speed or angle) of this pulley
 * @param positionX X position where the pulley is drawn
 * @param positionY Y position where the pulley is drawn
 */
Pulley::Pulley(double radius, double initialRotation, double positionX, double positionY)
    : mRadius(radius), mRotation(initialRotation), mPositionX(positionX), mPositionY(positionY)
{
    // By default, no special lines setup is done here.
}

/**
 * Receive rotation from a source
 * @param rotation The rotation value
 */
void Pulley::ReceiveRotation(double rotation)
{
    // Apply the input ratio to incoming rotation
    double adjustedRotation = rotation * mInputRatio;

    mRotation = adjustedRotation;

    // Update the source with this new rotation and notify all sinks connected to this pulley
    mSource.SetRotation(mRotation);
    mSource.NotifySinks();
}

/**
 * Connect this pulley to another pulley via a belt.
 * This pulley acts as the driving pulley, and the other as the driven pulley.
 * @param otherPulley The pulley to connect to
 */
void Pulley::ConnectToPulley(std::shared_ptr<Pulley> otherPulley)
{
    // Compute the ratio
    double ratio = mRadius / otherPulley->mRadius;

    // Set the input ratio on the driven pulley
    otherPulley->SetInputRatio(ratio);

    // Add the other pulley as a sink to this pulley’s source
    mSource.AddSink(otherPulley);

    // Set this pulley’s child
    mChildPulley = otherPulley;
}

/**
 * Set the visual lines on the pulley hub
 * @param lineColor The line color
 * @param lineWidth The width of the lines
 * @param lineCountDivisor The divisor used to determine the number of lines
 */
void Pulley::SetLines(const wxColour& lineColor, int lineWidth, double lineCountDivisor)
{
    int numLines = (mRadius / lineCountDivisor);
    mCylinder.SetLines(lineColor, lineWidth, numLines);
}

/**
 * Draw this pulley using the given graphics context
 * @param graphics The graphics context
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Save the current graphics state and translate
    graphics->PushState();
    graphics->Translate(mPositionX, mPositionY);

    double diameter = mRadius * 2.0;
    double hubWidth = PulleyHubWidth;
    double beltDepth = PulleyBeltDepth;

    // Calculate the number of lines for the pulley hub
    int hubLines = (diameter / PulleyHubLineCountDiviser);

    // --- Draw left hub ---
    mCylinder.SetColour(PulleyColor);
    mCylinder.SetLines(PulleyHubLineColor, PulleyHubLineWidth, hubLines);
    mCylinder.SetSize(diameter, hubWidth);
    mCylinder.SetOffset(mRotation);
    mCylinder.Draw(graphics, -diameter / 2.0, 0, mRotation);

    // --- Draw body ---
    // Make the body shorter from top and bottom by reducing its diameter
    double bodyDiameter = diameter * 0.95; // For example, 80% of original height
    mCylinder.SetColour(PulleyColor);
    mCylinder.SetLines(PulleyHubLineColor, PulleyHubLineWidth, 0);
    mCylinder.SetSize(bodyDiameter, 3 * hubWidth);
    mCylinder.SetOffset(mRotation);
    mCylinder.Draw(graphics, -diameter / 2.0 + hubWidth, 0, mRotation);

    // --- Draw right hub ---
    mCylinder.SetColour(PulleyColor);
    mCylinder.SetLines(PulleyHubLineColor, PulleyHubLineWidth, hubLines);
    mCylinder.SetSize(diameter, hubWidth);
    mCylinder.SetOffset(mRotation);
    mCylinder.Draw(graphics, -diameter / 2.0 + (3 * hubWidth) + hubWidth, 0, mRotation);

    if (mChildPulley)
    {
        double beltWidth = hubWidth*3;
        double beltLength = std::abs(mPositionY - mChildPulley->mPositionY) + mRadius + mChildPulley->mRadius;

        if (mPositionY < mChildPulley->mPositionY)
        {
            graphics->PushState();
            graphics->SetBrush(wxBrush(BeltColor));
            graphics->SetPen(wxPen(BeltColor));
            graphics->DrawRectangle(-diameter / 2.0 + (hubWidth), -mRadius, beltWidth, beltLength);
            graphics->PopState();
        } else if (mPositionY > mChildPulley->mPositionY)
        {
            graphics->PushState();
            graphics->SetBrush(wxBrush(BeltColor));
            graphics->SetPen(wxPen(BeltColor));
            graphics->DrawRectangle(-diameter / 2.0 + (hubWidth), (mChildPulley->mPositionY - mPositionY) - mChildPulley->mRadius, beltWidth, beltLength);
            graphics->PopState();
        }

    }

    // Restore graphics state
    graphics->PopState();
}

