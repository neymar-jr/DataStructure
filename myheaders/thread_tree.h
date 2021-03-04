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
    if(p){   //p��Ϊ���ǽ���������ǰ��
        inthread(p->lchild, pre);   //�ݹ飬������������
        if(p->lchild == nullptr){   //������Ϊ�գ�����ǰ������
            p->lchild = pre;
            p->ltag = 1;
        }
        if(pre != nullptr && pre->rchild == nullptr){   
            pre->rchild = p;    //����ǰ���ڵ�ĺ������
            pre->rtag = 1;
        }
        pre = p;    //��ǵ�ǰ�ڵ�Ϊ�ոշ��ʹ��Ľڵ�
        inthread(p->rchild, pre);   //�ݹ飬������������
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
