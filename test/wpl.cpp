#include <iostream>
#include <vector>
#include "../myheaders/wpl.h"

using namespace std;
int main()
{
    auto root = new Binary_Tree(1);
    root->left = new Binary_Tree(2);
    root->right = new Binary_Tree(3);
    root->left->left = new Binary_Tree(4);
    root->left->right = new Binary_Tree(5);
    root->right->left = new Binary_Tree(6);
    root->right->right = new Binary_Tree(7);
    root->right->right->right = new Binary_Tree(8);

    vector<int> v;
    dfs(root, 0, v);
    int size = v.size();
    for (int i = 0; i < size; i++)
    {
        cout << v[i] << ' ';
    }

    cout << endl;
    system("pause");
    return 0;
}