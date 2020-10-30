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
        // 若第i个元素大于i-1元素，不用处理，直接放在有序序列最后
        if (a[i] < a[i - 1])
        {
            int tmp = a[i]; /* 'etmptract' the element tmp */
            int j = i;
            // 限制边界和比较
            while (j > 0 && a[j - 1] > tmp) /* for j = lastSortedIndetmp down to 0 */
            {
                a[j] = a[j - 1]; //元素后移
                j--;
            }
            a[j] = tmp; //插入到正确位置
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
        for (j = i; j > 0 && a[j - 1] > tmp; j--) // 注意边界条件，是j-1 >= 0，即j > 0
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
        while (low <= high) // 由于是闭区间，所以终止条件为low = high + 1，即[low, high]为空
        {
            mid = (low + high) / 2;
            if (tmp < a[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (j = i - 1; j >= high + 1; j--) // 注意此处的终止条件，最后要插入的位置是high + 1
        {
            a[j + 1] = a[j];
        }
        a[high + 1] = tmp;
    }
}

void shell_sort(int a[], int n)
{
    // 增量每次都 / 2
    for (int step = n / 2; step > 0; step /= 2)
    {
        // 从第一个有前驱的增量数组开始遍历，类别插入排序（即step = 1）的跳过0从1开始
        for (int i = step; i < n; i++) // 注意插入排序就是遍历[1, n-1]从后往前比较后移，最后插入
        {
            int j = i;
            int tmp = a[j];

            while (j - step >= 0 && a[j - step] > tmp) // 限制边界和比较
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

    for (Increment = n / 2; Increment > 0; Increment / 2)
    {
        for (i = Increment; i < n; i++)
        {
            tmp = a[i];
            for (j = i; j >= Increment; j -= Increment)
            {
                if (tmp < a[j - Increment])
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
    int i, j;
    bool flag = true;
    for (i = 1; i < n && flag; i++) /* 如果flag为true则退出循环 */
    {
        flag = false; /* 初始为false */
        for (j = n - 1; j > i; j--)
        {
            if (a[j - 1] > a[j])
            {
                swap(a[j - 1], a[j]);
                flag = true; /* 如果有数据交换，则flag为true */
            }
        }
    }
}

void bubble_sort_init1(int a[], int n)
{
    int i, j;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
                swap(a[i], a[j]);
        }
    }
}

void bubble_sort_init2(int a[], int n)
{
    int i, j;
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 2; j >= i; j--)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

int partition(int a[], int low, int high)
{
    int pivotkey;
    int mid = low + (high - low) / 2;

    /* 着重分析一下三数排序。（先确定最小值，剩下两个一比较就能确定第二大还是第三大了）
    核心思想是先通过a[mid]和a[low]，a[mid]和a[high]的比较和交换,使a[mid]是三数中最小值
    最后只需要比较a[low]和a[high]，把较小的值放在a[low]，三个数大小顺序就是2，1，3
    */
    if(a[mid] > a[low])
        swap(a[mid], a[low]);
    if(a[mid] > a[high])
        swap(a[mid], a[high]);
    if(a[low] > a[high])
        swap(a[low], a[high]);

    pivotkey = a[low];      /* 用子表的第一个记录作枢纽记录 */
    while(low < high)       /* 从表的两端交替向中间扫描 */
    {
        while(low < high && a[high] >= pivotkey)    
            high--;
        swap(a[low], a[high]);      /* 将比枢纽记录小的记录交换到低端 */
        while(low < high && a[low] <= pivotkey)     
            low++;
        swap(a[low], a[high]);      /* 将比枢纽记录大的记录交换到高端 */
    }
    /* 终止条件是low == high，因为所有的循环都判断low < high */

    return low;                     /* 返回枢纽所在位置 */
}

int partition_optimize(int a[], int low, int high)
{
    int pivotkey;
    int tmp;
    int mid = low + (high - low) / 2;

    if(a[mid] > a[low])
        swap(a[mid], a[low]);
    if(a[mid] > a[high])
        swap(a[mid], a[high]);
    if(a[low] > a[high])
        swap(a[low], a[high]);

    pivotkey = a[low];      /* 用子表的第一个记录作枢纽记录 */
    tmp = pivotkey;
    while(low < high)       /* 从表的两端交替向中间扫描 */
    {
        while(low < high && a[high] >= pivotkey)    
            high--;
        a[low] = a[high];
        while(low < high && a[low] <= pivotkey)     
            low++;
        a[high] = a[low];
    }
    a[low] = tmp;
    return low;     /* 返回枢纽所在位置 */
}

void qsort(int a[], int low, int high)
{
    int pivot;
    if(low < high)
    {
        pivot = partition_optimize(a, low ,high);

        qsort(a, low, pivot - 1);
        qsort(a, pivot + 1, high);
    }
}

void quick_sort(int a[], int n)
{
    qsort(a, 0, n - 1);
}

