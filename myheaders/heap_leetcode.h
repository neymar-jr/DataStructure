#include<iostream>
#include<vector>
#define MAX 65535
using namespace std;

class heap_leetcode
{
private:
    vector<int> heap;
    void swim(int pos);
    void sink(int pos);
    
public:
    int top();
    int size();
    void push(int k);
    void pop();

    heap_leetcode(/* args */);
    ~heap_leetcode();
};

heap_leetcode::heap_leetcode(/* args */)
{
    heap.resize(1);
    heap[0] = MAX;
}

heap_leetcode::~heap_leetcode()
{
}

// 上浮
void heap_leetcode::swim(int pos)
{
    while (pos > 1 && heap[pos/2] < heap[pos]) // 注意此处pos > 1因为0处不放数
    {
        swap(heap[pos/2], heap[pos]);
        pos /= 2;
    }
}

// 下沉
void heap_leetcode::sink(int pos)
{
    int N = heap.size();
    while(pos * 2 < N)
    {
        int i = pos * 2;
        if(i < N && heap[i] < heap[i + 1]) ++i; // 找到较大孩子
        if(heap[pos] >= heap[i]) break;
        swap(heap[pos], heap[i]);
        pos = i;
    }
}

int heap_leetcode::top()
{
    return heap[1];
}

int heap_leetcode::size()
{
    return heap.size() - 1;
}

void heap_leetcode::push(int k)
{
    heap.push_back(k);
    swim(heap.size() - 1);
}

void heap_leetcode::pop()
{
    heap[1] = heap.back();
    heap.pop_back();
    sink(1);
}
