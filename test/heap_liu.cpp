#include <iostream>
#include "../myheaders/heap_liu.h"

using namespace std;

template <class E>
void visit(E e)
{
    cout << e << " ";
}

int main()
{
    int x;
    int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    auto heap = new Heap<int>(20, 9, a);

    heap->deletemin(x);
    cout << x << endl;
    heap->show(visit);
    cout << endl;

    cout << heap->isminheap() << endl;

    system("pause");
    return 0;
}