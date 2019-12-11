/******************************************************************************
 *  Class: Actor
 * ----------------------------------------------------------------------------
 * Purpose: This is the object that each player character, monster, and ally
 *          exists as. It has a name and an initiative.
 ******************************************************************************/

#ifndef ACTOR_H
#define ACTOR_H

#include <string>
using namespace std;

class Actor
{
private:
    string _name;
    int _initiative;

public:
    /**************************************************************************
     * FUNCTION: SetName
     * ------------------------------------------------------------------------
     * Purpose : This function allows _name to be set outside of this class
     * ------------------------------------------------------------------------
     * Receives:
     *     name  : const string
     * Returns:
     *     nothing
     *************************************************************************/
    void SetName (const string &name) { _name = name; }

    /**************************************************************************
     * FUNCTION: SetInitiative
     * ------------------------------------------------------------------------
     * Purpose : This function allows _initiative to be set outside of this
     *           class
     * ------------------------------------------------------------------------
     * Receives:
     *     initiative : const int
     * Returns:
     *     nothing
     *************************************************************************/
    void SetInitiative(const int &initiative) { _initiative = initiative; }

    /**************************************************************************
     * FUNCTION: GetName
     * ------------------------------------------------------------------------
     * Purpose : This function allows _name to be accessed outside of this
     *           class
     * ------------------------------------------------------------------------
     * Receives:
     *     nothing
     * Returns:
     *     name : string
     *************************************************************************/
    string GetName() const { return _name; }
    int GetInitiative() const { return _initiative; }

    /**************************************************************************
     * FUNCTION: operator==
     * ------------------------------------------------------------------------
     * Purpose : This function overloads == operator to allow comparison of
     *           specific datamembers
     * ------------------------------------------------------------------------
     * Receives:
     *     other : const Actor
     * Returns:
     *     same  : bool
     *************************************************************************/
    bool operator==(const Actor &other) const
    {
        bool same = false;

        same = _name == other._name;

        return same;
    }

    // Constructors
        // Default
    Actor()
    {
        _name = "";
        _initiative = 0;
    }
        // Full
    Actor(string &name, int &initiative)
    {
        _name = name;
        _initiative = initiative;
    }
        // Copy
    Actor(const Actor &other)
    {
        _name = other._name;
        _initiative = other._initiative;
    }

    // Destructor
    ~Actor() { }
};

#endif // ACTOR_H
