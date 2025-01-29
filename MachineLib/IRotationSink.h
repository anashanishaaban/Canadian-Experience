/**
 * @file IRotationSink.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H

/**
 * Interface for a class that receives rotation
 */
class IRotationSink {
public:
    /// Virtual destructor for proper cleanup in case of polymorphic use
    virtual ~IRotationSink() = default;

    /// Pure virtual function that will be implemented by any class that receives rotation
    virtual void ReceiveRotation(double rotation) = 0;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
