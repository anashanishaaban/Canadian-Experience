/**
 * @file Shaft.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include "Shaft.h"
#include "Const.h"

/**
 * Constructor
 */
void Shaft::SetSize(double radius, double height)
{
    mRadius = radius;
    mHeight = height;
}

/**
 * Draw the shaft
 * @param graphics The graphics context to draw on
 */
void Shaft::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Translate to the shaft's position
    graphics->Translate(mPosition.x, mPosition.y);

    // Draw the cylinder (shaft) with adjustable size
    mCylinder.SetSize(mRadius, mHeight); // Use member variables for size
    mCylinder.Draw(graphics, 0, 0, mRotation);  // Draw with the current rotation

    graphics->PopState();
}