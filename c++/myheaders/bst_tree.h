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
    left = NULL;
    right = NULL;
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
        delete (root); // ����������ص��Ƿ��ʵ�ǰ�ڵ�ʱ����֤�������ѷ��ʡ��������ѿ�
    }
    return NULL;
}

Bst_Tree *Find(int x, Bst_Tree *root)
{
    if (!root)
        return NULL; // ������Ҷ�ڵ�ĺ��ӣ����Ѿ���·������Ҳ�Ҳ������򷵻ؿ�ָ��
    if (x < root->val)
        return Find(x, root->left);
    else if (x > root->val)
        return Find(x, root->right);
    else
        return root; // x�Ȳ����ڵ�ǰ�ڵ��ֵ��Ҳ��С�ڵ�ǰ�ڵ��ֵ��������
}

Bst_Tree *FindMin_recur(Bst_Tree *root)
{
    if (!root)
        return NULL;
    else if (!root->left)
        return root;
    else
        return FindMin_recur(root->left);
}

Bst_Tree *FindMax_recur(Bst_Tree *root)
{
    if (!root)
        return NULL;
    else if (!root->right)
        return root;
    else
        return FindMax_recur(root->right);
}

Bst_Tree *FindMin(Bst_Tree *root)
{
    if (root)
    {
        while (root->left != NULL)
        {
            root = root->left;
        }
    }
    return root;
}

Bst_Tree *FindMax(Bst_Tree *root)
{
    if (root)
    {
        while (root->right != NULL)
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
    root = NULL;
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
        return NULL;
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
        temp = FindMin(root->right); /* FindMin�Ѿ��ߵ�������ˣ������滻�Ľڵ�ֻ���������1.ֻ���Һ��� 2.���Һ��Ӷ�û�� */
        root->val = temp->val;
        root->right = Delete(root->val, root->right);
    }
    else /* One or zero children */
    {
        temp = root;
        if (root->left == NULL)
        { /* Also handles 0 children �Һ���ҲΪNULL���ÿ� */
            root = root->right;
        }
        else if (root->right == NULL)
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
    �ж�һ���������ǲ��Ƕ�����������˼·�Ƕ��������������������һ���������С�
    ��ˣ��Ը����Ķ��������������������ʼ���ܱ���ǰһ��ֵ�Ⱥ�һ��ֵС����˵���ö�������һ�ö�����������
*/

int judge_bst(Bst_Tree *root, int &pre)
{
    int b1, b2;
    if (!root)
        return 1;
    else
    {
        b1 = judge_bst(root->left, pre); // �������
        if (b1 == 0 || pre >= root->val)
            return 0; // ע������������0���������һ������0��һ���ǵ�ǰֵС�ڵ�����һ��ֵ������������������Ѿ�����һ���������Է��ظ��ݹ����µ��õ�����0
        pre = root->val;
        b2 = judge_bst(root->right, pre);
        return b2;
    }
}

/* �ж϶������Ƿ���ƽ������� */
void judge_avl(Bst_Tree *root, int &balance, int &h)
{
    int bl = 0, br = 0, hl = 0, hr = 0;
    if (root == NULL)
    {
        h = 0;
        balance = 1;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        h = 1;
        balance = 1;
    }
    else
    {
        judge_avl(root->left, bl, hl);
        judge_avl(root->right, br, hr);
        h = (hl > hr ? hl : hr) + 1;
        if (abs(hl - hr) < 2)
        {
            balance = bl && br;
        }
        else
        {
            balance = 0;
        }
    }
}

// ����ֵ���ؽڵ����ڸ߶�
int mylevel(Bst_Tree *root, int x, int num)
{
    if (root == NULL)
        return num;
    if (x < root->val)
        return mylevel(root->left, x, num + 1);
    else if (x > root->val)
        return mylevel(root->right, x, num + 1);
    else
        return num;
}

// ����ָ�뷵�ؽڵ����ڲ��
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

// ���һ���㷨���Ӵ�С�������������������ֵ��С��k�Ĺؼ���
void dfs_k(Bst_Tree* root, int k)
{
    if(!root) return;
    dfs_k(root->right, k);
    if (root->val >= k)
    {
        cout << root->val << ' ';
    }
    dfs_k(root->left, k);
}