/**
 * @file Machine1Factory.cpp
 *
 * @author Charles Owen
 */

#include "pch.h"
#include "Machine1Factory.h"
#include "Machine.h"
#include "Box.h"
#include "Sparty.h"
#include "Crank.h"
#include "Shaft.h"
#include "Pulley.h"
#include "Cam.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
Machine1Factory::Machine1Factory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}

/**
 * Factory method to create machine #1
 * @return
 */
std::shared_ptr<Machine> Machine1Factory::Create()
{
    auto machine = std::make_shared<Machine>();

    // Create and configure the Box component
    mBox = std::make_shared<Box>(mResourcesDir + L"/images", 250, 240);
    mBox->SetPosition(wxPoint(450, 525)); // Set box position
    mBox->SetImageDirectory(mResourcesDir); // Set the resources directory
    mBox->SetName(L"Box");
    machine->AddComponent(mBox);

    // Create and configure the Sparty component
    mSparty = std::make_shared<Sparty>(mResourcesDir + L"/images/sparty.png", 210.0, 50.0);
    mSparty->SetPosition(wxPoint(450, 550)); // Set Sparty position
    mSparty->SetName(L"Sparty");
    machine->AddComponent(mSparty);

    // Create shafts
    auto shaft1 = std::make_shared<Shaft>();
    shaft1->SetPosition(wxPoint(540, 350));
    shaft1->SetSize(10, 70);
    shaft1->SetName(L"Shaft1");
    machine->AddComponent(shaft1);

    auto shaft2 = std::make_shared<Shaft>();
    shaft2->SetPosition(wxPoint(335, 455));
    shaft2->SetSize(10, 230);
    shaft2->SetName(L"Shaft2");
    machine->AddComponent(shaft2);

    auto shaft3 = std::make_shared<Shaft>();
    shaft3->SetPosition(wxPoint(335, 347));
    shaft3->SetSize(10, 50);
    shaft3->SetName(L"Shaft3");
    machine->AddComponent(shaft3);

    // Configure shafts
    shaft1->SetGearRatio(0.2);
    shaft2->SetGearRatio(0.5);
    shaft3->SetGearRatio(2);

    // Create crank
    mCrank = std::make_shared<Crank>(shaft1.get());
    mCrank->SetPosition(wxPoint(600, 360));
    mCrank->SetName(L"Crank");
    mCrank->GetSource()->AddSink(shaft1);
    machine->AddComponent(mCrank);

    // Create pulleys
    auto pulley1 = std::make_shared<Pulley>(45, 0.8, 590, 455);
    pulley1->SetName(L"Pulley1");
    machine->AddComponent(pulley1);

    auto pulley2 = std::make_shared<Pulley>(17, 0.8, 562, 350);
    pulley2->SetName(L"Pulley2");
    machine->AddComponent(pulley2);

    auto pulley4 = std::make_shared<Pulley>(50, 0.8, 390, 347);
    pulley4->SetName(L"Pulley4");
    machine->AddComponent(pulley4);

    auto pulley3 = std::make_shared<Pulley>(10, 0.8, 350, 455);
    pulley3->SetName(L"Pulley3");
    machine->AddComponent(pulley3);

    // Link pulleys and shafts
    pulley1->GetSource()->AddSink(shaft2);
    shaft2->GetSource()->AddSink(pulley3);
    shaft1->GetSource()->AddSink(pulley2);
    pulley2->ConnectToPulley(pulley1);
    pulley3->ConnectToPulley(pulley4);
    pulley4->GetSource()->AddSink(shaft3);

    // Set pulley input ratios
    pulley1->SetInputRatio(0.5);
    pulley2->SetInputRatio(0.5);
    pulley3->SetInputRatio(3);
    pulley4->SetInputRatio(0.4);

    // Create and configure the key
    mKey = std::make_shared<Key>(mResourcesDir);
    mKey->SetPosition(wxPoint(370, 317));
    mKey->SetName(L"Key");
    machine->AddComponent(mKey);

    // Create and configure the cam
    mCam = std::make_shared<Cam>(M_PI / 2);
    mCam->SetPosition(wxPoint(370, 350));
    mCam->SetInitialPosition(wxPoint(370, 350)); // Set initial position
    mCam->SetRotation(0.0);
    mCam->SetName(L"Cam");
    mCam->SetKey(mKey);
    shaft3->GetSource()->AddSink(mCam); // Link cam to shaft3
    machine->AddComponent(mCam);

    mPulley1 = pulley1;
    mPulley2 = pulley2;
    mPulley3 = pulley3;
    mPulley4 = pulley4;

    return machine;
}

