#include <iostream>
#include "../myheaders/binary_tree_exercise.h"

using namespace std;

void dfs(TreeNode* root){
    if(!root)
        return;
    cout << root->val;
    dfs(root->left);
    dfs(root->right);
}

int main()
{
    auto root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->right->right->right = new TreeNode(8);

    // cout << f1(root);
    // cout << f2(root);
    // cout << f3(root);
    // cout << f4(root);
    // cout << f5(root);
    cout << f5_clean(root);
    // dfs(root);
    
    cout << endl;
    system("pause");
    return 0;
}