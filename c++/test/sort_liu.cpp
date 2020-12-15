#include <iostream>
#include "../myheaders/sort_liu.h"

using namespace std;

int main()
{
    const int n = 11;
    int a[] = {5,4,8,2,0,7,9,3,1,6,6};
    // int a[] = {1,1,1,1,1,1,1,1,1,1,1};
    // int a[] = {0,1,2,3,4,5,6,6,7,8,9};
    // int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0};
    
    // bubble_sort(a, n);
    // insert_sort(a, n);
    // insert_sort_clean(a, n);
    // insert_sort_bin(a, n);
    // shell_sort(a, n);
    // quick_sort_clean(a, 0, n-1);
    heap_sort(a, n);

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    cout << endl;

    system("pause");
    return 0;
}