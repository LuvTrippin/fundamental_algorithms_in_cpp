#include <random>
#include <iostream>
#include <cmath>
#include <vector>
#include <stack> 
#include <ctime>
#include <string>
#include <optional>
#include <set>
#include <algorithm>

template <typename T>
class stackM
{
private:
    unsigned int sizeOfStack;
    int capacity;
    T* data;

public:
    stackM(const unsigned int maxSize = 50000);
    ~stackM();
    const T& top()const;
    T& top();
    void push(T&& elem);
    void push(const T& elem);
    void pop();
    int size();
    typedef typename T value_type;

    friend void swap(stackM<T> &s1, stackM<T> &s2)
    {
        std::swap(s1.sizeOfStack, s2.sizeOfStack);
        std::swap(s1.data, s2.data);

    }
};

template <typename T>
stackM<T>::stackM(const unsigned int maxSize)
{
    sizeOfStack = 0;
    data = new T[maxSize];

}

template <typename T>
stackM<T>::~stackM()
{
    delete[]data;
}

template <typename T>
const T& stackM<T>::top()const
{
    return data[sizeOfStack - 1];
}

template <typename T>
T& stackM<T>::top()
{
    return data[sizeOfStack - 1];
}

template <typename T>
void stackM<T> ::push(T&& elem)
{
    data[sizeOfStack] = elem;
    sizeOfStack++;
}

template <typename T>
void stackM<T> ::push(const T& elem)
{
    data[sizeOfStack] = elem;
    sizeOfStack++;
}

template <typename T>
void stackM<T> ::pop()
{
    sizeOfStack--;
}

template <typename T>
int stackM<T> ::size()
{
    return sizeOfStack;
}

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

    friend void swap(stackM<T>& s1, stackM<T>& s2)
    {
        std::swap(s1.link, s2.link);
        std::swap(s1.data, s2.data);

    }

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


