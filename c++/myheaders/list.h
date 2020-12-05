class SqList
{
private:
    /* data */
public:
    int *data;
    int maxsize;
    int length;

    SqList(int maxsize);
    bool Insert(int i, int e);
    bool Delete(int i, int &e);
    int Locate(int e);
    ~SqList();
};

SqList::SqList(int maxsize)
{
    data = new int[maxsize];
    this->maxsize = maxsize;
    length = 0;
}

SqList::~SqList()
{
}
/* 
线性表的插入

1.注意边界，数组下标0->length-1，可插入的位置有length+1个
2.注意判满
3.从右往左遍历后移
 */
bool SqList::Insert(int i, int e)
{
    if (i < 0 || i > length)
        return false;
    if (length >= maxsize)
        return false;
    for (int j = length - 1; j > i; j--)
        data[j + 1] = data[j];
    data[i] = e;
    length++;
    return true;
}
/* 
线性表的删除

1.注意删除下标范围0->length-1
2.从左往右遍历前移
 */
bool SqList::Delete(int i, int &e)
{
    if (i < 0 || i > length - 1)
        return false;
    e = data[i - 1];
    for (int j = i; j < length - 1; j++)
        data[j] = data[j + 1];
    length--;
    return true;
}

int SqList::Locate(int e)
{
    for(int i = 0;i<length;i++)
    {
        if(data[i] == e)
            return i;
    }
    return maxsize;
}

