/**
 * @file Key.cpp
 * @author Anas Shaaban
 */

#include "pch.h"

#include "Key.h"
#include <string>
using namespace std;

const double KeyDropSpeedMultiplier = 5.0; // Multiplier to increase drop speed

/// The key image
const std::wstring KeyImage = L"/key.png";

/// The key image size
const int KeyImageSize = 20;

/// The amount the key drops into the hole
const int KeyDrop = 10;

const int HoleDepth = 10;

/**
 * Constructor
 * @param resourcesDir The resources directory
 */
Key::Key(const std::wstring& resourcesDir) : mInitialPosition(0, 0) {
    mKeyPolygon.SetImage(resourcesDir + L"/images/key.png");
    mKeyPolygon.Rectangle(-KeyImageSize / 2, 0, KeyImageSize, KeyImageSize);

    // Initialize the position
    mInitialPosition = mPosition;
}



/**
 * Draw the key.
 * @param graphics The graphics context to draw on.
 */
void Key::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    mKeyPolygon.DrawPolygon(graphics, mPosition.x, mPosition.y);
}

/**
 * Trigger the key to drop.
 */
void Key::Trigger() {
    if (!mIsDropped) { // Only trigger the drop once
        mIsDropped = true;
    }
}

/**
 * Add a responder to handle key drops.
 * @param responder The responder to add.
 */
void Key::AddKeyDropResponder(KeyDropResponder* responder) {
    mResponders.push_back(responder);
}

/**
 * Update the key's state.
 * @param elapsedTime Time elapsed since the last update.
 */
void Key::Update(double elapsedTime) {
    if (mIsDropped && mPosition.y < mInitialPosition.y + HoleDepth) {

        // Move the key down faster using the speed multiplier
        mPosition.y += KeyDrop * KeyDropSpeedMultiplier * elapsedTime;

        // Clamp the key's position to not go beyond the hole depth
        if (mPosition.y >= mInitialPosition.y + HoleDepth) {
            mPosition.y = mInitialPosition.y + HoleDepth;
        }
    }
}

/**
 * Reset the key to its initial state.
 */
void Key::OnKeyDropped() {
    // Logic for what happens when the key is dropped
    mIsDropped = true;
    // Notify any other responders (if necessary)
    for (auto responder : mResponders) {
        responder->OnKeyDropped();
    }
}

/**
 * Reset the key to its initial state.
 */
void Key::Reset() {
    mIsDropped = false; // Reset drop state
    mPosition = mInitialPosition; // Reset to the initial position
}