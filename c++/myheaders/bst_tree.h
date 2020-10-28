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
        delete (root); // ����������ص��Ƿ��ʵ�ǰ�ڵ�ʱ����֤�������ѷ��ʡ��������ѿ�
    }
    return nullptr;
}

Bst_Tree *Find(int x, Bst_Tree *root)
{
    if (!root)
        return nullptr; // ������Ҷ�ڵ�ĺ��ӣ����Ѿ���·������Ҳ�Ҳ������򷵻ؿ�ָ��
    if (x < root->val)
        return Find(x, root->left);
    else if (x > root->val)
        return Find(x, root->right);
    else
        return root; // x�Ȳ����ڵ�ǰ�ڵ��ֵ��Ҳ��С�ڵ�ǰ�ڵ��ֵ��������
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

Bst_Tree* Delete(int x, Bst_Tree* root)
{
    Bst_Tree* temp;
    if(!root) return nullptr;
    else if(x < root->val){ /* Go left */
        root->left = Delete(x, root->left);
    }
    else if(x > root->val){ /* Go right */
        root->right = Delete(x, root->right);
    }
    /* Found element to be deleted */
    else if(root->left && root->right){
        /* Replace with smallest in right subtree */
        temp = FindMin(root->right);    /* FindMin�Ѿ��ߵ�������ˣ������滻�Ľڵ�ֻ���������1.ֻ���Һ��� 2.���Һ��Ӷ�û�� */
        root->val = temp->val;
        root->right = Delete(root->val, root->right);
    }
    else /* One or zero children */
    {
        temp = root;
        if(root->left == nullptr){  /* Also handles 0 children �Һ���ҲΪnullptr���ÿ� */
            root = root->right;
        }
        else if(root->right == nullptr){
            root = root->left;
        }
        delete(temp);
    }
    return root;
}

int Height(Bst_Tree* root)
{
    if(!root) return 0;
    else return 1 + (Height(root->left) > Height(root->right) ? Height(root->left) : Height(root->right));
}