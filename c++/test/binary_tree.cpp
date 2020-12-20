#include <iostream>
#include "../myheaders/binary_tree.h"

using namespace std;

// template<class E>
// void visit(Binary_Tree<E>* p)
// {
//     cout << p->val << " ";
// }

int main()
{
    auto root = new Binary_Tree<int>(1);
    root->left = new Binary_Tree<int>(2);
    root->right = new Binary_Tree<int>(3);
    root->left->left = new Binary_Tree<int>(4);
    root->left->right = new Binary_Tree<int>(5);
    root->right->left = new Binary_Tree<int>(6);
    root->right->right = new Binary_Tree<int>(7);
    root->right->right->right = new Binary_Tree<int>(8);

    // postorder_with_flag(visit, root);
    // cout << Is_Complete_Binary_Tree(root);
    // preorder_sparrow(visit, root);

    // cout << wangdao5_5(visit, root);

    // vector<int> preorder, inorder;
    // preorder = {1,2,4,5,3,6,7};
    // inorder = {4,2,5,1,6,3,7};
    // Binary_Tree<int>* tree;
    // tree = wangdao5_6(preorder, inorder);
    // levelorder(visit, tree);
    
    // cout << wangdao5_8_recursion(root);

    // wangdao5_9(root);
    // levelorder(visit, root);

    // int k = 4;
    // wangdao5_10(visit, root, k);

    // wangdao5_11(root, 7);
    // levelorder(visit, root);

    // wangdao5_12(visit, root, 8);
    // wangdao5_12_recur(visit, root, 8);

    //5.13
    // visit(wangdao5_13_recur(visit, root, root->left->left, root->left->right));
    
    //5.14
    // cout << wangdao5_14(root);

    //5.15
    // vector<int> preorder = {1,2,4,5,3,6,7};
    // vector<int> postorder(7);
    // wangdao5_15(preorder, postorder);

    //5.16
    // Binary_Tree<int>* head = wangdao5_16(root);
    // Binary_Tree<int>* p = head;
    // while(p){
    //     cout << p->val << ' ';
    //     p = p->right;
    // }

    // cout << maxDepth(root);

    cout << endl;
    system("pause");
    return 0;
}