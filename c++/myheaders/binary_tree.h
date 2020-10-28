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

//�ܽ�һ�£����ڷǵݹ�ʵ�����ı�����ǰ�к���Ҫʹ��ջ����α���ʹ�ö���
//ջ������������;��
//1.����dfs·���ϵ����нڵ㣬�ڱ�����Ҷ�ӽڵ�ʱ����ͨ��s.top()���ݣ�Ȼ���Ե����Ͻ����нڵ���ʡ�
//2.����dfs·���ϵ�������δ���ʵĲ�·�ڣ���dfs���������У�����в�·�ھͼӵ�ջ��ڱ�����Ҷ�ӽڵ�ʱ����ͨ��s.top()���ݣ�ֱ��ת�����һ��δ���ʵĲ�·�ڡ�
//3.������ʽ�������ڷ�ת��

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
            s.push(p); //����·���ϵĽڵ㣬���ڻ���
            p = p->left;
        }
        else
        {
            p = s.top(); //���ݵ�·���ϵ����һ���ڵ㣬�ж�������δ���ʵĲ�·��
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
        if (p->rchild) //�����δ���ʵĲ�·�ڣ���ջ����
        {
            s.push(p->rchild);
        }
        if (p->lchild)
        {
            p = p->lchild;
        }
        else
        {
            p = s.top(); //���ݵ��ϸ�δ���ʵĲ�·��
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

//�������ϰ汾
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
                p = NULL; //������p������������p����ΪҪ��ջ������һ��
            }
        }
    }
}

/* 
��������ı���˳�������Ҹ��������Ƿ���Դ�������Ϥ�Ҽ򵥵�ǰ�����ת����ȥ��������أ�
���ǿ��Եġ����ǿ��Թ۲쵽���������������˳���Ǹ�����Ľڵ����У��ٵ��򣬱�պ��Ǻ��������˳�����Ҹ���
������˳���Ǹ�����Ļ����ܺð죬��ǰ������Ĵ����и����о����ˡ��������ǿ���ѡ������ջ��һ�����ڸ����������һ�����ڱ������У����Ĵ����ǰ�����ֻ�����������޸ļ��ɡ�
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
            output.push(p); //�����Ը�->��->��˳������Ľ������������ջ��ʵ�ַ������������->��->��
            s.push(p);      //����dfsʱ·����δ������ȫ�Ľڵ�
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
    stack<Binary_Tree<E> *> s; //ջ�����ò�ͬ�����ڱ�������δ���ʵķֲ��
    Binary_Tree<E> *p = root;  //����һֱ�򵥲��ߣ�Ϊ�˱�֤����ʱ���ҵ�δ���ʵĲ�·�ڣ��ڵ�����ʱ�ͽ���·�ڼӵ�ջ�
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
            p = s.top(); //��ջ����
            s.pop();
        }
    }
    while (!output.empty())
    {
        visit(output.top());
        output.pop();
    }
}

/* ʵ���ϣ����ǿ���ֻʹ��һ��ջȥģ�������������ǻ�Ƚ��鷳��
Ϊ�˱��������ø��ӣ����ǿ����ȿ���һ���ܲ��ܽ��һ��ǰ�������˼·��
���ȣ����Ǻ�ȷ�����ǣ���������Ŀ�ͷ��ǰ������ǿ���һ���ģ������Ⱦ����������������֧��ֱ�������Ľڵ��Ǹ�Ҷ�ӽڵ㣨û�����Һ��ӣ�Ϊֹ���������£�
while(cur!=null) { // ����������ڵ�
    s.push(cur);
    cur = cur.left;
}
�������ܹؼ������ǵÿ���ʲôʱ����ܷ��ʽڵ㡣
�������ǿ��Ժ�ȷ��һ�������������Ҷ�ӽڵ㣬��Ȼ����ʡ�
���ǵ�һ����������ǻ���ǰ����������������ʱ�����Ǿ�����·����������ң�����ǰ���������˵������·�������ϸ�����·����һ�µġ�
�����ں�������У������Ⱦ������ڵ㣬�������ǲ���ȥ�����������ǻ�ѡ���ȷ����������ӽڵ㡣
��������������£����ǻὫ���ڵ�����ջ�в��������ȵ���Ҫ��������ʱ���ٳ���
��ô��ʲôʱ�����Ҫ���ʸ��ڵ��أ��𰸵�Ȼ���Ƿ��������ӽڵ�֮���ˡ�
������λ�ȡ�����Ϣ���Ⲣ���ѣ����ǿ��Լ�¼һ����һ�η��ʵĽڵ㣬Ȼ���ж�һ�µ�ǰ�����Ľڵ����һ�η��ʵĽڵ���ʲô��ϵ�ͺ��ˡ�
�����ǰ�����Ľڵ�����ӽڵ�����һ�η��ʵĽڵ㣬��Ȼ������Ҫ���ʵ�ǰ�ڵ��ˡ����ǵڶ��������

�ܽ�����������ʲôʱ����ܷ��ʽڵ㡣���������������

1.��ǰ�����ڵ���Ҷ�ӽڵ㡣
2.��ǰ�����ڵ���Һ��ӽڵ�����һ�η��ʵĽڵ㡣

�������˼·�Լ����ǰ�������˼·�����ǿ���д�����´��룺
 */
