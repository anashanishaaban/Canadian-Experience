/**
 * @file Box.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BOX_H
#define CANADIANEXPERIENCE_MACHINELIB_BOX_H

#include <wx/wx.h>
#include <wx/graphics.h>
#include <memory>
#include "Component.h"
#include "Polygon.h"

/**
 * Box component for the machine
 */
class Box : public Component
{
private:

    /// The background polygon
    cse335::Polygon mBackgroundPolygon;

    /// The foreground polygon
    std::shared_ptr<wxBitmap> mBackground;

    /// The foreground polygon
    std::shared_ptr<wxBitmap> mForeground;

    /// The lid polygon
    std::shared_ptr<wxBitmap> mLid;

    /// The lid polygon
    double mLidAngle;

    /// The lid polygon
    double mX;

    /// The lid polygon
    double mY;

    /// The box size
    double mBoxSize;

    /// The lid size
    double mLidSize;

    /// If the lid is opening
    bool mLidOpening;

    /// If the lid is closing
    bool mLidClosing;

    /// The lid speed
    double mLidSpeed;

    /// The position of the box
    wxPoint mPosition;

    /// The directory containing the images
    std::wstring mImageDirectory;




public:
    //Constructor
    Box(const std::wstring& imagesDir, int boxSize, int lidSize);

    /**
     * Draw the box
     * @param graphics Graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Handle a key press
     * @param event The key event
     */
    void OnKeyDown(wxKeyEvent& event);

    /**
     * Update the state of the box (e.g., opening the lid)
     * @param elapsedTime Time passed since the last update
     */
    void Update(double elapsedTime) override;

    /**
     * Trigger the lid to open
     */
    void TriggerLidOpen();

    /**
     * Trigger the lid to close
     */
    void TriggerLidClose();

    void SetPosition(const wxPoint& position)
    {
        // Offset the position so the box appears above the given coordinates
        mPosition.x = position.x;
        mPosition.y = position.y - mBoxSize; // Shift up by the box's height
    }

    void DrawForeground(std::shared_ptr<wxGraphicsContext>) override;
    void Reset();

    bool ShouldBeDrawnBehind() const override
    {
        return true; // Box background and lid are drawn behind the crank and foreground
    }

    bool IsLidOpen() const { return mLidAngle > 0; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_BOX_H
