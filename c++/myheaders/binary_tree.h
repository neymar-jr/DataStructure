#include <stack>
#include <queue>
#include <map>

using namespace std;

template <class E>
class Binary_Tree
{
private:
    /* val */
public:
    E val;
    Binary_Tree *left;
    Binary_Tree *right;

    Binary_Tree(E e);
    ~Binary_Tree();
};

template <class E>
Binary_Tree<E>::Binary_Tree(E e)
{
    val = e;
    left = NULL;
    right = NULL;
}

template <class E>
Binary_Tree<E>::~Binary_Tree<E>()
{
}

template <class E>
void visit(Binary_Tree<E> *p)
{
    cout << p->val << " ";
}

//总结一下，对于非递归实现树的遍历，前中后都需要使用栈，层次遍历使用队列
//栈大体有两种用途：
//1.保存dfs路径上的所有节点，在遍历到叶子节点时可以通过s.top()回溯，然后自底向上将所有节点访问。
//2.保存dfs路径上的所有尚未访问的岔路口，在dfs遍历过程中，如果有岔路口就加到栈里，在遍历到叶子节点时可以通过s.top()回溯，直接转到最后一个未访问的岔路口。
//3.保存访问结果，用于反转。

template <class E>
void preorder(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    stack<Binary_Tree<E> *> s;
    Binary_Tree<E> *p = root;
    if (!root)
        return;
    while (p || !s.empty())
    {
        if (p)
        {
            visit(p);
            s.push(p); //保存路径上的节点，用于回溯
            p = p->left;
        }
        else
        {
            p = s.top(); //回溯到路径上的最后一个节点，判断其有无未访问的岔路口
            s.pop();
            p = p->right;
        }
    }
}

template <class E>
void preorder_sparrow(void (*visit)(Binary_Tree<E> *bt), Binary_Tree<E> *root)
{
    stack<Binary_Tree<E> *> s;
    Binary_Tree<E> *p = root;
    s.push(NULL);

    while (p != NULL)
    {
        visit(p);
        if (p->rchild) //如果有未访问的岔路口，入栈保存
        {
            s.push(p->rchild);
        }
        if (p->lchild)
        {
            p = p->lchild;
        }
        else
        {
            p = s.top(); //回溯到上个未访问的岔路口
            s.pop();
        }
    }
}

template <class E>
void preorder_recur(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    if (!root)
        return;
    visit(root);
    preorder_recur(visit, root->left);
    preorder_recur(visit, root->right);
}

template <class E>
void inorder(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    stack<Binary_Tree<E> *> s;
    Binary_Tree<E> *p = root;
    if (!root)
        return;
    while (p || !s.empty())
    {
        if (p)
        {
            s.push(p);
            p = p->left;
        }
        else
        {
            p = s.top();
            s.pop();
            visit(p);
            p = p->right;
        }
    }
}

template <class E>
void inorder_recur(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    if (!root)
        return;
    inorder_recur(visit, root->left);
    visit(root);
    inorder_recur(visit, root->right);
}

//王道书上版本
template <class E>
void postorder(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    stack<Binary_Tree<E> *> s;
    Binary_Tree<E> *p = root;
    Binary_Tree<E> *last = NULL;

    while (p || !s.empty())
    {
        if (p)
        {
            s.push(p);
            p = p->left;
        }
        else
        {
            p = s.top();
            if (p->right && p->right != last)
            {
                p = p->right;
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top();
                s.pop();
                visit(p);
                last = p;
                p = NULL; //访问完p的子树，重置p，因为要出栈访问下一个
            }
        }
    }
}

/* 
后序遍历的遍历顺序是左右根。我们是否可以从我们熟悉且简单的前序遍历转化过去后序遍历呢？
答案是可以的。我们可以观察到，可以先求出遍历顺序是根右左的节点序列，再倒序，便刚好是后序遍历的顺序：左右根。
而遍历顺序是根右左的话，很好办，从前序遍历的代码中改两行就是了。所以我们可以选用两个栈，一个用于根右左遍历，一个用于保存序列，最后的代码和前序遍历只是稍作几点修改即可。
*/
template <class E>
void postorder_two_stack(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    stack<Binary_Tree<E> *> s;
    stack<Binary_Tree<E> *> output;
    Binary_Tree<E> *p = root;
    while (p || !s.empty())
    {
        if (p)
        {
            output.push(p); //保存以根->右->左顺序遍历的结果，用于最后出栈以实现反序输出，即左->右->根
            s.push(p);      //保存dfs时路径上未访问完全的节点
            p = p->right;
        }
        else
        {
            p = s.top();
            s.pop();
            p = p->left;
        }
    }
    while (!output.empty())
    {
        visit(output.top());
        output.pop();
    }
}

