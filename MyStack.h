#ifndef MYSTACK_H
#define MYSTACK_H
class MyStack{
public:
    MyStack();
    ~MyStack();
    void clear();
    void push(const int& num);
    int  pop();
    int  top();
    int  size();
    bool empty();
    bool contains(int data);
    int  indexof(int index);
private:
    int _index;
    int _data[600];
};

#endif // MYSTACK_H

