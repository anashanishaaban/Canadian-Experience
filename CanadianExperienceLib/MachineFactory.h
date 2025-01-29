/**
 * @file MachineFactory.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEFACTORY_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEFACTORY_H

#include <memory>
#include <string>

class Actor;

/**
 * Factory class that builds a machine actor
 */
class MachineFactory {
public:
    /**
     * Create a machine actor
     * @param imagesDir Directory that contains the images for this application
     * @param machine The machine adapter to add to the actor
     * @return Pointer to an actor object
     */
    std::shared_ptr<Actor> Create(std::wstring imagesDir, std::shared_ptr<class MachineAdapter> machine);
};


#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEFACTORY_H