template <class E>
void postorder_two_stack_sparrow(void (*visit)(Binary_Tree<E> *bt), Binary_Tree<E> *root)
{
    stack<Binary_Tree<E> *> output;
    stack<Binary_Tree<E> *> s; //栈的作用不同，用于保存所有未访问的分叉口
    Binary_Tree<E> *p = root;  //由于一直向单侧走，为了保证回溯时能找到未访问的岔路口，在单侧走时就将岔路口加到栈里。
    s.push(NULL);
    while (p)
    {
        output.push(p);
        if (p->lchild)
        {
            s.push(p->lchild);
        }
        if (p->rchild)
        {
            p = p->rchild;
        }
        else
        {
            p = s.top(); //出栈回溯
            s.pop();
        }
    }
    while (!output.empty())
    {
        visit(output.top());
        output.pop();
    }
}

/* 实际上，我们可以只使用一个栈去模拟后序遍历，但是会比较麻烦。
为了避免问题变得复杂，我们可以先考虑一下能不能借鉴一下前序遍历的思路。
首先，我们很确定的是，后序遍历的开头和前序遍历是可以一样的，都是先经过二叉树的最左分支，直到经过的节点是个叶子节点（没有左右孩子）为止。代码如下：
while(cur!=null) { // 经过所有左节点
    s.push(cur);
    cur = cur.left;
}
接下来很关键，我们得考虑什么时候才能访问节点。
首先我们可以很确定一种情况：发现是叶子节点，必然会访问。
这是第一种情况。我们回想前序遍历和中序遍历的时候，它们经过的路径都是左根右，对于前序和中序来说，访问路径基本上跟经过路径是一致的。
但是在后序遍历中，我们先经过根节点，但是我们不会去访问它，而是会选择先访问它的右子节点。
所以在这种情况下，我们会将根节点留在栈中不弹出，等到需要访问它的时候再出。
那么，什么时候才需要访问根节点呢？答案当然就是访问完右子节点之后了。
我们如何获取这个信息？这并不难，我们可以记录一下上一次访问的节点，然后判断一下当前经过的节点和上一次访问的节点是什么关系就好了。
如果当前经过的节点的右子节点是上一次访问的节点，显然我们需要访问当前节点了。这是第二种情况。

总结起来，我们什么时候才能访问节点。有如下两种情况：

1.当前经过节点是叶子节点。
2.当前经过节点的右孩子节点是上一次访问的节点。

根据这个思路以及借鉴前序遍历的思路，我们可以写出如下代码：
 */
template <class E>
void postorder_one_stack(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    stack<Binary_Tree<E> *> s;
    Binary_Tree<E> *cur = root;
    Binary_Tree<E> *pre = NULL; //用于记录上一次访问的节点

    while (cur || !s.empty())
    {
        while (cur) //保证没有左孩子
        {
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();
        if (cur->right == NULL || cur->right == pre)
        {               // 当前节点没有右孩子,为叶节点即第一种情况
            visit(cur); // 当前节点右孩子是上一次访问的节点即第二种情况
            s.pop();    // 当前节点符合访问条件，所以出栈
            pre = cur;
            cur = NULL; // 相当于让下次循环直接进入回溯过程，为了跳过下一次循环的访问左子节点的过程，直接进入栈的弹出阶段，因为但凡在栈中的节点，它们的左子节点都肯定被经过且已放入栈中。
        }
        else
        {
            cur = cur->right; // 经过右孩子节点，因为开始的循环已经使当前节点没有左孩子了
        }
    }
}

template <class E>
void postorder_recur(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    if (!root)
        return;
    postorder_recur(visit, root->left);
    postorder_recur(visit, root->right);
    visit(root);
}

// 层次遍历
template <class E>
void levelorder(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    if (!root)
        return;
    queue<Binary_Tree<E> *> q;
    Binary_Tree<E> *p = root;
    q.push(p);
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        visit(p);
        if (p->left)
        {
            q.push(p->left);
        }
        if (p->right)
        {
            q.push(p->right);
        }
    }
}

