#define MinData (-32767)

template<class E>
class Heap
{
private:
    int capacity;
    int size;
    E* elements;
public:
    Heap(int maxelements);
    ~Heap();

    bool isempty();
    bool isfull();
    bool insert(E x);
    bool deletemin(E &x);
};

template<class E>
Heap<E>::Heap(int maxelements)
{
    size = 0;
    capacity = maxelements;
    elements = new E[maxelements];
    elements[0] = MinData;
}

template<class E>
Heap<E>::~Heap()
{
    delete[] elements;
}

template<class E>
bool Heap<E>::isempty()
{
    return size == 0;
}

template<class E>
bool Heap<E>::isfull()
{
    return size == capacity;
}

template<class E>
bool Heap<E>::insert(E x)
{
    
}
