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
    for (i = 1; i < n && flag; i++) /* ���flagΪtrue���˳�ѭ�� */
    {
        flag = false; /* ��ʼΪfalse */
        for (j = n - 1; j > i; j--)
        {
            if (a[j - 1] > a[j])
            {
                swap(a[j - 1], a[j]);
                flag = true; /* ��������ݽ�������flagΪtrue */
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

    /* ���ط���һ���������򡣣���ȷ����Сֵ��ʣ������һ�ȽϾ���ȷ���ڶ����ǵ������ˣ�
    ����˼������ͨ��a[mid]��a[low]��a[mid]��a[high]�ıȽϺͽ���,ʹa[mid]����������Сֵ
    ���ֻ��Ҫ�Ƚ�a[low]��a[high]���ѽ�С��ֵ����a[low]����������С˳�����2��1��3
    */
    if (a[mid] > a[low])
        swap(a[mid], a[low]);
    if (a[mid] > a[high])
        swap(a[mid], a[high]);
    if (a[low] > a[high])
        swap(a[low], a[high]);

    pivotkey = a[low]; /* ���ӱ�ĵ�һ����¼����Ŧ��¼ */
    while (low < high) /* �ӱ�����˽������м�ɨ�� */
    {
        while (low < high && a[high] >= pivotkey)
            high--;
        swap(a[low], a[high]); /* ������Ŧ��¼С�ļ�¼�������Ͷ� */
        while (low < high && a[low] <= pivotkey)
            low++;
        swap(a[low], a[high]); /* ������Ŧ��¼��ļ�¼�������߶� */
    }
    /* ��ֹ������low == high����Ϊ���е�ѭ�����ж�low < high */

    return low; /* ������Ŧ����λ�� */
}

int partition_optimize(int a[], int low, int high)
{
    int pivotkey;
    int tmp;
    int mid = low + (high - low) / 2;

    if (a[mid] > a[low])
        swap(a[mid], a[low]);
    if (a[mid] > a[high])
        swap(a[mid], a[high]);
    if (a[low] > a[high])
        swap(a[low], a[high]);

    pivotkey = a[low]; /* ���ӱ�ĵ�һ����¼����Ŧ��¼ */
    tmp = pivotkey;
    while (low < high) /* �ӱ�����˽������м�ɨ�� */
    {
        while (low < high && a[high] >= pivotkey)
            high--;
        a[low] = a[high];
        while (low < high && a[low] <= pivotkey)
            low++;
        a[high] = a[low];
    }
    a[low] = tmp;
    return low; /* ������Ŧ����λ�� */
}

void qsort(int a[], int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = partition_optimize(a, low, high);

        qsort(a, low, pivot - 1);
        qsort(a, pivot + 1, high);
    }
}

void quick_sort(int a[], int n)
{
    qsort(a, 0, n - 1);
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

void BuildMaxHeap(int a[], int n)
{
    for (int i = n / 2; i > 0; i++) // ���к��ӽڵ�Ľڵ����
    {
        HeapAdjust(a, i, n);
    }
}

void HeapAdjust(int a[], int k, int n) // ��Ԫ��kΪ�����������е���
{
    a[0] = a[k];
    for (int i = 2 * k; i <= n; i *= 2)
    {
        if (i < n && a[i] < a[i + 1])
            i++;
        if (a[0] >= a[i]) // �Ѿ��Ǵ���ѣ��������
            break;
        else
        {
            a[k] = a[i];
            k = i;
        }
    }
    a[k] = a[0];
}

void PercDown(int a[], int i, int n)
{
    
}

// ˫��ð������
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

// �����������ƶ�������ż��ǰ��
// ����˼�룺�ȴ�ǰ����ҵ�һ��ż��Ԫ�أ��ڴӺ���ǰ�ҵ�һ������Ԫ�أ������߽������ظ�ֱ��i >= j
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

// �����������еĵ�kС��
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
    // ��ֹ����� low == high ������pivotӦ�÷������������λ��
    a[low] = pivot;

    if (low == k)
        return a[low];
    else if (low > k)
        return wangdao8_6(a, low_temp, low - 1, k);
    else if (low < k)
        return wangdao8_6(a, low + 1, high_temp, k);
}