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
���Ա�Ĳ���

1.ע��߽磬�����±�0->length-1���ɲ����λ����length+1��
2.ע������
3.���������������
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
���Ա��ɾ��

1.ע��ɾ���±귶Χ0->length-1
2.�������ұ���ǰ��
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

