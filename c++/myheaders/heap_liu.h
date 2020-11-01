#define MinData (-32767)

template <class E>
class Heap
{
private:
    int capacity;
    int size;
    E *elements;

public:
    Heap(int maxelements);
    Heap(int maxelements, int size, E e[]);
    ~Heap();

    bool isempty();
    bool isfull();
    bool insert(E x);
    bool deletemin(E &x);
    E findmin();
    void show(void (*visit)(E));
    bool isminheap();
};

template <class E>
Heap<E>::Heap(int maxelements)
{
    size = 0;
    capacity = maxelements;
    elements = new E[maxelements];
    elements[0] = MinData;
}

template <class E>
Heap<E>::Heap(int maxelements, int size, E e[])
{
    this->size = 0;
    capacity = maxelements;
    elements = new E[maxelements];
    elements[0] = MinData;

    for (int i = 0; i < size; i++)
    {
        insert(e[i]);
    }
}

template <class E>
Heap<E>::~Heap()
{
    delete[] elements;
}

template <class E>
bool Heap<E>::isempty()
{
    return size == 0;
}

template <class E>
bool Heap<E>::isfull()
{
    return size == capacity;
}

template <class E>
bool Heap<E>::insert(E x)
{
    int i;
    if (isfull())
        return false;
    for (i = ++size; elements[i / 2] > x; i /= 2) // 小根堆要把较大父亲下移，即上滤（空泡从最后位置上升）
        elements[i] = elements[i / 2];
    elements[i] = x;
    return true;
}

template <class E>

bool Heap<E>::deletemin(E &x)
{
    int i, child;
    E minelement, lastelement;

    if (isempty())
        return false;
    minelement = elements[1];
    lastelement = elements[size--];

    for (i = 1; i * 2 <= size; i = child)
    {
        child = i * 2;
        if (child != size && elements[child + 1] < elements[child]) // 小根堆要把较小孩子上移，即下滤（空泡从根下沉）
            child++;
        if (lastelement > elements[child])
            elements[i] = elements[child];
        else
            break;
    }
    elements[i] = lastelement;
    x = minelement;
    return true;
}

template <class E>
E Heap<E>::findmin()
{
    if (!isempty())
        return elements[1];
    return elements[0];
}

template <class E>
void Heap<E>::show(void (*visit)(E))
{
    for (int i = 1; i < size; i++)
    {
        visit(elements[i]);
    }
}

template <class E>
bool Heap<E>::isminheap()
{
    int i;
    if (size % 2 == 0)
    {
        if (elements[size / 2] > elements[size])
            return false;
        for (i = size / 2; i >= 1; i--)
        {
            if (elements[i] > elements[2 * i] || elements[i] > elements[2 * i + 1])
                return false;
        }
    }
    else
    {
        for (i = size / 2; i >= 1; i--)
        {
            if (elements[i] > elements[2 * i] || elements[i] > elements[2 * i + 1])
                return false;
        }
    }
    return true;
}