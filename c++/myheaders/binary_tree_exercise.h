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

// 统计二叉树中度为1的节点个数


// 统计二叉树中度为2的节点个数


// 统计二叉树中度为0的节点个数


// 统计二叉树的树高


// 统计二叉树的宽度


// 从二叉树中删去所有叶节点


// 计算指定节点*p所在的层次


// 计算二叉树中各节点中的最大元素的值


// 交换二叉树中每个节点的两个子女


// 以先序次序输出一棵二叉树中所有节点的数据值及节点所在层次