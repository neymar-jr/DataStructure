#include <iostream>
#include <vector>

using namespace std;

class Bst_Tree
{
private:
    /* data */
public:
    int val;
    Bst_Tree *left;
    Bst_Tree *right;
    Bst_Tree(int e);
    ~Bst_Tree();
};

Bst_Tree::Bst_Tree(int e)
{
    val = e;
    left = nullptr;
    right = nullptr;
}

Bst_Tree::~Bst_Tree()
{
}

Bst_Tree *MakeEmpty(Bst_Tree *root)
{
    if (!root)
    {
        MakeEmpty(root->left);
        MakeEmpty(root->right);
        delete (root); // 后序遍历，特点是访问当前节点时，保证其子树已访问。即子树已空
    }
    return nullptr;
}

Bst_Tree *Find(int x, Bst_Tree *root)
{
    if (!root)
        return nullptr; // 遍历到叶节点的孩子，即已经将路径走完也找不到，则返回空指针
    if (x < root->val)
        return Find(x, root->left);
    else if (x > root->val)
        return Find(x, root->right);
    else
        return root; // x既不大于当前节点的值，也不小于当前节点的值，即等于
}

Bst_Tree *FindMin(Bst_Tree *root)
{
    if (!root)
        return nullptr;
    else if (!root->left)
        return root;
    else
        return FindMin(root->left);
}

Bst_Tree *FindMax(Bst_Tree *root)
{
    if (root)
    {
        while (root->right)
        {
            root = root->right;
        }
    }

    return root;
}

Bst_Tree *Insert(int x, Bst_Tree *root)
{
    if (!root)
    { /* Create and return a one-node tree */
        root = new Bst_Tree(x);
    }
    else if (x < root->val)
    {
        root->left = Insert(x, root->left);
    }
    else if (x > root->val)
    {
        root->right = Insert(x, root->right);
    }
    /* Else X is in the tree already; we'll do nothing */

    return root;
}

void Create(vector<int> v, Bst_Tree *&root)
{
    root = nullptr;
    int size = v.size();
    for (int i = 0; i < size; i++)
    {
        root = Insert(v[i], root);
    }
}

Bst_Tree *Delete(int x, Bst_Tree *root)
{
    Bst_Tree *temp;
    if (!root)
        return nullptr;
    else if (x < root->val)
    { /* Go left */
        root->left = Delete(x, root->left);
    }
    else if (x > root->val)
    { /* Go right */
        root->right = Delete(x, root->right);
    }
    /* Found element to be deleted */
    else if (root->left && root->right)
    {
        /* Replace with smallest in right subtree */
        temp = FindMin(root->right); /* FindMin已经走到最左边了，所以替换的节点只有两种情况1.只有右孩子 2.左右孩子都没有 */
        root->val = temp->val;
        root->right = Delete(root->val, root->right);
    }
    else /* One or zero children */
    {
        temp = root;
        if (root->left == nullptr)
        { /* Also handles 0 children 右孩子也为nullptr，置空 */
            root = root->right;
        }
        else if (root->right == nullptr)
        {
            root = root->left;
        }
        delete (temp);
    }
    return root;
}

int Height(Bst_Tree *root)
{
    if (!root)
        return 0;
    else
        return 1 + (Height(root->left) > Height(root->right) ? Height(root->left) : Height(root->right));
}

/* 
    判断一个二叉树是不是二叉排序树，思路是二叉排序树的中序遍历是一个有序数列。
    因此，对给定的二叉树进行中序遍历，若始终能保持前一个值比后一个值小，则说明该二叉树是一棵二叉排序树。
 */

int judge(Bst_Tree *root, int &pre)
{
    int b1, b2;
    if (!root)
        return 1;
    else
    {
        b1 = judge(root->left, pre); // 中序遍历
        if (b1 == 0 || pre >= root->val)
            return 0; // 注意左子树返回0的情况，第一个返回0的一定是当前值小于等于上一个值的情况，由于左子树已经存在一个逆序，所以返回给递归向下调用的子树0
        pre = root->val;
        b2 = judge(root->right, pre);
        return b2;
    }
}

int mylevel(Bst_Tree *root, int x, int num)
{
    if (root == nullptr)
        return num;
    if (x < root->val)
        return mylevel(root->left, x, num + 1);
    else if (x > root->val)
        return mylevel(root->right, x, num + 1);
    else
        return num;
}

int level(Bst_Tree *root, Bst_Tree *p)
{
    int n = 0;
    Bst_Tree *cur = root;
    if (cur)
        n++;
    while (1)
    {
        if (p->val < cur->val)
        {
            cur = cur->left;
            n++;
        }
        else if (p->val > cur->val)
        {
            cur = cur->right;
            n++;
        }
        else
            break;
    }
    return n;
}