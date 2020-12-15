#include <vector>
#include <stack>

using namespace std;

class Binary_Tree
{
private:
    /* data */
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
    left = nullptr;
    right = nullptr;
}

Binary_Tree::~Binary_Tree()
{
}

void dfs(Binary_Tree *root, int sum, vector<int> &v)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        v.push_back(sum + root->val);
    }
    dfs(root->left, sum + root->val, v);
    dfs(root->right, sum + root->val, v);
    return;
}