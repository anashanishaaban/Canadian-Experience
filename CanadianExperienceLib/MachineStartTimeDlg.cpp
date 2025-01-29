/**
 * @file MachineStartTimeDlg.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include "MachineStartTimeDlg.h"
#include <wx/xrc/xmlres.h>

MachineStartTimeDlg::MachineStartTimeDlg(wxWindow* parent, MachineAdapter* machineAdapter)
    : wxDialog(parent, wxID_ANY, L"Set Machine Start Time"), mMachineAdapter(machineAdapter)
{
    mStartTime = machineAdapter->GetStartTime();

    // Main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Label and input for start time
    wxBoxSizer* startTimeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* labelStartTime = new wxStaticText(this, wxID_ANY, L"Start Time (seconds):", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    startTimeSizer->Add(labelStartTime, 1, wxALIGN_CENTER_VERTICAL | wxALL, 10);

    auto startTimeCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, -1));
    wxFloatingPointValidator<double> validator(&mStartTime, wxNUM_VAL_DEFAULT);
    validator.SetRange(0.0, 10000.0);
    startTimeCtrl->SetValidator(validator);
    startTimeSizer->Add(startTimeCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);

    mainSizer->Add(startTimeSizer, 0, wxEXPAND | wxALL, 10);

    // Add standard OK/Cancel buttons
    auto buttonSizer = new wxStdDialogButtonSizer();
    buttonSizer->AddButton(new wxButton(this, wxID_OK));
    buttonSizer->AddButton(new wxButton(this, wxID_CANCEL));
    buttonSizer->Realize();

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizerAndFit(mainSizer);

    // Bind OK button event
    Bind(wxEVT_BUTTON, &MachineStartTimeDlg::OnOK, this, wxID_OK);
}

/**
 * Handle the OK button press event
 * @param event Button press event
 */
void MachineStartTimeDlg::OnOK(wxCommandEvent& event)
{
    if (Validate() && TransferDataFromWindow())
    {
        mMachineAdapter->SetStartTime(mStartTime); // Update the machine adapter
        EndModal(wxID_OK);
    }
}