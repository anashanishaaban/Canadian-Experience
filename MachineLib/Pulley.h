/**
 * @file Pulley.h
 * @author Anas Shaaban
 *
 * A class that represents a Pulley which is both a RotationSource and an IRotationSink.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

#include <memory>
#include <vector>
#include <wx/graphics.h>
#include "IRotationSink.h"
#include "RotationSource.h"
#include "Cylinder.h"
#include "Component.h"

/**
 * Pulley class that represents a pulley in the machine system.
 */
class Pulley : public Component, public IRotationSink, public RotationSource
{
public:
    /**
     * Constructor
     * @param radius Radius of the pulley
     * @param initialRotation Initial rotation (speed or angle) of this pulley
     * @param positionX X position where the pulley is drawn
     * @param positionY Y position where the pulley is drawn
     */
    Pulley(double radius, double initialRotation, double positionX, double positionY);

    /// Destructor
    virtual ~Pulley() = default;

    /// IRotationSink interface implementation
    void ReceiveRotation(double rotation) override;

    /**
     * Connect this pulley to another pulley via a belt.
     * This pulley acts as the driving pulley, and the other as the driven pulley.
     * @param otherPulley The pulley to connect to
     */
    void ConnectToPulley(std::shared_ptr<Pulley> otherPulley);

    /**
     * Get this pulley’s rotation source.
     * @return Pointer to the rotation source
     */
    RotationSource* GetSource()
    {
        return &mSource;
    }

    /**
     * Set the visual lines on the pulley hub
     * @param lineColor The line color
     * @param lineWidth The width of the lines
     * @param lineCountDivisor The divisor used to determine the number of lines
     */
    void SetLines(const wxColour& lineColor, int lineWidth, double lineCountDivisor);

    /**
     * Draw this pulley using the given graphics context
     * @param graphics The graphics context
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Set the input ratio for this pulley. This ratio is used to scale the incoming rotation.
     * For example, if this pulley should rotate half as fast as the source, the ratio would be 0.5.
     * @param ratio The ratio to set
     */
    void SetInputRatio(double ratio) { mInputRatio = ratio; }

    void Update(double elapsedTime) override{}


private:
    double mRadius = 0.0;        ///< Radius of the pulley
    double mRotation = 0.0;      ///< Current rotation speed/angle of the pulley
    double mPositionX = 0.0;     ///< X position of the pulley center
    double mPositionY = 0.0;     ///< Y position of the pulley center
    double mInputRatio = 1.0;    ///< The ratio to apply to incoming rotation (default 1.0 means no change)
    double mDiameter = 0.0;      ///< Diameter of the pulley
    double mLeftHub = 0.0;       ///< Left hub of the pulley
    double mRightHub = 0.0;      ///< Right hub of the pulley
    double mBody = 0.0;
    std::vector<std::shared_ptr<Pulley>> mConnectedPulleys;

    RotationSource mSource;      ///< Rotation source for this pulley
    cse335::Cylinder mCylinder;          ///< Cylinder drawing object for visualizatio

    std::shared_ptr<Pulley> mChildPulley = nullptr;



};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
