/**
 * @file PictureFactory.cpp
 *
 * @author Charles Owen
 * @author Anik Momtaz
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineFactory.h"
#include "MachineAdapter.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
        std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background2.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(150, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(650, 620));
    picture->AddActor(sparty);

    // Create the machine systems
    MachineSystemFactory systemFactory(resourcesDir);
    auto machineSystem1 = systemFactory.CreateMachineSystem();
    auto machineSystem2 = systemFactory.CreateMachineSystem();



    // Create the machine adapters and configure their machine numbers
    auto machineAdapter1 = std::make_shared<MachineAdapter>(L"Machine1", machineSystem1, picture->GetTimeline());
    machineAdapter1->SetMachineNumber(1); // Set this adapter to use Machine 1
    machineAdapter1->SetStartTime(10);   // Start time for Machine 1

    auto machineAdapter2 = std::make_shared<MachineAdapter>(L"Machine2", machineSystem2, picture->GetTimeline());
    machineAdapter2->SetMachineNumber(2); // Set this adapter to use Machine 2
    machineAdapter2->SetStartTime(15);   // Start time for Machine 1

    // Create the machine actors
    MachineFactory machineFactory;
    auto machineActor1 = machineFactory.Create(imagesDir, machineAdapter1);
    auto machineActor2 = machineFactory.Create(imagesDir, machineAdapter2);

    // Position the machines
    machineAdapter1->SetPosition(wxPoint(50, 200)); // Position for Machine 1
    machineAdapter2->SetPosition(wxPoint(500, 200)); // Position for Machine 2

    // Add the machine actors to the picture
    picture->AddActor(machineActor1);
    picture->AddActor(machineActor2);

    return picture;
}