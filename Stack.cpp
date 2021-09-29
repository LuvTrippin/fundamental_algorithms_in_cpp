#pragma once
#include <iostream>

template <typename T>
class stackM
{
private:
    int count;
    T* data;

public:
    stackM(int capacity = 50000)
    {
        count = 0;
        data = new T[capacity];
    }

    ~stackM()
    {
        delete[] data;
    }

    const T& top()const
    {
        return data[count];
    }


    T& top()
    {
        return data[count];
    }

    void push(T&& elem)
    {
        count++;
        data[count] = elem;
    }

    void push(const T& elem)
    {
        count++;
        data[count] = elem;
    }

    void pop()
    {
        count--;
    }

    int size()
    {
        return count;
    }
};

template <typename T>
class stackL
{
private:
    struct Node
    {
        int data;
        Node* link;
    };

public:
    int count = 0;
    Node* top = NULL;

    void push(int value)
    {
        Node* ptr = new Node();
        ptr->data = value;
        ptr->link = top;
        top = ptr;
        count++;
    }

    void pop()
    {

        Node* ptr = top;
        top = top->link;
        delete(ptr);
        count--;
    }

    T& Top()
    {
        return top->data;
    }

    int size()
    {
        return count;
    }
};

int main()
{
    stackL<int> newStack;
    newStack.push(2);
    std::cout << newStack.Top();
    stackM<int> newStackm;
    newStackm.push(12);
    std::cout << std::endl << newStackm.top();
}