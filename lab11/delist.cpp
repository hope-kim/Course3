#include <iostream>
#include "delist.h"

using namespace std;

// Constructs an empty Double-Ended List
DEList::DEList()
{
    mSize = 0;
    mHead = 0;
    mTail = 0;
}
// Destructor to clean-up memory of current list
DEList::~DEList()
{
    while (mSize > 0)
    {
        pop_front();
    }
}
// returns a Boolean 'true' if the list is empty
bool DEList::empty()
{
    if (mSize == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// returns number of items in the list
int DEList::size()
{
    return mSize;
}
// returns front item or -1 if empty list
int DEList::front()
{
    if (mSize == 0)
    {
        return -1;
    }
    else
    {
        return mHead->val;
    }
}
// returns back item or -1 if empty list
int DEList::back()
{
    if (mSize == 0)
    {
        return -1;
    }
    else
    {
        return mTail->val;
    }
}
// Adds a new integer to the front of the list
void DEList::push_front(int new_val)
{
    DEItem* item = new DEItem;
    item->val = new_val;
    item->prev = 0;
    item->next = mHead;
    
    if (mSize == 0)
    {
        mTail = item;
    }
    else
    {
        mHead->prev = item;
    }
    mHead = item;
    mSize++;
}
// Adds a new integer to the back of the list
void DEList::push_back(int new_val)
{
    DEItem* item = new DEItem;
    item->val = new_val;
    item->prev = mTail;
    item->next = 0;
    if (mSize == 0)
    {
        mHead = item;
    }
    else
    {
        mTail->next = item;
    }
    mTail = item;
    mSize++;
}
// Removes the front item of the list (if it exists)
void DEList::pop_front()
{
    if (mSize == 0)
    {
        return;
    }
    else if (mSize == 1)
    {
        delete mHead;
        mSize = 0;
        mHead = 0;
        mTail = 0;
    }
    else
    {
        DEItem* temp = mHead->next;
        delete mHead;
        mHead = temp;
        mHead->prev = 0;
        mSize--;
    }
}
// Removes the back item of the list (if it exists)
void DEList::pop_back()
{
    if (mSize == 0)
    {
        return;
    }
    else if (mSize == 1)
    {
        delete mTail;
        mSize = 0;
        mHead = 0;
        mTail = 0;
    }
    else
    {
        DEItem* temp = mTail->prev;
        delete mTail;
        mTail = temp;
        mTail->next = 0;
        mSize--;
    }
}

