/**
 * @file Crank.cpp
 * @author Anas
 */

#include "pch.h"

#include <wx/brush.h>
#include <wx/pen.h>
#include <cmath>
#include "Crank.h"
#include "Const.h"

/**
 * Constructor
 * @param positionX X position where the crank is drawn
 * @param positionY Y position where the crank is drawn
 */
void Crank::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Translate to the crank's position (the base pivot point)
    graphics->Translate(mPosition.x, mPosition.y);

    // Base constant height of 20 pixels
    const double BaseHeight = 20.0;

    // Calculate the dynamic height based on the current rotation angle
    double dynamicHeight = 55 * std::cos(mRotation) - 5.0;

    wxPen crankBorderPen(CrankHandleLineColor, 1, wxPENSTYLE_SOLID);
    graphics->SetPen(crankBorderPen);

    // Set up the brush for filling the crank rectangle
    wxBrush crankBrush(CrankColor);
    graphics->SetBrush(crankBrush);

    // Determine the y-position and height
    double rectX = -CrankWidth / 2.0; // Center the rectangle horizontally
    double rectY;
    double totalLength;

    if (dynamicHeight >= 0)
    {
        // Extending upwards
        rectY = -BaseHeight; // Start from the base height going up
        totalLength = BaseHeight + dynamicHeight;
    }
    else
    {
        // Extending downwards
        rectY = -BaseHeight + dynamicHeight;
        totalLength = BaseHeight - dynamicHeight;
    }

    double handleX = -10; // Handle X remains fixed relative to the crank
    double handleY = dynamicHeight-10; // Handle moves with the crank

    double handleRotationTurns = mRotation / (2.0 * Const::PI);
    mHandle.Draw(graphics, handleX, handleY, handleRotationTurns);

    // Draw the crank rectangle with base height and dynamic addition
    graphics->DrawRectangle(rectX, rectY, CrankWidth, totalLength);

    graphics->PopState();
}

/**
 * Update the crank rotation based on elapsed time
 * @param elapsedTime Time elapsed since the last update
 */
void Crank::Update(double elapsedTime)
{
    // Ensure elapsed time is reasonable
    if (elapsedTime > 0.1) {
        elapsedTime = 0.1; // Cap elapsed time to avoid extreme updates
    }

    // Update the rotation with speed scaled by elapsed time
    mRotation += mRotationSpeed * elapsedTime;


    // Update the source's rotation
    mSource.SetRotation(mRotation);

    // Notify all sinks connected to the source
    mSource.NotifySinks();
}



void Crank::Reset()
{
    // Reset rotation angle to 0
    mRotation = 0.0;
}

void Crank::AddSink(std::shared_ptr<IRotationSink> sink) {
    mSinks.push_back(sink);
}