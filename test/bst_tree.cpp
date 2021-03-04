#include <iostream>
#include <vector>
#include "../myheaders/bst_tree.h"

using namespace std;

void visit(Bst_Tree* p)
{
    if(!p) return;
    cout << p->val << endl;
}

void dfs(Bst_Tree* root)
{
    if(!root) return;
    cout << root->val << ' ';
    dfs(root->left);
    dfs(root->right);
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    int pre = -32767;
    int balance, h;
    Bst_Tree *root;
    Create(v, root);
    dfs(root);
    cout << endl;
    
    visit(FindMin(root));
    visit(FindMax(root));
    visit(Find(8, root));
    cout << Height(root) << endl;
    cout << judge_bst(root, pre) << endl;
    judge_avl(root, balance, h);
    cout << balance <<endl;
    cout << mylevel(root, 3, 1) << endl;
    cout << level(root, root->right->right) << endl;

    dfs_k(root, 4);

    cout << endl;
    system("pause");
    return 0;
}