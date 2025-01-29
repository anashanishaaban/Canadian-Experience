/**
 * @file MachineStartTimeDlg.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINESTARTTIMEDLG_H
#define CANADIANEXPERIENCE_MACHINESTARTTIMEDLG_H

#include <wx/wx.h>
#include <wx/valnum.h>
#include "MachineAdapter.h"

/**
 * Dialog for setting the start time of a machine.
 */
class MachineStartTimeDlg : public wxDialog
{
private:
    double mStartTime;  ///< Start time to be edited
    MachineAdapter* mMachineAdapter; ///< Pointer to the machine adapter

public:
    /**
     * Constructor
     * @param parent The parent window for this dialog
     * @param machineAdapter The machine adapter to update the start time
     */
    MachineStartTimeDlg(wxWindow* parent, MachineAdapter* machineAdapter);

    /// Event handler for OK button
    void OnOK(wxCommandEvent& event);
};

#endif //CANADIANEXPERIENCE_MACHINESTARTTIMEDLG_H
