/******************************************************************************
 *  Class: DynamicList
 * ----------------------------------------------------------------------------
 * Purpose: This
 *
 *
 * ----------------------------------------------------------------------------
 * Exists within: InitiativeTracker, DatabaseManager
 *
 *
 *
 ******************************************************************************/

#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
class DynamicList
{
private:
    T* _list;
    int _size;
    int _capacity;

public:

    /**************************************************************************
     * FUNCTION: Size
     * ------------------------------------------------------------------------
     * Purpose : This function returns the size of the DynamicList
     * ------------------------------------------------------------------------
     * Receives:
     *     nothing
     * Returns:
     *     _count : int
     *************************************************************************/
    int Size() const { return _size; }

    /**************************************************************************
     * FUNCTION: Add
     * ------------------------------------------------------------------------
     * Purpose : This function adds items to the DynamicList. If list reaches
     *           capacity, list will double in size and allocate new item.
     * ------------------------------------------------------------------------
     * Receives:
     *     elem : T : Item to be added to list
     * Returns:
     *     nothing
     *************************************************************************/
    void Add(T elem)
    {
        // if count < capacity
        if(_size < _capacity)
        {
            _list[_size] = elem;
            _size++;
        }
        else // If count >= cap
        {
            // Create new list
            T* newList = new T[2 * _capacity];

            // Copy old list into it
            for(int index = 0; index < _size; index++)
            {
                newList[index] = _list[index];
            }

            // Double capacity
            _capacity = _capacity *2;

            // Delete old list
            delete[] _list;

            // Assign old to new
            _list = newList;

            // Add element to list
            _list[_size] = elem;
            _size++;
        }
    }

    /**************************************************************************
     * FUNCTION: Remove
     * ------------------------------------------------------------------------
     * Purpose : This function removes an item from the list. When removed,
     *           rest of list will shift down to fill empty space. May need
     *           to adjust sorting method in the future for larger lists.
     * ------------------------------------------------------------------------
     * Receives:
     *     elem : T : Item to be removed from list
     * Returns:
     *     nothing
     *************************************************************************/
    void Remove(T elem)
    {
        if(_size == 0)
        {
            cout << "Cannot delete from empty list";
        }
        else
        {
            // if count < capacity
            if(_size >= _capacity)
            {
                // Create new list
                T* newList = new T[2 * _capacity];

                // Copy old list into it
                for(int index = 0; index < _size; index++)
                {
                    newList[index] = _list[index];
                }

                // Double capacity
                _capacity = _capacity *2;

                // Delete old list
                delete[] _list;

                // Assign old to new
                _list = newList;
            }

            bool found = false;
            int index = 0;

            while(index < _size && !found)
            {
                found = (elem == _list[index]);
                if(found)
                {
                    // move everything down one spot to maintain positioning
                    while(index < _size)
                    {
                        _list[index] = _list[index + 1];
                        index++;
                    }
                    _size--;
                }
                else
                {
                    index++;
                }
            }// END while(index < _count && !found)
        }
    }

    /**************************************************************************
     * FUNCTION: IsEmpty
     * ------------------------------------------------------------------------
     * Purpose : This function returns true if list is empty. False if it is
     *           not
     * ------------------------------------------------------------------------
     * Receives:
     *     nothing
     * Returns:
     *     _count == 0 : bool
     *************************************************************************/
    bool IsEmpty() const { return _size == 0; }

    /**************************************************************************
     * FUNCTION: Print TESTING PURPOSES ONLY
     * ------------------------------------------------------------------------
     * Purpose : This function prints the list
     * ------------------------------------------------------------------------
     * Receives:
     *     nothing
     * Returns:
     *     nothing
     *************************************************************************/
    void Print() const
    {
        for(int index = 0; index < _size; index++)
        {
            cout << _list[index].GetName() << endl;
        }
    }

    void InitializeList()
    {
        delete [] _list;
        _size = 0;
        _capacity = 1;
        _list = new T [_capacity];
    }

    // Overload [] Operator
    T& operator[](int index)
    {
        assert(0 <= index && index < _size);
        return _list[index];
    }

    // Constructors
        // Default
    DynamicList()
    {
        _size = 0;
        _capacity = 1;
        _list = new T [_capacity];
    }

        // Size Parameter Constructor
    DynamicList(const int size)
    {
        _size = 0;
        _capacity = size;
        _list = new T[_capacity];
    }

        // Copy Constructor
    DynamicList(const DynamicList<T> &other)
    {
        _capacity = other._capacity;
        _list = new T[_capacity];
        _size = other._size;

        // Copy old list into it
        for(int index = 0; index < other._size; index++)
        {
            _list[index] = other._list[index];
        }
    }

    // Destructor
    ~DynamicList()
    {
        delete [] _list;
    }
};

#endif // DYNAMICLIST_H
