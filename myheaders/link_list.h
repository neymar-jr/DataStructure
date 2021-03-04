#include<iostream>
using namespace std;

class Link_List
{
public:
    // 定义链表节点结构体
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int val) : val(val), next(NULL) {}
    };

    // 初始化链表
    Link_List()
    {
        dummyHead = new ListNode(0); // 这里定义的头结点 是一个虚拟头结点，而不是真正的链表头结点
        size = 0;
    }

    // 获取到第index个节点数值，如果index是非法数值直接返回-1， 注意index是从0开始的，第0个节点就是头结点
    int get(int index)
    {
        if (index > (size - 1) || index < 0)
        {
            return -1;
        }
        ListNode *cur = dummyHead->next;
        while (index--)
        { // 如果--index 就会陷入死循环
            cur = cur->next;
        }
        return cur->val;
    }

    // 在链表最前面插入一个节点，插入完成后，新插入的节点为链表的新的头结点
    void addAtHead(int val)
    {
        ListNode *newListNode = new ListNode(val);
        newListNode->next = dummyHead->next;
        dummyHead->next = newListNode;
        size++;
    }

    // 在链表最后面添加一个节点
    void addAtTail(int val)
    {
        ListNode *newListNode = new ListNode(val);
        ListNode *cur = dummyHead;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = newListNode;
        size++;
    }

    // 在第index个节点之前插入一个新节点，例如index为0，那么新插入的节点为链表的新头节点。
    // 如果index 等于链表的长度，则说明是新插入的节点为链表的尾结点
    // 如果index大于链表的长度，则返回空
    void addAtIndex(int index, int val)
    {
        if (index > size)
        {
            return;
        }
        ListNode *newListNode = new ListNode(val);
        ListNode *cur = dummyHead;
        while (index--)
        {
            cur = cur->next;
        }
        newListNode->next = cur->next;
        cur->next = newListNode;
        size++;
    }

    // 删除第index个节点，如果index 大于等于链表的长度，直接return，注意index是从0开始的
    void deleteAtIndex(int index)
    {
        if (index >= size || index < 0)
        {
            return;
        }
        ListNode *cur = dummyHead;
        while (index--)
        {
            cur = cur->next;
        }
        ListNode *tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        size--;
    }

    // 打印链表
    void printLinkedList()
    {
        ListNode *cur = dummyHead;
        while (cur->next != NULL)
        {
            cout << cur->next->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }

    

private:
    int size;
    ListNode *dummyHead;
};