//5.4
template <class E>
void wangdao5_4(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    stack<Binary_Tree<E> *> s;
    queue<Binary_Tree<E> *> q;
    if (!root)
        return;
    Binary_Tree<E> *cur = root;
    q.push(root);
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        s.push(cur);
        if (cur->left)
            q.push(cur->left);
        if (cur->right)
            q.push(cur->right);
    }
    while (!s.empty())
    {
        cur = s.top();
        visit(cur);
        s.pop();
    }
}

//5.5
template <class E>
int wangdao5_5(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    queue<Binary_Tree<E> *> q;
    Binary_Tree<E> *cur;
    int remain = 1;
    int nextlevel = 0;
    int count = 0;
    if (!root)
        return 0;
    q.push(root);
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        remain--;
        if (cur->left)
        {
            q.push(cur->left);
            nextlevel++;
        }
        if (cur->right)
        {
            q.push(cur->right);
            nextlevel++;
        }
        if (remain == 0)
        {
            remain = nextlevel;
            nextlevel = 0;
            count++;
        }
    }
    return count;
}

//5.6

/* 
    核心思想：
    递归的每个子模式是根据对应的先序序列和中序序列，找到中序序列中对应的根节点下标，
    之后就能找到中序序列中位于根节点左右的左右子树的下标范围，就可以继续递归。
    最后一次递归是前序序列和中序序列都是单节点树。
    所以递归终点条件是inL > inR，因为每次递归前序序列和中序序列的元素个数是对应的，所以值判断中序序列即可。
 */

template <class E>
Binary_Tree<E> *dfs(int preL, int preR, int inL, int inR, vector<E> &preorder, vector<E> &inorder)
{
    if (inL > inR)
        return NULL;
    int val = preorder[preL];
    Binary_Tree<E> *root = new Binary_Tree<E>(val);
    int k; //根节点的下标
    for (k = inL; inorder[k] != val; k++)
        ;
    int num_left = k - inL;  //左子树节点个数
    int num_right = inR - k; //右子树节点个数
    root->left = dfs(preL + 1, preL + num_left, inL, inL + num_left - 1, preorder, inorder);
    root->right = dfs(preR - num_right + 1, preR, inR - num_right + 1, inR, preorder, inorder);
    return root;
}

//根据先序遍历数组和中序遍历数组重建二叉树
template <class E>
Binary_Tree<E> *wangdao5_6(vector<E> preorder, vector<E> inorder)
{
    // map<E, int> dict;
    // int size = inorder.size();
    // for(int i=0;i<size;i++){
    //     dict[i] = i;
    // }
    Binary_Tree<E> *root;
    int pre_size = preorder.size();
    int in_size = inorder.size();
    root = dfs(0, pre_size - 1, 0, in_size - 1, preorder, inorder);
    return root;
}

//5.7

//判断二叉树是否是完全二叉树
/* 
1>如果树为空，则直接返回错 
2>如果树不为空：层序遍历二叉树 
2.1>如果一个节点左右孩子都不为空，则pop该节点，将其左右孩子入队列； 
2.2>如果遇到一个节点，左孩子为空，右孩子不为空，则该树一定不是完全二叉树； 
2.3>如果遇到一个节点，左孩子不为空，右孩子为空；或者左右孩子都为空；则该节点之后的队列中的节点都为叶子节点；该树才是完全二叉树，否则就不是完全二叉树； 
*/
template <class E>
bool wangdao5_7(Binary_Tree<E> *root)
{
    queue<Binary_Tree<E> *> Q;
    if (!root)
        return true;
    Q.push(root);
    while (!Q.empty())
    {
        Binary_Tree<E> *p = Q.front();
        Q.pop();
        if (p->left && p->right)
        {
            Q.push(p->left);
            Q.push(p->right);
        }
        else if (p->right && p->left == NULL)
        {
            return false;
        }
        else
        {
            if (p->left && p->right == NULL)
            {
                Q.push(p->left);
            }
            while (!Q.empty())
            {
                p = Q.front();
                Q.pop();
                if (p->left || p->right)
                    return false;
            }
        }
    }
}

