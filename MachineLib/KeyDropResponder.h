/**
 * @file KeyDropResponder.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_KEYDROPRESPONDER_H
#define CANADIANEXPERIENCE_MACHINELIB_KEYDROPRESPONDER_H

/**
 * Interface for responding to a key drop event.
 */
class KeyDropResponder
{
public:
    virtual ~KeyDropResponder() = default;

    /**
     * This method is called when the key drops into the cam's hole.
     */
    virtual void OnKeyDropped() = 0;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_KEYDROPRESPONDER_H
