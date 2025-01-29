/**
 * @file Machine.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"

void Machine::SetLocation(wxPoint location)
{
    mLocation = location;
    for (auto& component : mComponents)
    {
        component->SetLocation(location);
    }
}

wxPoint Machine::GetLocation()
{
    return mLocation;
}

void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!graphics) return;

    // Step 1: Draw background and components that are behind everything
    for (auto& component : mComponents)
    {
            component->Draw(graphics);

    }


    // Step 5: Explicitly draw any additional foreground elements
    for (auto& component : mComponents)
    {
        component->DrawForeground(graphics);
    }
}



void Machine::SetFrame(int frame)
{
    for (auto& component : mComponents)
    {
        component->Update(frame);
    }
}

void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
}

void Machine::SetMachineNumber(int number)
{
    mMachineNumber = number;
}

int Machine::GetMachineNumber()
{
    return mMachineNumber;
}

void Machine::SetResourceDirectory(const std::wstring& resourcesDir)
{
    for (auto& component : mComponents)
    {
        component->SetImageDirectory(resourcesDir);
    }
}

void Machine::Update(double elapsedTime) {
    for (auto& component : mComponents) {
        component->Update(elapsedTime);
    }
}


void Machine::SetTime(double time)
{
    for (auto& component : mComponents)
    {
        component->SetTime(time); // Synchronize component time
    }
}

void Machine::Reset()
{
    // Reset all components to their initial state
    for (auto& component : mComponents)
    {
        component->Reset();
    }
}