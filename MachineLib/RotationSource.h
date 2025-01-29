/**
 * @file RotationSource.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H

#include <vector>
#include <memory>
#include "IRotationSink.h"

/**
 * Rotation source class that provides a rotation value and notifies sinks about changes.
 */
class RotationSource {
public:
    RotationSource(double initialRotation = 0.0)
        : mRotation(initialRotation) {}

    /// Getter for the current rotation value
    double GetRotation() const { return mRotation; }

    /// Setter for the current rotation value
   void SetRotation(double rotation) { mRotation = rotation; }

    /// Function to update the rotation (e.g., apply some change)
    void UpdateRotation(double delta) { mRotation += delta; }

    /// Add a sink to the source
    void AddSink(std::shared_ptr<IRotationSink> sink) {
        mSinks.push_back(sink);
    }

    /// Notify all sinks about the current rotation
    void NotifySinks() {
        for (auto& sink : mSinks) {
            sink->ReceiveRotation(mRotation);
        }
    }

private:
    double mRotation;  // Current rotation value
    std::vector<std::shared_ptr<IRotationSink>> mSinks;  // List of sinks
};


#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
