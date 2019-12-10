/******************************************************************************
 *  Class: Actor
 * ----------------------------------------------------------------------------
 * Purpose: This is the object that each player character, monster, and ally
 *          exists as. It has a name and an initiative.
 *
 *
 * ----------------------------------------------------------------------------
 * Exists within: DynamicList
 *
 *
 *
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
    // Setters
    void SetName (const string &name) { _name = name; }
    void SetInitiative(const int &initiative) { _initiative = initiative; }
    // Getters
    string GetName() const { return _name; }
    int GetInitiative() const { return _initiative; }

    // Public Methods
    void print();

    // Overloaded Operators
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
        _initiative = -999;
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
