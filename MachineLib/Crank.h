/**
 * @file Crank.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CRANK_H
#define CANADIANEXPERIENCE_MACHINELIB_CRANK_H

#include "Component.h"
#include "Cylinder.h"
#include "Const.h"
#include "RotationSource.h"
#include "Shaft.h"

/**
 * Crank component for the machine
 */
class Crank : public Component, RotationSource {
private:
    // Dimensions and colors
    int CrankWidth = 10;
    int CrankLength = 50;
    int CrankDepth = 20;
    int HandleDiameter = 7;
    int HandleLength = 40;
    int HandleStartX = -10;

    wxColour CrankColor = wxColour(220, 220, 220);
    wxColour CrankHandleLineColor = wxColour(0, 0, 0);

    // Handle (a cylinder)
    cse335::Cylinder mHandle;

    // Position of the crank
    wxPoint mPosition;

    /// Rotation angle (in radians)
    double mRotation = 0.0;

    std::vector<std::shared_ptr<IRotationSink>> mSinks;  // List of sinks


    /// Speed of rotation (radians per second)

    double mRotationSpeed = 2; // One full rotation per second

    wxBrush mCrankBrush;
    wxPen mCrankBorderPen;

    RotationSource mSource;

    std::shared_ptr<Shaft> mShaft;

public:

    /**
     * Draw the crank
     * @param graphics Graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Set the position of the crank
     * @param position Position of the crank
     */
    void SetPosition(const wxPoint& position) { mPosition = position; }

    void Update(double elapsedTime) override;

    /// Reset the crank (required by Component)
    void Reset() ;

    /// Set the rotation speed
    void SetRotationSpeed(double speed) { mRotationSpeed = speed; }

    bool IsCrank() const override
    {
        return true; // This is a crank, so it should be drawn after the background but before the foreground
    }

    Crank(Shaft* shaft) : mShaft(shaft){
        // Initialize the crank handle
        mHandle.SetSize(HandleDiameter, HandleLength);
        mHandle.SetColour(CrankColor);
        mHandle.SetLines(CrankHandleLineColor, 1, 4);

        // Initialize rotation variables
        mRotation = 0.0;
    }

    /// Getter for the rotation source object
    RotationSource* GetSource() { return &mSource; }

    void UpdateRotation(double delta) { mRotation += delta; }


    /// Function to update the crank's rotation source
    void UpdateSourceRotation(double delta) { mSource.UpdateRotation(delta); }

    void AddSink(std::shared_ptr<IRotationSink> sink);

};


#endif //CANADIANEXPERIENCE_MACHINELIB_CRANK_H
