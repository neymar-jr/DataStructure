#include <iostream>
#include "../myheaders/thread_tree.h"

using namespace std;

int main()
{
    auto head = new Thread_Tree<int>(0);
    auto tree = new Thread_Tree<int>(1);
    head->lchild = tree;
    Thread_Tree<int>* pre = head;

    tree->lchild = new Thread_Tree<int>(2);
    tree->rchild = new Thread_Tree<int>(3);
    tree->lchild->lchild = new Thread_Tree<int>(4);
    tree->lchild->rchild = new Thread_Tree<int>(5);
    tree->rchild->lchild = new Thread_Tree<int>(6);
    tree->rchild->rchild = new Thread_Tree<int>(7);
    tree->rchild->rchild->rchild = new Thread_Tree<int>(8);

    inthread(tree, pre);
    pre->rchild = head;
    pre->rtag = 1;
    
    traverse(tree);
    cout << endl;

    system("pause");
    return 0;
}