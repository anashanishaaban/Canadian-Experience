/**
 * @file Shaft.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SHAFT_H
#define CANADIANEXPERIENCE_MACHINELIB_SHAFT_H

#include "Component.h"
#include "Cylinder.h"
#include "Const.h"
#include "IRotationSink.h"
#include "RotationSource.h"

/// The color to draw the shaft
const wxColour ShaftColor = wxColour(220, 220, 220);

/// The color to draw the lines on the shaft
/// First parameter to Cylinder::SetLines
const wxColour ShaftLineColor = wxColour(100, 100, 100);

/// The width to draw the lines on the shaft
/// Second parameter to Cylinder::SetLines
const int ShaftLinesWidth = 1;

/// The number of lines to draw on the shaft
/// Third parameter to Cylinder::SetLines
const int ShaftNumLines = 4;

/**
 * Shaft component for the machine
 */
class Shaft : public Component, public IRotationSink, public RotationSource
 {
private:
    // Cylinder representing the shaft
    cse335::Cylinder mCylinder;

    // Shaft rotation angle (in radians), initialized to 0 for now
    double mRotation = 0.0;

    // Position of the shaft
    wxPoint mPosition;

    // Rotation source for the shaft
    RotationSource mSource;

    /// Radius and height of the shaft
    double mRadius;

    /// Height of the shaft
    double mHeight;

    /// Gear ratio for the shaft
    double mGearRatio = 10;

public:
    /**
     * Constructor
     */
    Shaft() : mRotation(0.0){
        mCylinder.SetColour(ShaftColor);
        mCylinder.SetLines(ShaftLineColor, ShaftLinesWidth, ShaftNumLines);
    }

    /**
     * Draw the shaft (with no rotation for now)
     * @param graphics Graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Set the position of the shaft
     * @param position Position of the shaft
     */
    void SetPosition(const wxPoint& position) { mPosition = position; }

    /**
     * Set the rotation of the shaft (received from the Crank class)
     * @param rotation Rotation angle in radians
     */
    void SetRotation(double rotation) { mRotation = rotation; }

    // You can implement an Update function here if needed in the future
    // to advance the rotation based on time
    void Update(double elapsedTime) override {}

    bool ShouldBeDrawnBehind() const override
    {
        return false; // Box background and lid are drawn behind the crank and foreground
    }

    bool IsShaft() const override
    {
        return true; // This is a shaft, so it should be drawn after the background but before the foreground
    }

    void Reset() {}

    /**
     * Receive the rotation from the source
     * @param rotation Rotation angle in radians
     */
    void ReceiveRotation(double rotation) override {
        // Apply gear ratio to the rotation
        mRotation = rotation * mGearRatio;
        mSource.SetRotation(mRotation);
        mSource.NotifySinks();
    }

    /**
     * Get the current rotation of the shaft
     * @return Rotation angle in radians
     */
    double GetRotation() const { return mRotation; }

    /**
     * Get the rotation source for the shaft
     * @return Pointer to the rotation source
     */
    RotationSource* GetSource() { return &mSource; }

    void SetSize(double radius, double height);

    /**
     * Set the gear ratio for the shaft
     * @param gearRatio Gear ratio to set
     */
    void SetGearRatio(double gearRatio) {
        mGearRatio = gearRatio;
    }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_SHAFT_H
