#include <random>
#include <iostream>
#include <cmath>
#include <vector>
#include <stack> 
#include <ctime>


template <typename T>
class stackM
{
private:
    unsigned int sizeOfStack;
    T* data;

public:
    stackM(const unsigned int maxSize)
    {
        sizeOfStack = 0;
        data = new T[maxSize];
    }

    ~stackM()
    {
        delete[]data;
    }

    const T& top()const
    {
        return data[sizeOfStack - 1];
    }

    T& top()
    {
        return data[sizeOfStack - 1];
    }

    void push(T&& elem)
    {
        data[sizeOfStack] = elem;
        sizeOfStack++;
    }

    void push(const T& elem)
    {
        data[sizeOfStack] = elem;
        sizeOfStack++;
    }

    void pop()
    {
        sizeOfStack--;
    }

    int size()
    {
        return sizeOfStack;
    }
};

template <typename T>
class stackL
{
private:
    struct Node
    {
        T data;
        Node* link;
    };

public:
    int count = 0;
    Node* top = NULL;

    void push(T value)
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



void test_stack_arr(int k, int n)
{
    int count = n;
    stackM<int> arrStack(n);
    for (; k != 0; k--)
    {
        while (count != 0)
        {
            arrStack.push(1);
            count--;
        }
        while (count != n)
        {
            arrStack.pop();
            count++;
        }
    }
}

void test_stack_list(int k, int n)
{
    int count = n;
    stackL<int> liststack;
    for (; k != 0; k--)
    {
        while (count != 0)
        {
            liststack.push(1);
            count--;
        }

        while (count != n)
        {
            liststack.pop();
            count++;
        }
    }
}

void test_stack(int k, int n)
{
    int count = n;
    std::stack <int> Stack;
    for (; k != 0; k--)
    {
        while (count != 0)
        {
            Stack.push(1);
            count--;
        }
        while (count != n)
        {
            Stack.pop();
            count++;
        }
    }
}

template<typename Stack>
void print_stack(Stack& st) {
    Stack tmp(st.size());
    while (st.size()) {
        tmp.push(st.top());
        std::cout << st.top() << ' ';
        st.pop();
    }
    std::cout << '\n';

    while (tmp.size() > 0) {
        st.push(tmp.top());
        tmp.pop();
    }
}

template <typename Stack, typename T>
void delete_elem_from_stack(Stack& src, T elem)
{
    Stack newStack(src.size());
    while (src.size())
    {
        if (elem != src.top())
        {
            newStack.push(src.top());
            src.pop();
        }
        else
        {
            src.pop();
        }
    }
    while (newStack.size())
    {
        src.push(newStack.top());
        newStack.pop();
    }
}

template <typename Stack>
void stack_sort(Stack& src)
{
    Stack first(src.size()), second(src.size());
    while (src.size())
    {
        if (first.size() == 0)
        {
            first.push(src.top());
            src.pop();
        }
        while (first.size() && src.top() <= first.top())
        {
            second.push(first.top());
            first.pop();
        }
        first.push(src.top());
        src.pop();
        while (second.size())
        {
            first.push(second.top());
            second.pop();
        }
    }
    while (first.size())
    {
        src.push(first.top());
        first.pop();
    }
}

int main()
{       
    //double start_time = clock(); // начальное время
    //test_stack_arr(pow(10, 8), pow(10, 0));
    //test_stack_list(pow(10, 8), pow(10, 0));
    //test_stack(pow(10, 8), pow(10, 0));
    //double end_time = clock(); // конечное время
    /*stackM<int> newStack(12);
    newStack.push(1);
    newStack.push(10);
    newStack.push(12);
    newStack.push(0);
    newStack.push(1);
    newStack.push(3);
    newStack.push(4);
    newStack.push(98);
    newStack.push(11);
    newStack.push(87);
    newStack.push(5);
    newStack.push(2);
    print_stack(newStack);
    stack_sort(newStack);
    print_stack(newStack);*/
    /*stackM<char> newStack(12);
    newStack.push('a');
    newStack.push('l');
    newStack.push('q');
    newStack.push('b');
    newStack.push('u');
    newStack.push('y');
    newStack.push('w');
    newStack.push('e');
    newStack.push('x');
    newStack.push('k');
    newStack.push('s');
    newStack.push('c');
    print_stack(newStack);
    stack_sort(newStack);
    print_stack(newStack);*/

    stackM<int> newStack(10);
    newStack.push(1);
    newStack.push(2);
    newStack.push(1);
    newStack.push(3);
    newStack.push(1);
    newStack.push(4);
    newStack.push(1);
    newStack.push(5);
    delete_elem_from_stack(newStack, 1);
    print_stack(newStack);
}