//计算二叉树所有双分支节点个数
template <class E>
int wangdao5_8(Binary_Tree<E> *root)
{
    queue<Binary_Tree<E> *> Q;
    int count = 0;
    if (!root)
        return 0;
    Q.push(root);
    while (!Q.empty())
    {
        Binary_Tree<E> *p = Q.front();
        Q.pop();
        if (p->left && p->right)
        {
            count++;
            Q.push(p->left);
            Q.push(p->right);
        }
        else if (p->left && !p->right)
            Q.push(p->left);
        else if (p->right && !p->left)
            Q.push(p->right);
    }
    return count;
}

template <class E>
int wangdao5_8_recursion(Binary_Tree<E> *root)
{
    if (root == NULL)
        return 0;
    else if (root->left != NULL && root->right != NULL)
        return wangdao5_8_recursion(root->left) + wangdao5_8_recursion(root->right) + 1;
    else
        return wangdao5_8_recursion(root->left) + wangdao5_8_recursion(root->right);
}

template <class E>
void wangdao5_9(Binary_Tree<E> *&root)
{
    if (!root)
        return;
    Binary_Tree<E> *temp = root->right;
    root->right = root->left;
    root->left = temp;
    wangdao5_9(root->left);
    wangdao5_9(root->right);
}

template <class E>
void wangdao5_10(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root, int k)
{
    stack<Binary_Tree<E> *> s;
    if (!root)
        return;
    Binary_Tree<E> *p = root;
    int count = 0;
    while (p || !s.empty())
    {
        if (p)
        {
            ++count;
            if (count == k)
            {
                visit(p);
                break;
            }
            s.push(p);
            p = p->left;
        }
        else
        {
            p = s.top();
            s.pop();
            p = p->right;
        }
    }
}

template <class E>
void Delete(Binary_Tree<E> *&root)
{
    if (!root)
        return;
    Delete(root->left);
    Delete(root->right);
    free(root); //删除以元素值x为根的子树，只要能删除左右子树
} //就可以释放值为x的根节点，因此用后序遍历。（防止断链）

template <class E>
void wangdao5_11(Binary_Tree<E> *&root, E x)
{
    if (!root)
        return;
    if (root->val == x)
    {
        Delete(root);
        exit(0);
    }
    queue<Binary_Tree<E> *> Q;
    Q.push(root);
    while (!Q.empty())
    {
        Binary_Tree<E> *p = Q.front();
        Q.pop();
        if (p->left)
        {
            if (p->left->val == x)
            {
                Delete(p->left);
                p->left = NULL;
            }
            else
                Q.push(p->left);
        }
        if (p->right)
        {
            if (p->right->val == x)
            {
                Delete(p->right);
                p->right = NULL;
            }
            else
                Q.push(p->right);
        }
    }
}

