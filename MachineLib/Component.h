/**
 * @file Component.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

#include <wx/graphics.h>
#include <iostream>

/**
 * Base class for components in a machine.
 */
class Component
{
private:
    /// Position of the component
    wxPoint mPosition;

    /// Directory for loading images
    std::wstring mImageDirectory;

    double mTime = 0.0;

    std::wstring mName;

public:
    /// Constructor
    Component() = default;

    /// Destructor
    virtual ~Component() = default;

    /// Set the position of the component
    void SetPosition(wxPoint position);

    /// Get the position of the component
    wxPoint GetPosition() const;

    /// Set the image directory for loading assets
    void SetImageDirectory(const std::wstring& directory);

    /// Get the image directory
    std::wstring GetImageDirectory() const;

    /// Draw the component (to be overridden by derived classes)
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    virtual void Update(double elapsedTime) = 0;

    void SetLocation(wxPoint location) { mPosition = location; }

    /**
     * Draw the component
     * @param graphics Graphics context to draw on
     */
    virtual void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) {}

    /***
     *
     * Set Time
     * @param time Time to set
     */
    void SetTime(double time) { mTime = time; }

    void Reset();

    /**
     * Get the root position of the machine
     * @return location x,y in pixels as a point
     */
    virtual bool ShouldBeDrawnBehind() const { return false; } // Default to not behind

    /**
     * Get the root position of the machine
     * @return location x,y in pixels as a point
     */
    virtual bool IsCrank() const { return false; } // Default to not being a crank

    /**
     * Get the root position of the machine
     * @return location x,y in pixels as a point
     */
    virtual bool IsShaft() const { return false; } // Default to not being a shaft

    /**
     * Get the root position of the machine
     * @return location x,y in pixels as a point
     */
    void SetName(const std::wstring& name) { mName = name; }

    /**
     * Get the root position of the machine
     * @return location x,y in pixels as a point
     */
    std::wstring GetName() const { return mName; }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
