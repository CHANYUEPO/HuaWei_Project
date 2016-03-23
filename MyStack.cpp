#include "MyStack.h"
MyStack::MyStack()
    :_index(-1)
{

}
int MyStack::top()
{
    return _data[_index];
}
int MyStack::indexof(int index)
{
    return _data[index];
}

int MyStack::pop()
{
    if(_index>=0)
       return _data[_index--];
    else
        return -1;
}
bool MyStack::contains(int data)
{
    for(int i=0;i<=_index;i++)
    {
        if(_data[i]==data)
            return true;
    }
    return false;
}
bool MyStack::empty()
{
    if(_index==-1)
        return true;
    else
        return false;
}

void MyStack::clear()
{
    _index=-1;
}
void MyStack::push(const int &num)
{
    _data[++_index]=num;
}
int MyStack::size()
{
    return _index+1;
}
MyStack::~MyStack()
{

}
