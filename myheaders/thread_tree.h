#include<iostream>
using namespace std;

template<class E>
class Thread_Tree
{
private:
    /* data */
public:
    E data;
    Thread_Tree* lchild;
    Thread_Tree* rchild;
    int ltag;
    int rtag;

    Thread_Tree(E e);
    ~Thread_Tree();
};

template<class E>
Thread_Tree<E>::Thread_Tree(E e)
{
    data = e;
    lchild = nullptr;
    rchild = nullptr;
    ltag = 0;
    rtag = 0;
}
template<class E>
Thread_Tree<E>::~Thread_Tree()
{
}

template<class E>
void inthread(Thread_Tree<E>* p, Thread_Tree<E>* &pre)
{
    if(p){   //p不为空是建立线索的前提
        inthread(p->lchild, pre);   //递归，线索化左子树
        if(p->lchild == nullptr){   //左子树为空，建立前驱线索
            p->lchild = pre;
            p->ltag = 1;
        }
        if(pre != nullptr && pre->rchild == nullptr){   
            pre->rchild = p;    //建立前驱节点的后继线索
            pre->rtag = 1;
        }
        pre = p;    //标记当前节点为刚刚访问过的节点
        inthread(p->rchild, pre);   //递归，线索化右子树
    }
}

template<class E>
Thread_Tree<E>* firstnode(Thread_Tree<E>* root){
    while(root->ltag == 0) root = root->lchild;
    return root;
}

template<class E>
Thread_Tree<E>* nextnode(Thread_Tree<E>* root){
    if(root->rtag == 0) return firstnode(root->rchild);
    else return root->rchild;
}

template<class E>
void traverse(Thread_Tree<E>* root){
    for(Thread_Tree<E>* p = firstnode(root); p != nullptr; p = nextnode(p)) 
        cout << p->data;
}
