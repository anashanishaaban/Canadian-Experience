/**
 * @file Machine2Factory.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H

#include <memory>
#include <string>
#include <wx/graphics.h>
#include "Cam.h"
#include "Key.h"
#include "Sparty.h"
#include "Box.h"
#include "Crank.h"
#include "Shaft.h"
#include "Pulley.h"
#include "Machine.h"
#include "IMachineSystem.h"

/**
 * Factory class that creates the machine
 */
class Machine2Factory
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

    /// The machine
    std::shared_ptr<Machine> mMachine;


    /// The cam
    std::shared_ptr<Cam> mCam;

    /// The key
    std::shared_ptr<Key> mKey;

    /// The sparty
    std::shared_ptr<Sparty> mSparty;

    /// The box
    std::shared_ptr<Box> mBox;

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

    /// The component
    std::shared_ptr<Component> mComponent;


public:
    Machine2Factory(std::wstring resourcesDir);

    std::shared_ptr<Machine> Create();

    // Accessors to retrieve specific components

    /**
     * Get the Box component
     * @return Box component
     */
    std::shared_ptr<Box> GetBox() const { return mBox; }

    /**
     * Get the Sparty component
     * @return Sparty component
     */
    std::shared_ptr<Sparty> GetSparty() const { return mSparty; }

    /**
     * Get the Cam component
     * @return Cam component
     */
    std::shared_ptr<Cam> GetCam() const { return mCam; }

    /**
     * Get the Crank component
     * @return Crank component
     */
    std::shared_ptr<Key> GetKey() const { return mKey; }

    /**
     * Get the Crank component
     * @return Crank component
     */
    std::shared_ptr<Crank> GetCrank() const { return mCrank; }

    /**
     * Get the Shaft component
     * @return Shaft component
     */
    std::shared_ptr<Shaft> GetShaft() const { return mShaft; }

    /**
     * Get a component
     * @return Component
     */
    std::shared_ptr<Component> GetComponent() const { return mComponent; }

    /**
     * Get the Pulley1 component
     * @return Pulley1 component
     */
    std::shared_ptr<Pulley> GetPulley1() const { return mPulley1; }

    /**
     * Get the Pulley2 component
     * @return Pulley2 component
     */
    std::shared_ptr<Pulley> GetPulley2() const { return mPulley2; }

    /**
     * Get the Pulley3 component
     * @return Pulley3 component
     */
    std::shared_ptr<Pulley> GetPulley3() const { return mPulley3; }

    /**
     * Get the Pulley4 component
     * @return Pulley4 component
     */
    std::shared_ptr<Pulley> GetPulley4() const { return mPulley4; }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