template<typename Stack, typename T>
void test_stack(Stack& s, int k, int n)
{
    int count = n;
    for (; k != 0; k--)
    {
        while (count != 0)
        {
            s.push(1);
            count--;
        }
        while (count != n)
        {
            s.pop();
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
void delete_elem_from_stack(Stack& src, const T& elem)
{
    Stack newStack(src.size());
    while (src.size())
    {
        if (elem != src.top())
        {
            newStack.push(src.top());
        }
        src.pop();
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
    Stack first, second;
    while (src.size())
    {
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

template <typename Stack>
void mov_elems_from_stack_to_stack(Stack& source, Stack& dest)
{
    if (!source.size())
        return;
    dest.push(source.top());
    source.pop();
    while (source.size() && source.top() > dest.top())
    {
        dest.push(source.top());
        source.pop();
    }
}

template <typename Stack>
void move_top_stack_to_stack(Stack& source, Stack& dest)
{
    dest.push(source.top());
    source.pop();
}

template <typename Stack>
void from_stack_to_stack(Stack& source, Stack& dest)
{
    while (source.size())
    {
        move_top_stack_to_stack(source, dest);
    }
}

template <typename Stack>
auto get_top(Stack& source)
{
    auto tmp = source.top();
    source.pop();
    return tmp;
}

template <typename Stack>
bool equal_stack(Stack& Stack1, Stack& Stack2)
{
    Stack tmp1, tmp2, tmp3, tmp4;
    if (Stack1.size() != Stack2.size())
    {
        return 0;
    }
    while (Stack1.size())
    {
        tmp1.push(Stack1.top());
        tmp2.push(Stack2.top());
        tmp3.push(Stack1.top());
        tmp4.push(Stack2.top());
        Stack1.pop();
        Stack2.pop();
    }
    while (tmp3.size())
    {
        move_top_stack_to_stack(tmp3, Stack1);
        move_top_stack_to_stack(tmp4, Stack2);
    }
    sort_stack(tmp1);
    sort_stack(tmp2);
    while (tmp1.size())
    {
        if (tmp1.top() != tmp2.top())
        {
            return 0;
        }
        tmp1.pop();
        tmp2.pop();

    }
    return 1;
}

template <typename Stack>
void quick_sort(Stack& s)
{
    if (s.size() < 2)
    {
        return;
    }
    Stack l, g, e;
    for (int i = 0; i < s.size() / 2; i++)
    {
        move_top_stack_to_stack(s, l);
    }
    auto pivot = s.top();
    while (l.size())
    {
        from_stack_to_stack(l, s);
    }
    while (s.size())
    {
        if (pivot == s.top())
        {
            move_top_stack_to_stack(s, e);
        }
        else if (pivot < s.top())
        {
            move_top_stack_to_stack(s, g);
        }
        else if (pivot > s.top())
        {
            move_top_stack_to_stack(s, l);
        }
    }

    quick_sort(l);
    quick_sort(g);
    from_stack_to_stack(g, e);
    from_stack_to_stack(e, s);
    from_stack_to_stack(l, e);
    from_stack_to_stack(e, s);

}


template <typename Stack>
void merge_stacks_to(Stack& s1, Stack& s2, Stack& dest)
{
    while (s1.size() && s2.size())
    {
        if (s1.top() < s2.top())
        {
            move_top_stack_to_stack(s2, dest);
        }
        else if (s1.top() > s2.top())
        {
            move_top_stack_to_stack(s1, dest);
        }
        else
        {
            move_top_stack_to_stack(s1, dest);
            move_top_stack_to_stack(s2, dest);
        }
    }
    from_stack_to_stack(s1, dest);
    from_stack_to_stack(s2, dest);
}

bool correct_bracket_sequence(std::string& s)
{
    std::stack<char> tmp;

    for (int i = 0; i < s.size(); i++)
    {

        if ((s[i] == ']' or s[i] == ')' or s[i] == '}' or s[i] == '>') && tmp.size())
            return 0;

        if (s[i] == '[' or s[i] == '(' or s[i] == '{' or s[i] == '<')
        {
            tmp.push(s[i]);
        }

        else if ((s[i] == ']' && tmp.top() == '[') || (s[i] == ')' && tmp.top() == '(') || (s[i] == '}' && tmp.top() == '{') || (s[i] = '>' && tmp.top() == '<'))
        {
            tmp.pop();
        }

    }
    if (tmp.size())
        return 0;
    else
        return 1;
}

template <typename Stack>
void merge_sort(Stack& s)
{
    if (s.size() == 1)
    {
        return;
    }
    Stack left_half_stack;
    Stack right_half_stack;
    Stack tmp;
    for (int i = 0; i < s.size() / 2; i++)
    {
        move_top_stack_to_stack(s, left_half_stack);
    }
    while (s.size())
    {
        move_top_stack_to_stack(s, right_half_stack);
    }

    merge_sort(left_half_stack);
    merge_sort(right_half_stack);
    merge_stacks_to(left_half_stack, right_half_stack, tmp);
    from_stack_to_stack(tmp, s);
}

template<typename Stack>
void natural_merge_sort(Stack& s)
{
    if (s.size() <= 1) return;

    Stack tmp1, tmp2, res;
    int count = 0;
    while (count != 1)
    {
        count = 0;
        while (s.size())
        {
            mov_elems_from_stack_to_stack(s, tmp1);
            mov_elems_from_stack_to_stack(s, tmp2);
            merge_stacks_to(tmp1, tmp2, res);
            count++;
        }
        swap(res, s);
    }
}

template <typename T>
std::optional<T> find_major_elem(const std::vector<T>& sequence)
{
    stackM<T> dest;
    int count = 0;
    for (const auto& item : sequence)
    {
        if (!dest.size())
        {
            dest.push(item);
        }
        else if (dest.top() == item)
        {
            dest.push(item);
        }
        else
        {
            dest.pop();
        }
    }
    if (!dest.size())
    {
        return std::nullopt;
    }
    for (auto item : sequence)
    {
        if (dest.top() == item)
        {
            count++;
        }
    }
    if (count > sequence.size() / 2)
    {
        return dest.top();
    }
}


using graph_s = std::vector<std::set<int>>;
using graph_v = std::vector<std::vector<int>>;

std::vector<int> euler_path(const graph_s& G)
{
    graph_s g = G;
    std::stack<int> s;
    std::vector<int> out;
    int startVertex = (find_if(g.begin(), g.end(),
        [](auto& lst) {return lst.size() % 2; }) - g.begin()) % g.size();
    s.push(startVertex);

    while (!s.empty()) {
        int w = s.top();

        if (g[w].empty()) {
            out.push_back(s.top());
            s.pop();
        }
        else
        {
            s.push(*g[w].begin());
            g[w].erase(s.top());
            g[s.top()].erase(w);
        }
    }
    return out;
}


int main()
{

    std::stack<int> newStack1;

    for (int i = 0; i < 50000; i++)
    {
        newStack1.push(rand());
    }
    unsigned int start_time = clock(); // ?????????????????? ??????????
    natural_merge_sort(newStack1);
    unsigned int end_time = clock(); // ???????????????? ??????????
    unsigned int search_time = end_time - start_time; // ?????????????? ??????????
    //print_stack(newStack1);
    std::cout << end_time - start_time;
    //merge_stack(newStack1, newStack2);
    //print_stack(newStack1);
    //merge_sort(newStack1);
    //print_stack(newStack1);
    /*auto res = find_major_elem(newVect);
    if (res)
    {
        std::cout << *res;
    }
    else
    {
        std::cout << "not found";
    }*/
    //std::cout << find_the_volume(newVect);
    /*std::vector<int> a = { 10,9,8,6,7,10 };
    double b;
    b = block_stone(a);
    std::cout << b;*/
}
