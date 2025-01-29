/**
 * @file MachineFactory.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include "MachineFactory.h"
#include "Actor.h"
#include "MachineAdapter.h"

/**
 * Create a machine actor
 * @param imagesDir Directory that contains the images for this application
 * @param machine The machine adapter to add to the actor
 * @return Pointer to an actor object
 */
std::shared_ptr<Actor> MachineFactory::Create(std::wstring imagesDir, std::shared_ptr<MachineAdapter> machine)
{
    std::shared_ptr<Actor> actor = std::make_shared<Actor>(L"Machine");

    // Set the MachineAdapter as the root drawable
    machine->SetPosition(wxPoint(0, 0));
    actor->SetRoot(machine);

    // Add the adapter to the actor's drawables
    actor->AddDrawable(machine);

    return actor;
}


