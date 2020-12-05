int Binary_Search(int a[], int n, int x)
{
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x == a[mid])
            return mid;
        else if (x < a[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}