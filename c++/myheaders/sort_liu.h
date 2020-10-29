#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void insert_sort(int a[], int n)
{                               /* mark first element as sorted */
    for (int i = 1; i < n; i++) /* for each unsorted element tmp */
    {
        // ����i��Ԫ�ش���i-1Ԫ�أ����ô���ֱ�ӷ��������������
        if (a[i] < a[i - 1])
        {
            int tmp = a[i]; /* 'etmptract' the element tmp */
            int j = i;
            // ���Ʊ߽�ͱȽ�
            while (j > 0 && a[j - 1] > tmp) /* for j = lastSortedIndetmp down to 0 */
            {
                a[j] = a[j - 1]; //Ԫ�غ���
                j--;
            }
            a[j] = tmp; //���뵽��ȷλ��
        }
    }
}

void insert_sort_clean(int a[], int n)
{
    int i, j;
    int tmp;

    for (int i = 1; i < n; i++)
    {
        tmp = a[i];
        for (j = i; j > 0 && a[j - 1] > tmp; j--) // ע��߽���������j-1 >= 0����j > 0
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

void insert_sort_bin(int a[], int n)
{
    int i, j, low, high, mid;
    
    for (int i = 1; i < n; i++)
    {
        int tmp = a[i];
        low = 0;
        high = i - 1;
        while (low <= high) // �����Ǳ����䣬������ֹ����Ϊlow = high + 1����[low, high]Ϊ��
        {
            mid = (low + high) / 2;
            if (tmp < a[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (j = i - 1; j >= high + 1; j--) // ע��˴�����ֹ���������Ҫ�����λ����high + 1
        {
            a[j + 1] = a[j];
        }
        a[high + 1] = tmp;
    }
}

void shell_sort(int a[], int n)
{
    // ����ÿ�ζ� / 2
    for (int step = n / 2; step > 0; step /= 2)
    {
        // �ӵ�һ����ǰ�����������鿪ʼ���������������򣨼�step = 1��������0��1��ʼ
        for (int i = step; i < n; i++) // ע�����������Ǳ���[1, n-1]�Ӻ���ǰ�ȽϺ��ƣ�������
        {
            int j = i;
            int tmp = a[j];

            while (j - step >= 0 && a[j - step] > tmp) // ���Ʊ߽�ͱȽ�
            {
                a[j] = a[j - step];
                j = j - step;
            }
            a[j] = tmp;
        }
    }
}

void shell_sort_clean(int a[], int n)
{
    int i, j, Increment;
    int tmp;

    for(Increment = n / 2; Increment > 0; Increment / 2)
    {
        for(i = Increment; i < n; i++)
        {
            tmp = a[i];
            for(j = i; j >= Increment; j -= Increment)
            {
                if(tmp < a[j - Increment])
                    a[j] = a[j - Increment];
                else 
                    break;
            }
        }
    }
}

void bubble_sort(int a[], int n)
{
    bool flag;
    for (int i = 0; i < n - 1; i++)
    {
        flag = false;
        for (int j = n - 1; j > i; j--)
        {
            if (a[j - 1] > a[j])
            {
                swap(a[j - 1], a[j]);
                flag = true;
            }
        }
        if (flag == false)
            return;
    }
}

void bubble_sort_clean(int a[], int n)
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

