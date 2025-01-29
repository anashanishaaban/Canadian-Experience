/**
 * @file MachineAdapter.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H

#include <memory>
#include <machine-api.h>
#include "Drawable.h"

/**
 * Adapter class for integrating IMachineSystem into the Canadian Experience system.
 */
class MachineAdapter : public Drawable
{
private:
    /// Encapsulated machine system
    std::shared_ptr<IMachineSystem> mMachine;

    /// Machine number
    int mMachineNumber = 1;

    /// Start time in seconds
    double mStartTime = 0.0;

    /// Frame rate for animation
    double mFrameRate = 30.0;

    Timeline* mTimeline;

public:
    /**
     * Constructor
     * @param name The name of the drawable
     * @param machine The machine system to adapt
     */
    MachineAdapter(const std::wstring& name, std::shared_ptr<IMachineSystem> machine, Timeline* timeline);

    /// Draw the machine
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /// Set the timeline for this machine
    virtual void SetTimeline(Timeline* timeline) override;

    /// Set a keyframe based on the current state
    virtual void SetKeyframe() override{}

    /// Get a keyframe and update the state
    virtual void GetKeyframe() override{}

    virtual bool HitTest(wxPoint pos) override{}

    /// Save machine details to XML
    virtual wxXmlNode* XmlSave(wxXmlNode* node);

    /// Load machine details from XML
    virtual void XmlLoad(wxXmlNode* node);

    /// Show the MachineDialog for selecting machine number
    void ShowMachineDialog(wxWindow* parent);

    /**
     * Set the start time for the machine
     * @param time Start time in seconds
     */
    void SetStartTime(double time) { mStartTime = time; }

    /**
     * Get the start time for the machine
     * @return Start time in seconds
     */
    double GetStartTime() const { return mStartTime; }

    /// Set the machine number
    void SetMachineNumber(int number);

    /**
     * Get the machine number
     * @return Machine number
     */
    int GetMachineNumber() const { return mMachineNumber; }

    /// Set the frame rate
    void SetFrameRate(double frameRate) { mFrameRate = frameRate; }
    void SetMachineFrame(int frame);

    void OpenMachineDialog(wxWindow* parent);


};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H
