#include<iostream>
using namespace std;

class Link_List
{
public:
    // ��������ڵ�ṹ��
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int val) : val(val), next(NULL) {}
    };

    // ��ʼ������
    Link_List()
    {
        dummyHead = new ListNode(0); // ���ﶨ���ͷ��� ��һ������ͷ��㣬����������������ͷ���
        size = 0;
    }

    // ��ȡ����index���ڵ���ֵ�����index�ǷǷ���ֱֵ�ӷ���-1�� ע��index�Ǵ�0��ʼ�ģ���0���ڵ����ͷ���
    int get(int index)
    {
        if (index > (size - 1) || index < 0)
        {
            return -1;
        }
        ListNode *cur = dummyHead->next;
        while (index--)
        { // ���--index �ͻ�������ѭ��
            cur = cur->next;
        }
        return cur->val;
    }

    // ��������ǰ�����һ���ڵ㣬������ɺ��²���Ľڵ�Ϊ������µ�ͷ���
    void addAtHead(int val)
    {
        ListNode *newListNode = new ListNode(val);
        newListNode->next = dummyHead->next;
        dummyHead->next = newListNode;
        size++;
    }

    // ��������������һ���ڵ�
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

    // �ڵ�index���ڵ�֮ǰ����һ���½ڵ㣬����indexΪ0����ô�²���Ľڵ�Ϊ�������ͷ�ڵ㡣
    // ���index ��������ĳ��ȣ���˵�����²���Ľڵ�Ϊ�����β���
    // ���index��������ĳ��ȣ��򷵻ؿ�
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

    // ɾ����index���ڵ㣬���index ���ڵ�������ĳ��ȣ�ֱ��return��ע��index�Ǵ�0��ʼ��
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

    // ��ӡ����
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