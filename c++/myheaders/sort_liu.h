#include <iostream>
#define leftchild(i) (2 * (i) + 1)
#define MAX_SIZE 100
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
        for (j = i; j - 1 >= 0 && a[j - 1] > tmp; j--) // 注意边界条件，是j-1 >= 0，即j > 0
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

/* 每次把最小的元素交换到数组左边 */
/* 总共迭代n-1次，最后一个元素也就确定了 */
void bubble_sort_clean(int a[], int n)
{
    int i, j;
    bool flag = true;
    for (i = 0; i < n - 1 && flag; i++) /* 如果flag为true则退出循环 */
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

int partition(int a[], int low, int high)
{
    int pivotkey;

    pivotkey = a[low]; /* 用子表的第一个记录作枢纽记录 */
    while (low < high) /* 从表的两端交替向中间扫描 */
    {
        while (low < high && a[high] >= pivotkey)
            high--;
        swap(a[low], a[high]); /* 将比枢纽记录小的记录交换到低端 */
        while (low < high && a[low] <= pivotkey)
            low++;
        swap(a[low], a[high]); /* 将比枢纽记录大的记录交换到高端 */
    }
    /* 终止条件是low == high，因为所有的循环都判断low < high */

    return low; /* 返回枢纽所在位置 */
}

int partition_optimize(int a[], int low, int high)
{
    int pivotkey;
    int tmp;
    int mid = low + (high - low) / 2;

    /* 着重分析一下三数排序。（先确定最小值，剩下两个一比较就能确定第二大还是第三大了）
    核心思想是先通过a[mid]和a[low]，a[mid]和a[high]的比较和交换,使a[mid]是三数中最小值
    最后只需要比较a[low]和a[high]，把较小的值放在a[low]，三个数大小顺序就是2，1，3
    */

    // if (a[mid] > a[low])
    //     swap(a[mid], a[low]);
    // if (a[mid] > a[high])
    //     swap(a[mid], a[high]);
    // if (a[low] > a[high])
    //     swap(a[low], a[high]);

    pivotkey = a[low]; /* 用子表的第一个记录作枢纽记录 */
    tmp = pivotkey;
    while (low < high) /* 从表的两端交替向中间扫描 */
    {
        while (low < high && a[high] >= pivotkey)
            high--;
        a[low] = a[high];
        while (low < high && a[low] <= pivotkey)
            low++;
        a[high] = a[low];
    }
    a[low] = tmp;
    return low; /* 返回枢纽所在位置 */
}

void qsort(int a[], int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = partition(a, low, high);

        qsort(a, low, pivot - 1);
        qsort(a, pivot + 1, high);
    }
}

void quick_sort(int a[], int n)
{
    qsort(a, 0, n - 1);
}

void quick_sort_clean(int a[], int left, int right)
{
    if (left > right)   //递归边界别忘了
        return;

    int pivot;
    int i, j;

    pivot = a[left];
    i = left;
    j = right - 1;

    swap(a[left], a[right]); //枢纽元即第一个元素与最后一个元素交换，使得枢纽元离开要被分割的数据段
    for (;;)
    {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i < j)
            swap(a[i], a[j]);
        else
            break;
    }
    swap(a[i], a[right]);   //把枢纽元放到最终有序数组的位置即i的位置

    quick_sort_clean(a, left, i - 1);   //i位置确定，左递归右递归
    quick_sort_clean(a, i + 1, right);
}

void select_sort(int a[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < min)
                min = j;
        }
        if (i != min)
            swap(a[i], a[min]);
    }
}

// 建小根堆，下滤
void percdown_minroot(int a[], int i, int n)
{
    int child;
    int tmp;
    // 从最后一个有孩子的节点开始调整
    for (tmp = a[i]; leftchild(i) < n; i = child)
    {
        child = leftchild(i);
        if (child != n - 1 && a[child + 1] > a[child]) // 双孩子情况下选中较大孩子
            child++;
        if (tmp < a[child])
            a[i] = a[child];
        else
            break;
    }
    a[i] = tmp;
}

// 建大根堆，下滤(下滤是指把元素往下层赋值)
void percdown_maxroot(int a[], int i, int n)
{
    int child;
    int tmp;
    // 从最后一个有孩子的节点开始调整
    for (tmp = a[i]; leftchild(i) < n; i = child)   // 下滤到合适位置
    {
        child = leftchild(i);
        if (child != n - 1 && a[child + 1] < a[child])  // 双孩子情况下选中较小孩子
            child++;
        if (tmp > a[child])
            a[i] = a[child];    // 由于当前节点由tmp缓存了，所以不担心当前值被覆盖
        else
            break;
    }
    a[i] = tmp; // 填入下滤找到的位置
}

void heap_sort(int a[], int n)
{
    int i;

    for (i = n / 2 - 1; i >= 0; i--) /* BuildHeap */
    {
        percdown_maxroot(a, i, n);
    }
    for (i = n - 1; i > 0; i--) /* DeleteMax */
    {
        swap(a[0], a[i]);   // 堆顶最小值和最后一个元素交换
        percdown_maxroot(a, 0, i);  // 调整堆，保证堆顶最小，每次i都是堆最后一个节点
    }
}

