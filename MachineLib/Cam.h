/**
 * @file Cam.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CAM_H
#define CANADIANEXPERIENCE_MACHINELIB_CAM_H


#include <wx/graphics.h>
#include "IRotationSink.h"
#include "Component.h"
#include "RotationSource.h"
#include "Key.h"

/**
 * Cam component for the machine
 */
class Cam : public IRotationSink, public Component, public RotationSource
{
private:
    /// The hole angle
    double mHoleAngle;
    /// Angle of the hole in radians
    double mHoleSize; // Size of the hole

    /// The rotation
    double mRotation = 0.0;
    /// Position of the cam
    wxPoint mPosition;       // Position of the cam
    /// Pointer to the key that interacts with the cam
    std::shared_ptr<Key> mKey = nullptr;
    /// Initial rotation of the cam
    double mInitialRotation = 0.0; // Initial rotation of the cam

    /// initial position of the cam
    wxPoint mInitialPosition; // Initial position of the cam

public:
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsedTime) override;
    void SetRotation(double rotation);


    /**
     * Set the position of the cam
     * @param position Position of the cam
     */
    void SetPosition(const wxPoint& position) {
        mPosition = position;        // Update current position
        mInitialPosition = position; // Store initial position
    }
    bool IsHoleUnderKey() const;

    Cam(double holeAngle = 0);

    /**
     * Set the rotation of the cam.
     * @param rotation Rotation in radians.
     */
    void ReceiveRotation(double rotation) override {
        mRotation = rotation;
        // Add logic to handle the rotation, such as updating the cam's visual state
    }

    void SetKey(std::shared_ptr<Key> key);

    void Reset();
    void SetFrame(int frame);
    int mRotationPerFrame;
    void SetInitialPosition(wxPoint position);
};


#endif //CANADIANEXPERIENCE_MACHINELIB_CAM_H
