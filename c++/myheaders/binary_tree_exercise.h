#include <stack>
#include <queue>
#include <map>

using namespace std;

class Binary_Tree
{
private:
    /* val */
public:
    int val;
    Binary_Tree *left;
    Binary_Tree *right;

    Binary_Tree(int e);
    ~Binary_Tree();
};

Binary_Tree::Binary_Tree(int e)
{
    val = e;
    left = NULL;
    right = NULL;
}


Binary_Tree::~Binary_Tree()
{
}

// ͳ�ƶ������ж�Ϊ1�Ľڵ����


// ͳ�ƶ������ж�Ϊ2�Ľڵ����


// ͳ�ƶ������ж�Ϊ0�Ľڵ����


// ͳ�ƶ�����������


// ͳ�ƶ������Ŀ��


// �Ӷ�������ɾȥ����Ҷ�ڵ�


// ����ָ���ڵ�*p���ڵĲ��


// ����������и��ڵ��е����Ԫ�ص�ֵ


// ������������ÿ���ڵ��������Ů


// ������������һ�ö����������нڵ������ֵ���ڵ����ڲ��