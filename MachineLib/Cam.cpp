/**
 * @file Cam.cpp
 * @author Anas Shaaban
 */

#include "pch.h"

#include "Cam.h"
#include <wx/wx.h>

/// Width of the cam on the screen in pixels
const double CamWidth = 17;

/// Cam height (diameter)
const double CamDiameter = 65;

/// How big is the hole in the cam?
const double HoleSize = 8;

/// Initial cam
const double InitialCamPosition = 0;


/// Color constants
const wxColour OutlineColor = *wxBLACK;

/// The color white
const wxColour FillColor = *wxWHITE;

/// The color black
const wxColour LineColor = *wxBLACK;

/**
 * Constructor
 * @param holeAngle Angle of the hole in radians
 */
Cam::Cam(double holeAngle)
    : mHoleAngle(holeAngle), mInitialRotation(0.0), mInitialPosition(wxPoint(0, 0))
{
    // Initial state is set in the initializer list
}
/**
 * Draw the cam.
 * @param graphics The graphics context to draw on.
 */
void Cam::Draw(std::shared_ptr<wxGraphicsContext> graphics) {

    graphics->PushState();
    graphics->Translate(mPosition.x, mPosition.y);

    // Draw the cam body with an outline
    graphics->SetBrush(wxBrush(FillColor));
    graphics->SetPen(wxPen(OutlineColor, 1));
    graphics->DrawRectangle(-CamWidth / 2, -CamDiameter / 2, CamWidth, CamDiameter);

    // Calculate the vertical position of the hole based on rotation
    double holeY = -CamDiameter / 2 + HoleSize / 2 +
        (CamDiameter - HoleSize) * (1 - ((mRotation))) * 0.9; // Add scaling factor (0.9)

    // Adjust holeY to move higher up the cam
    holeY -= -5; // Move the hole upward by 5 pixels

    // Offset for stopping slightly higher
    double topStopOffset = -1; // Stop slightly higher by 3 pixels

    // Clamp holeY to stop slightly higher than the top of the cam
    if (holeY < (-CamDiameter / 2 + topStopOffset)) {
        holeY = -CamDiameter / 2 + topStopOffset; // Stop slightly above the top
    }

    // Calculate squished height of the hole based on its position
    double squishFactor = fabs(holeY / (CamDiameter / 2)); // Closer to 1 at the ends, 0 in the middle
    double holeHeight = HoleSize * (1 - 0.5 * squishFactor); // Adjust squish factor as needed
    double holeWidth = HoleSize; // Width remains constant

    // Draw the squished hole
    graphics->SetBrush(*wxBLACK_BRUSH);
    graphics->DrawEllipse(-holeWidth / 2, holeY, holeWidth, holeHeight);

    graphics->PopState();
}


/**
 * Update the cam's state.
 * @param elapsedTime Time elapsed since the last update.
 */
void Cam::Update(double elapsedTime)
{
    // Move forward or backward based on elapsedTime
    mRotation += elapsedTime * 0.0005; // Rotate at 0.5 radians per second

    // Check if the hole is under the key
    if (IsHoleUnderKey() && mKey) {
        mKey->Trigger();
    }
}

/**
 * Set the frame of the cam.
 * @param frame Frame number.
 */
void Cam::SetFrame(int frame)
{
    if (frame == 0)
    {
        Reset();
        return;
    }

    // Compute rotation deterministically based on frame
    mRotation = mInitialRotation + frame * mRotationPerFrame;

    // If the hole aligns with the key, trigger the key
    if (IsHoleUnderKey() && mKey)
    {
        mKey->Trigger();
    }
}


/**
 * Set the rotation of the cam.
 * @param rotation Rotation in radians.
 */
void Cam::SetRotation(double rotation) {
    mRotation = rotation;
}


/**
 * Check if the hole is under the key.
 * @return True if the hole is under the key, false otherwise.
 */
bool Cam::IsHoleUnderKey() const {
    double currentAngle = fmod(mRotation, 2 * M_PI);
    return fabs(currentAngle - mHoleAngle) < 0.28; // Threshold for alignment
}

/**
 * Set the key that interacts with the cam.
 * @param key Key to set.
 */
void Cam::SetKey(std::shared_ptr<Key> key) {
    mKey = key;
}

/**
 * Reset the cam to its initial state.
 */
void Cam::Reset()
{
    mRotation = InitialCamPosition;  // Reset to the initial rotation}
}

/**
 * Set the initial position of the cam.
 * @param position Initial position to set.
 */
void Cam::SetInitialPosition(wxPoint position) {
    mInitialPosition = position;
    mPosition = position; // Also set the current position
}
