/**
 * @file MachineSystem.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H

#include "IMachineSystem.h"
#include "Machine.h"
#include <memory>
#include <wx/graphics.h>
#include "Box.h"
#include "Sparty.h"
#include "Crank.h"
#include "Shaft.h"
#include "Pulley.h"
#include "Key.h"
#include "KeyDropResponder.h"
#include "Cam.h"

/**
 * A custom implementation of the Machine System.
 */
class MachineSystem : public IMachineSystem
{
private:
    /// The machine managed by this system
    std::shared_ptr<Machine> mMachine;

    /// The location of the machine
    wxPoint mLocation;

    /// Frame rate for the animation
    double mFrameRate = 30.0;

    /// Current frame of the animation
    int mFrame = 0;

    /// The machine number
    std::wstring mResourcesDir;

    /// The box
    std::shared_ptr<Box> mBox;

    /// The sparty
    std::shared_ptr<Sparty> mSparty;

    /// The crank
    std::shared_ptr<Crank> mCrank;

    /// The shaft
    std::shared_ptr<Shaft> mShaft;

    /// The pulleys
    std::shared_ptr<Pulley> mPulley1;


    /// The pulleys
    std::shared_ptr<Pulley> mPulley2;

    /// The pulleys
    std::shared_ptr<Pulley> mPulley3;

    /// The pulleys
    std::shared_ptr<Pulley> mPulley4;

    /// The key
    std::shared_ptr<Key> mKey;

    /// The cam
    std::shared_ptr<Cam> mCam;

    /// The last frame
    int mLastFrame = -1;

    /// The flag
    double mTime = 0.0;

    /// The flag
    bool mStarted = false;



public:
    /// Constructor
    MachineSystem(const std::wstring& resourcesDir);

    /// Destructor
    virtual ~MachineSystem() = default;

    // Methods inherited from IMachineSystem


    virtual void SetLocation(wxPoint location) override;
    virtual wxPoint GetLocation() override;
    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    virtual void SetMachineFrame(int frame) override;
    virtual void SetFrameRate(double rate) override;
    virtual void ChooseMachine(int machine) override;
    virtual int GetMachineNumber() override;
    virtual double GetMachineTime() override;
    virtual void SetFlag(int flag) override;

    void SetResourceDirectory(const std::wstring& resourcesDir);

    void CreateMachine(int machine);

    void SetTime(double time);

    /**
     * Get the current time
     * @return The current time
     */
    double GetTime() const { return mTime; } // Get the current time

    void Play();

    void Update(double elapsedTime);

    void Reset();

    void ReinitializeMachine();
};


#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
