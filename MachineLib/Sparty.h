/**
 * @file Sparty.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SPARTY_H
#define CANADIANEXPERIENCE_MACHINELIB_SPARTY_H

#include <wx/wx.h>
#include <wx/graphics.h>
#include "Component.h"
#include "Box.h"

/**
 * Sparty class that represents the Sparty component in the machine system.
 */
class Sparty : public Component
{
private:
    const double mSize;               ///< Size of Sparty
    const double mCompressedLength;   ///< Compressed length of the spring
    double mExtendedLength;     ///< Extended length of the spring
    double mCurrentLength;      ///< Current length of the spring
    wxPoint mPosition;          ///< Position of Sparty
    std::shared_ptr<wxBitmap> mSpartyImage; ///< Sparty image
    double mPopupTime = 0.0;    ///< Time since Sparty started popping up
    bool mIsPoppingUp = false;  ///< True if Sparty is popping up
    std::shared_ptr<Box> mBox;  ///< Box component

    const double PopupSpeed = 70.0;    ///< Multiplier for pop-up speed




public:
    Sparty(const std::wstring &imagePath, double size, double compressedLength);

    void SetPosition(const wxPoint &position);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override;
    void TriggerPopUp();
    void DrawSpring(std::shared_ptr<wxGraphicsContext> graphics,
                    int x,
                    int y,
                    double length,
                    double width,
                    int numLinks);


    void Reset();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_SPARTY_H
