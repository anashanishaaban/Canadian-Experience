/**
 * @file Machine.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

#include "Box.h"
#include "Sparty.h"


class Component;

/**
 * Machine class that represents a machine in the system
 */
class Machine
{
private:
    std::vector<std::shared_ptr<Component>> mComponents; ///< Components of the machine
    wxPoint mLocation; ///< Location of the machine
    int mMachineNumber = 1; ///< Machine number
    std::wstring mResourcesDir; ///< Resources directory
    std::shared_ptr<Box> mBox;

    std::shared_ptr<Sparty> mSparty;

public:

    std::shared_ptr<Component> FindComponentByName(const std::wstring& name)
    {
        for (const auto& component : mComponents)
        {
            if (component->GetName() == name)
            {
                return component;
            }
        }
        return nullptr; // Not found
    }

    Machine() = default;

    void SetLocation(wxPoint location);

    wxPoint GetLocation();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void SetFrame(int frame);

    void AddComponent(std::shared_ptr<Component> component);

    void SetMachineNumber(int number);

    int GetMachineNumber();

    void SetResourceDirectory(const std::wstring& resourcesDir);

    void Update(double elapsedTime);

    void SetTime(double time);

    void Reset();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
