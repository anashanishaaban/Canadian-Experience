/**
 * @file Machine1Factory.h
 *
 * @author Anik Momtaz
 * @author Charles Owen
 *
 * Factory for creating Machine #1
 */

#ifndef CANADIANEXPERIENCE_MACHINE1FACTORY_H
#define CANADIANEXPERIENCE_MACHINE1FACTORY_H

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


class Machine;

/**
 * Factory for creating Machine #1
 */
class Machine1Factory {
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

    std::shared_ptr<Machine> mMachine;

    std::shared_ptr<Cam> mCam;

    std::shared_ptr<Key> mKey;

    std::shared_ptr<Sparty> mSparty;

    std::shared_ptr<Box> mBox;

    std::shared_ptr<Crank> mCrank;

    std::shared_ptr<Shaft> mShaft;

    std::shared_ptr<Pulley> mPulley1;
    std::shared_ptr<Pulley> mPulley2;
    std::shared_ptr<Pulley> mPulley3;
    std::shared_ptr<Pulley> mPulley4;

    std::shared_ptr<Component> mComponent;



public:
    Machine1Factory(std::wstring resourcesDir);

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
     * Get the Pulley1 component
     * @return Pulley1 component
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

#endif //CANADIANEXPERIENCE_MACHINE1FACTORY_H
