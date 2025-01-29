/**
 * @file Key.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_KEY_H
#define CANADIANEXPERIENCE_MACHINELIB_KEY_H

#include <wx/graphics.h>
#include <memory>
#include <vector>
#include "Polygon.h"
#include <wx/wx.h>
#include "Component.h"
#include "KeyDropResponder.h"

/**
 * Key component for the machine
 */
class Key : public Component, public KeyDropResponder
{
private:
    bool mIsDropped = false; // Is the key dropped into the cam's hole?
    wxPoint mPosition;       // Position of the key
    wxPoint mInitialPosition; // Initial position of the key
    std::vector<KeyDropResponder*> mResponders; // Responders for the key drop

    cse335::Polygon mKeyPolygon; // Polygon representation of the key

public:

    Key(const std::wstring& resourcesDir);


        /**
         * Draw the key.
         * @param graphics The graphics context to draw on.
         */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Trigger the key to drop.
     */
    void Trigger();

    /**
     * Add a responder to handle key drops.
     * @param responder The responder to add.
     */
    void AddKeyDropResponder(KeyDropResponder* responder);

    /**
     * Update the key's state.
     * @param elapsedTime Time elapsed since the last update.
     */
    void Update(double elapsedTime) override;

    void OnKeyDropped() override;

    void SetPosition(wxPoint position) {
        mPosition = position;
        mInitialPosition = position; // Update the initial position
    }
    wxPoint GetPosition() const { return mPosition; }

    void Reset();

    bool IsDropped() const { return mIsDropped; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_KEY_H
