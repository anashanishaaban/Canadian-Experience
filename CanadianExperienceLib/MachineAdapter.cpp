/**
 * @file MachineAdapter.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include "MachineAdapter.h"
#include "Timeline.h"
#include <wx/xml/xml.h>
#include <machine-api.h>

MachineAdapter::MachineAdapter(const std::wstring& name, std::shared_ptr<IMachineSystem> machine, Timeline* timeline)
    : Drawable(name), mMachine(machine)
{
    SetTimeline(timeline);
    mFrameRate = timeline->GetFrameRate();
}


void MachineAdapter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    SetMachineFrame(mTimeline->GetCurrentFrame());

    graphics->PushState();
    graphics->Translate(GetPosition().x, GetPosition().y);
    graphics->Scale(0.75, 0.75); // Scale down machine for integration
    mMachine->SetLocation(wxPoint(0, 0));
    mMachine->DrawMachine(graphics);
    graphics->PopState();
}

void MachineAdapter::SetTimeline(Timeline* timeline)
{
    Drawable::SetTimeline(timeline);
    mTimeline = timeline;
    int startFrame = static_cast<int>(mStartTime * mFrameRate);
    // Use startFrame as needed for custom animations
}

wxXmlNode* MachineAdapter::XmlSave(wxXmlNode* node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"MachineAdapter");
    node->AddChild(itemNode);
    itemNode->AddAttribute(L"machine-number", std::to_wstring(mMachineNumber));
    itemNode->AddAttribute(L"start-time", std::to_wstring(mStartTime));
    return itemNode;
}

void MachineAdapter::XmlLoad(wxXmlNode* node)
{
    wxString machineNumberStr = node->GetAttribute(L"machine-number", L"1");
    wxString startTimeStr = node->GetAttribute(L"start-time", L"0");
    mMachineNumber = std::stoi(machineNumberStr.ToStdWstring());
    mStartTime = std::stod(startTimeStr.ToStdWstring());
    mMachine->ChooseMachine(mMachineNumber);
}

void MachineAdapter::ShowMachineDialog(wxWindow* parent)
{
    MachineDialog dialog(parent, mMachine);
    if (dialog.ShowModal() == wxID_OK)
    {
        // Retrieve the updated machine number from the machine system
        mMachineNumber = mMachine->GetMachineNumber();
    }
}

void MachineAdapter::SetMachineNumber(int number)
{
    mMachineNumber = number;
    mMachine->ChooseMachine(mMachineNumber);
}

void MachineAdapter::SetMachineFrame(int frame)
{
    double elapsedTime = frame / mFrameRate; // Calculate elapsed time
    if (elapsedTime >= mStartTime) // Only start after the specified start time
    {
        int adjustedFrame = ((elapsedTime - mStartTime) * mFrameRate);
        mMachine->SetMachineFrame(adjustedFrame);
    }
}

void MachineAdapter::OpenMachineDialog(wxWindow* parent)
{
    // Open the dialog and pass the current machine system
    MachineDialog dialog(parent, mMachine);

    if (dialog.ShowModal() == wxID_OK)
    {
        // After the dialog, the machine number may have been updated
        int newMachineNumber = mMachine->GetMachineNumber();

        mMachine->ChooseMachine(newMachineNumber); // Ensure this updates the internal machine configuration

        // Perform any additional updates or re-initialization based on the new machine
        wxLogMessage(L"MachineAdapter updated to machine %d", newMachineNumber);
    }
}