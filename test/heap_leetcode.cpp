#include<iostream>
#include "../myheaders/heap_leetcode.h"

using namespace std;

int main()
{
    auto heap = new heap_leetcode();
    for(int i = 0; i < 10; i++)
    {
        heap->push(i);
    }
    for(int i = 0; i < 10; i++)
    {
        cout << heap->top();
        heap->pop();
    }
    system("pause");
    return 0;
}