/* 
    核心思想：
    用三个指针，p1指向第一个数组的头，p2指向第二个数组的头，p3指向缓冲数组的头
    然后逐个比较p1和p2指向的元素大小，记pmin = min{p1, p2}，pmin指向元素赋给p3，pmin++，p3++
    循环终止条件是p1或p2有一个遍历到终点
    直接再加两个循环，while(p1 <= length1) 复制，while(p2 <= length2) 复制
    由于我们没有保存循环终止时p1和p2的值，所以不知道是哪个数组遍历到终点了
    折中的方案是最开始记录第一个数组和第二个数组元素个数之和
    RightEnd一直没有修改过，从RightEnd开始从后向前遍历，逐个覆盖原数组，成有序数组 
 */

void Merge(int a[], int tmpa[], int L, int R, int RightEnd)
{
    int LeftEnd = R - 1;
    int tmp = L;
    int NumElements = RightEnd - L + 1;
    while (L <= LeftEnd && R <= RightEnd)
    {
        if (a[L] <= a[R])
            tmpa[tmp++] = a[L++];
        else
            tmpa[tmp++] = a[R++];
    }
    while (L <= LeftEnd)
        tmpa[tmp++] = a[L++];
    while (R <= RightEnd)
        tmpa[tmp++] = a[R++];
    for (int i = 0; i < NumElements; i++, RightEnd--)
        a[RightEnd] = tmpa[RightEnd];
}

/* 
    类似二分法，其实就是二分递归，递归到边界之后再归并回来
 */
void MSort(int a[], int tmpa[], int L, int RightEnd)
{
    int Center;
    if (L < RightEnd)
    {
        Center = (L + RightEnd) / 2;
        MSort(a, tmpa, L, Center);
        MSort(a, tmpa, Center + 1, RightEnd);
        Merge(a, tmpa, L, Center + 1, RightEnd); // 注意这里是Center+1开始
    }
}

void merge(int a[], int TmpArray[], int Lpos, int Rpos, int RightEnd)
{
    int i, LeftEnd, NumElements, TmpPos;

    LeftEnd = Rpos - 1;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;

    /* main loop */
    while (Lpos <= LeftEnd && Rpos <= RightEnd)
        if (a[Lpos] <= a[Rpos])
            TmpArray[TmpPos++] = a[Lpos++];
        else
            TmpArray[TmpPos++] = a[Rpos++];

    while (Lpos <= LeftEnd) /* Copy rest of first half */
        TmpArray[TmpPos++] = a[Lpos++];
    while (Rpos <= RightEnd) /* Copy rest of second half */
        TmpArray[TmpPos++] = a[Rpos++];

    /* Copy TmpArray back */
    for (i = 0; i < NumElements; i++, RightEnd--)
        a[RightEnd] = TmpArray[RightEnd];
}

void msort(int a[], int TmpArray[], int left, int right)
{
    int center;

    if (left < right)
    {
        center = (left + right) / 2;
        msort(a, TmpArray, left, center);
        msort(a, TmpArray, center + 1, right);
        merge(a, TmpArray, left, center + 1, right);
    }
}

void merge_sort(int a[], int n)
{
    int *TmpArray = new int[MAX_SIZE];
    msort(a, TmpArray, 0, n - 1);
    delete[] TmpArray;
}

// 双向冒泡排序
void wangdao8_2(int a[], int n)
{
    int i;
    int low = 0, high = n - 1;
    bool flag = true;
    while (low < high && flag)
    {
        flag = false;
        for (i = low; i < high; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                flag = true;
            }
        }
        high--;
        for (i = high; i > low; i--)
        {
            if (a[i] < a[i - 1])
            {
                swap(a[i], a[i - 1]);
                flag = true;
            }
        }
        low++;
    }
}

// 把所有奇数移动到所有偶数前边
// 核心思想：先从前向后找到一个偶数元素，在从后向前找到一个奇数元素，将二者交换，重复直至i >= j
void wangdao8_3(int a[], int n)
{
    int i = 0, j = n - 1;
    while (i < j)
    {
        while (i < j && a[i] % 2 != 0)
            i++;
        while (i < j && a[j] % 2 != 1)
            j--;
        if (i < j)
            swap(a[i], a[j]);
        i++;
        j--;
    }
}

// 找乱序数组中的第k小数
int wangdao8_6(int a[], int low, int high, int k)
{
    int pivot = a[low];
    int low_temp = low;
    int high_temp = high;
    while (low < high)
    {
        while (low < high && a[high] >= pivot)
            --high;
        a[low] = a[high];
        while (low < high && a[low] <= pivot)
            ++low;
        a[high] = a[low];
    }
    // 终止情况下 low == high 都代表pivot应该放在有序数组的位置
    a[low] = pivot;

    if (low == k)
        return a[low];
    else if (low > k)
        return wangdao8_6(a, low_temp, low - 1, k);
    else
        return wangdao8_6(a, low + 1, high_temp, k);
}