template <class E>
void wangdao5_12(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root, E x)
{
    stack<Binary_Tree<E> *> s;
    Binary_Tree<E> *cur = root;
    Binary_Tree<E> *pre = NULL; //用于记录上一次访问的节点

    while (cur || !s.empty())
    {
        while (cur) //保证没有左孩子
        {
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();
        if (cur->val == x)
        {
            s.pop(); // 当前节点符合访问条件，所以出栈
            while (!s.empty())
            {
                Binary_Tree<E> *temp = s.top();
                s.pop();
                visit(temp);
            }
            return;
        }
        if (cur->right == NULL || cur->right == pre) // 当前节点没有右孩子,为叶节点即第一种情况
        {                                            // 当前节点右孩子是上一次访问的节点即第二种情况
            // visit(cur);
            s.pop();
            pre = cur;
            cur = NULL; // 相当于让下次循环直接进入回溯过程，为了跳过下一次循环的访问左子节点的过程，直接进入栈的弹出阶段，因为但凡在栈中的节点，它们的左子节点都肯定被经过且已放入栈中。
        }
        else
        {
            cur = cur->right; // 经过右孩子节点，因为开始的循环已经使当前节点没有左孩子了
        }
    }
}

//根据递归的模式分析，自底向上返回时，只有值为x的节点向上返回1
//要么从左子树返回，要么从右子树返回，所以自顶向下写递归时，只要左孩子或者后孩子有返回1的，那么当前节点就是祖先
//树的特点是，到每个节点只有一条路径，当前节点也向上返回1，直到根节点
template <class E>
int wangdao5_12_recur(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root, E x)
{
    if (!root)
        return 0;
    if (root->val == x)
        return 1;
    //如果子树中可以找到匹配值 那么此节点肯定是祖先结点
    if (wangdao5_12_recur(visit, root->left, x) || wangdao5_12_recur(visit, root->right, x))
    {
        visit(root);
        return 1;
    }
    return 0;
}

template <class E>
Binary_Tree<E> *wangdao5_13_recur(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root, Binary_Tree<E> *p, Binary_Tree<E> *q)
{
    if (!root || root == p || root == q)
        return root;
    Binary_Tree<E> *left = wangdao5_13_recur(visit, root->left, p, q);
    Binary_Tree<E> *right = wangdao5_13_recur(visit, root->right, p, q);
    if (left && right)
        return root;
    return left ? left : right;
}

template <class E>
int wangdao5_14(Binary_Tree<E> *root)
{
    if (!root)
        return 0;
    queue<Binary_Tree<E> *> q;
    Binary_Tree<E> *cur = root;
    q.push(root);
    int remain = 1;
    int nextlevel = 0;
    int max = 1;
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        remain--;
        if (cur->left)
        {
            nextlevel++;
            q.push(cur->left);
        }
        if (cur->right)
        {
            nextlevel++;
            q.push(cur->right);
        }
        if (remain == 0)
        {
            remain = nextlevel;
            if (nextlevel > max)
                max = nextlevel;
            nextlevel = 0;
        }
    }
    return max;
}

template <class E>
void dfs(vector<E> &preorder, vector<E> &postorder, int preL, int preR, int postL, int postR)
{
    if (preL > preR)
        return;
    postorder[postR] = preorder[preL];
    int num = (preR - preL) / 2; //左右子树数量相同
    dfs(preorder, postorder, preL + 1, preL + num, postL, postL + num - 1);
    dfs(preorder, postorder, preR - num + 1, preR, postR - num, postR - 1);
}

template <class E>
void wangdao5_15(vector<E> &preorder, vector<E> &postorder)
{
    int size = preorder.size();
    dfs(preorder, postorder, 0, size - 1, 0, size - 1);
    for (int i = 0; i < size; i++)
    {
        cout << postorder[i] << ' ';
    }
}
template <class E>
void dfs(Binary_Tree<E> *root, queue<Binary_Tree<E> *> &q)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        q.push(root);
    }
    dfs(root->left, q);
    dfs(root->right, q);
}

template <class E>
Binary_Tree<E> *wangdao5_16(Binary_Tree<E> *root)
{
    if (!root)
        return NULL;
    Binary_Tree<E> *head;
    queue<Binary_Tree<E> *> q;
    dfs(root, q);
    Binary_Tree<E> *pre, *cur;
    pre = new Binary_Tree<E>(0);
    head = q.front();
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        pre->right = cur;
        pre = cur;
    }
    cur->right = NULL;
    return head;
}

// 判断二叉树是否相似
// 总结：写树的递归的时候注意，自底向上先考虑单节点或者空的最基本情况，然后考虑一个三节点树的情况。
// 类似数学归纳法，n=1和n=2成立，且子过程相同，所以对整个树都成立。
template<class E>
bool wangdao5_17(Binary_Tree<E>* root1, Binary_Tree<E>* root2){
    int leftS, rightS;
    if(!root1 && !root2)    return true;        // 两树为空
    if(!root1 || !root2) return false;     // 单树为空
    leftS = wangdao5_17(root1->left, root2->right);     // dfs遍历树
    rightS = wangdao5_17(root1->right, root2->right);
    return leftS && rightS;
}

template<class E>
int wangdao5_19(Binary_Tree<E>* root, int &sum){
    if(!root) return 0;
    wangdao5_19(root->left, sum + root->val);
    wangdao5_19(root->right, sum + root->val);
}

/* 判断二叉树是否是平衡二叉树 */
// template<class E>
// bool is_avltree(Binary_Tree<E>* root){

// }