template <class E>
void postorder_one_stack(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root)
{
    stack<Binary_Tree<E> *> s;
    Binary_Tree<E> *cur = root;
    Binary_Tree<E> *pre = NULL; //���ڼ�¼��һ�η��ʵĽڵ�

    while (cur || !s.empty())
    {
        while (cur) //��֤û������
        {
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();
        if (cur->right == NULL || cur->right == pre)
        {               // ��ǰ�ڵ�û���Һ���,ΪҶ�ڵ㼴��һ�����
            visit(cur); // ��ǰ�ڵ��Һ�������һ�η��ʵĽڵ㼴�ڶ������
            s.pop();    // ��ǰ�ڵ���Ϸ������������Գ�ջ
            pre = cur;
            cur = NULL; // �൱�����´�ѭ��ֱ�ӽ�����ݹ��̣�Ϊ��������һ��ѭ���ķ������ӽڵ�Ĺ��̣�ֱ�ӽ���ջ�ĵ����׶Σ���Ϊ������ջ�еĽڵ㣬���ǵ����ӽڵ㶼�϶����������ѷ���ջ�С�
        }
        else
        {
            cur = cur->right; // �����Һ��ӽڵ㣬��Ϊ��ʼ��ѭ���Ѿ�ʹ��ǰ�ڵ�û��������
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

// ��α���
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
    ����˼�룺
    �ݹ��ÿ����ģʽ�Ǹ��ݶ�Ӧ���������к��������У��ҵ����������ж�Ӧ�ĸ��ڵ��±꣬
    ֮������ҵ�����������λ�ڸ��ڵ����ҵ������������±귶Χ���Ϳ��Լ����ݹ顣
    ���һ�εݹ���ǰ�����к��������ж��ǵ��ڵ�����
    ���Եݹ��յ�������inL > inR����Ϊÿ�εݹ�ǰ�����к��������е�Ԫ�ظ����Ƕ�Ӧ�ģ�����ֵ�ж��������м��ɡ�
 */

template <class E>
Binary_Tree<E> *dfs(int preL, int preR, int inL, int inR, vector<E> &preorder, vector<E> &inorder)
{
    if (inL > inR)
        return NULL;
    int val = preorder[preL];
    Binary_Tree<E> *root = new Binary_Tree<E>(val);
    int k; //���ڵ���±�
    for (k = inL; inorder[k] != val; k++)
        ;
    int num_left = k - inL;  //�������ڵ����
    int num_right = inR - k; //�������ڵ����
    root->left = dfs(preL + 1, preL + num_left, inL, inL + num_left - 1, preorder, inorder);
    root->right = dfs(preR - num_right + 1, preR, inR - num_right + 1, inR, preorder, inorder);
    return root;
}

//����������������������������ؽ�������
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

//�ж϶������Ƿ�����ȫ������
/* 
1>�����Ϊ�գ���ֱ�ӷ��ش� 
2>�������Ϊ�գ�������������� 
2.1>���һ���ڵ����Һ��Ӷ���Ϊ�գ���pop�ýڵ㣬�������Һ�������У� 
2.2>�������һ���ڵ㣬����Ϊ�գ��Һ��Ӳ�Ϊ�գ������һ��������ȫ�������� 
2.3>�������һ���ڵ㣬���Ӳ�Ϊ�գ��Һ���Ϊ�գ��������Һ��Ӷ�Ϊ�գ���ýڵ�֮��Ķ����еĽڵ㶼ΪҶ�ӽڵ㣻����������ȫ������������Ͳ�����ȫ�������� 
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

//�������������˫��֧�ڵ����
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
    free(root); //ɾ����Ԫ��ֵxΪ����������ֻҪ��ɾ����������
} //�Ϳ����ͷ�ֵΪx�ĸ��ڵ㣬����ú������������ֹ������

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
    Binary_Tree<E> *pre = NULL; //���ڼ�¼��һ�η��ʵĽڵ�

    while (cur || !s.empty())
    {
        while (cur) //��֤û������
        {
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();
        if (cur->val == x)
        {
            s.pop(); // ��ǰ�ڵ���Ϸ������������Գ�ջ
            while (!s.empty())
            {
                Binary_Tree<E> *temp = s.top();
                s.pop();
                visit(temp);
            }
            return;
        }
        if (cur->right == NULL || cur->right == pre) // ��ǰ�ڵ�û���Һ���,ΪҶ�ڵ㼴��һ�����
        {                                            // ��ǰ�ڵ��Һ�������һ�η��ʵĽڵ㼴�ڶ������
            // visit(cur);
            s.pop();
            pre = cur;
            cur = NULL; // �൱�����´�ѭ��ֱ�ӽ�����ݹ��̣�Ϊ��������һ��ѭ���ķ������ӽڵ�Ĺ��̣�ֱ�ӽ���ջ�ĵ����׶Σ���Ϊ������ջ�еĽڵ㣬���ǵ����ӽڵ㶼�϶����������ѷ���ջ�С�
        }
        else
        {
            cur = cur->right; // �����Һ��ӽڵ㣬��Ϊ��ʼ��ѭ���Ѿ�ʹ��ǰ�ڵ�û��������
        }
    }
}

//���ݵݹ��ģʽ�������Ե����Ϸ���ʱ��ֻ��ֵΪx�Ľڵ����Ϸ���1
//Ҫô�����������أ�Ҫô�����������أ������Զ�����д�ݹ�ʱ��ֻҪ���ӻ��ߺ����з���1�ģ���ô��ǰ�ڵ��������
//�����ص��ǣ���ÿ���ڵ�ֻ��һ��·������ǰ�ڵ�Ҳ���Ϸ���1��ֱ�����ڵ�
template <class E>
int wangdao5_12_recur(void (*visit)(Binary_Tree<E> *), Binary_Tree<E> *root, E x)
{
    if (!root)
        return 0;
    if (root->val == x)
        return 1;
    //��������п����ҵ�ƥ��ֵ ��ô�˽ڵ�϶������Ƚ��
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
    int num = (preR - preL) / 2; //��������������ͬ
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

// �ж϶������Ƿ�����
// �ܽ᣺д���ĵݹ��ʱ��ע�⣬�Ե������ȿ��ǵ��ڵ���߿յ�����������Ȼ����һ�����ڵ����������
// ������ѧ���ɷ���n=1��n=2���������ӹ�����ͬ�����Զ���������������
template<class E>
bool wangdao5_17(Binary_Tree<E>* root1, Binary_Tree<E>* root2){
    int leftS, rightS;
    if(!root1 && !root2)    return true;        // ����Ϊ��
    if(!root1 || !root2) return false;     // ����Ϊ��
    leftS = wangdao5_17(root1->left, root2->right);     // dfs������
    rightS = wangdao5_17(root1->right, root2->right);
    return leftS && rightS;
}

template<class E>
int wangdao5_19(Binary_Tree<E>* root, int &sum){
    if(!root) return 0;
    wangdao5_19(root->left, sum + root->val);
    wangdao5_19(root->right, sum + root->val);
}

/* �ж϶������Ƿ���ƽ������� */
// template<class E>
// bool is_avltree(Binary_Tree<E>* root){

// }