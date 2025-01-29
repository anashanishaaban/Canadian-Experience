/**
 * @file MachineSystem.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include "MachineSystem.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"
#include "Crank.h"
#include "Shaft.h"
#include "Cam.h"
#include "Key.h"
#include "Box.h"
#include "Sparty.h"

/**
 * Constructor
 * @param resourcesDir The resources directory
 */
MachineSystem::MachineSystem(const std::wstring& resourcesDir)
    : mResourcesDir(resourcesDir)
{
    Machine1Factory factory(resourcesDir);
    mMachine = factory.Create();

    mBox = factory.GetBox();
    mSparty = factory.GetSparty();
    mCam = factory.GetCam();
    mKey = factory.GetKey();
    mCrank = factory.GetCrank();
    mShaft = factory.GetShaft();
    mPulley1 = factory.GetPulley1();
    mPulley2 = factory.GetPulley2();
    mPulley3 = factory.GetPulley3();
    mPulley4 = factory.GetPulley4();

}

/**
 * Set the position for the root of the machine
 * @param location X,Y location in pixels
 */
void MachineSystem::SetLocation(wxPoint location)
{
    mLocation = location;
    mMachine->SetLocation(location);
}

/**
 * Get the root position of the machine
 * @return location x,y in pixels as a point
 */
wxPoint MachineSystem::GetLocation()
{
    return mLocation;
}

/**
 * Draw the machine
 * @param graphics Graphics context to draw on
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mMachine)
    {
        mMachine->Draw(graphics);

    }
}

/**
 * Set the current machine animation frame
 * @param frame Frame number
 */
void MachineSystem::SetMachineFrame(int frame)
{
    if (frame < mFrame)
    {
        mFrame = 0;
        Reset();
    }

    while (mFrame < frame) {
        mFrame++;
        mTime = mFrame / mFrameRate;
        mMachine->Update(1.0 / mFrameRate);
        mMachine->SetTime(mTime);
    }


    // Check if the key is in the hole
    if (mKey && mKey->IsDropped() && mBox && !mBox->IsLidOpen()) {
        if (mSparty) {
            mSparty->TriggerPopUp();
        }
        mBox->TriggerLidOpen();
    }

    double time = (frame) / mFrameRate;
    SetTime(time);
}

/**
 * Set the frame rate for the animation
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
}

/**
 * Choose the machine to display
 * @param machine Machine number
 */
void MachineSystem::ChooseMachine(int machine)
{
    CreateMachine(machine); // Create the selected machine
    if (mMachine)
    {
        mMachine->SetMachineNumber(machine);
    }
}

/**
 * Get the machine number
 * @return Machine number
 */
int MachineSystem::GetMachineNumber()
{
    return mMachine ? mMachine->GetMachineNumber() : 0;
}

/**
 * Get the machine time
 * @return Machine time
 */
double MachineSystem::GetMachineTime()
{
    return mTime;
}

/**
 * Set the resources directory
 * @param resourcesDir Resources directory
 */
void MachineSystem::SetResourceDirectory(const std::wstring& resourcesDir)
{
    if (mMachine)
    {
        mMachine->SetResourceDirectory(resourcesDir);
    }
}

/**
 * Set a flag
 * @param flag Flag to set
 */
void MachineSystem::SetFlag(int flag) {
    // Not implemented
}

/**
 * Create a machine
 * @param machineNumber Machine number
 */
void MachineSystem::CreateMachine(int machineNumber)
{
    if (machineNumber == 1)
    {
        Machine1Factory factory(mResourcesDir);
        mMachine = factory.Create();
        mBox = factory.GetBox();
        mSparty = factory.GetSparty();
        mKey = factory.GetKey();
        mCam = factory.GetCam();
    }
    else if (machineNumber == 2)
    {
        Machine2Factory factory(mResourcesDir);
        mMachine = factory.Create();
        mBox = factory.GetBox();
        mSparty = factory.GetSparty();
        mKey = factory.GetKey();
        mCam = factory.GetCam();
    }
    else
    {
        mMachine = nullptr; // Handle invalid machine numbers
    }
}

/**
 * Play the machine
 */
void MachineSystem::SetTime(double time)
{
    if (time == 0)
    {
        Reset(); // Ensure the system resets when moving backward in time
    }

    mTime = time; // Update the system's time
    if (mMachine)
    {
        mMachine->SetTime(mTime); // Propagate time to the machine
    }
}

/**
 * Updates the machine system
 * @param timeStep
 */
void MachineSystem::Update(double timeStep)
{
    mTime += timeStep;
    mMachine->Update(timeStep); // Update the machine's components
    mMachine->SetTime(mTime);    // Synchronize machine time
}


/**
 * Reset the machine system
 */
void MachineSystem::Reset()
{
    mTime = 0.0;
    mLastFrame = -1; // Reset the frame counter

    if (mMachine) {
        mMachine->Reset();
    }

    // Reset each component
    if (mBox) {
        mBox->Reset();
    }

    if (mSparty) {
        mSparty->Reset();
    }

    if (mCam) {
        mCam->Reset();
    }

    if (mKey) {
        mKey->Reset();
    }
}
