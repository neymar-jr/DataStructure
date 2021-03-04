#include<iostream>
#include"../myheaders/search.h"
using namespace std;

int main()
{
    const int n = 11;
    int a[] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << Binary_Search(a, n, 5);
    cout << endl;
    system("pause");
    return 0;
}