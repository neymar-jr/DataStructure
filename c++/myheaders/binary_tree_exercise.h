#include <stack>
#include <queue>
#include <map>

using namespace std;

int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;
int cnt4 = 0;
int cnt5 = 0;

class TreeNode
{
private:
    /* val */
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int e);
    ~TreeNode();
};

TreeNode::TreeNode(int e)
{
    val = e;
    left = NULL;
    right = NULL;
}


TreeNode::~TreeNode()
{
}


// ͳ�ƶ������ж�Ϊ1�Ľڵ����
void dfs1(TreeNode* root){
    if(root == NULL)
        return;
    if(root->left && !root->right || root->right && !root->left)
        cnt1++;
    dfs1(root->left);
    dfs1(root->right);

}

int f1(TreeNode* root){
    dfs1(root);
    return cnt1;
}

// ͳ�ƶ������ж�Ϊ2�Ľڵ����
void dfs2(TreeNode* root){
    if(root == NULL)
        return;
    if(root->left && root->right)
        cnt2++;
    dfs2(root->left);
    dfs2(root->right);

}

int f2(TreeNode* root){
    dfs2(root);
    return cnt2;
}

// ͳ�ƶ������ж�Ϊ0�Ľڵ����
void dfs3(TreeNode* root){
    if(root == NULL)
        return;
    if(!root->left && !root->right)
        cnt3++;
    dfs3(root->left);
    dfs3(root->right);

}

int f3(TreeNode* root){
    dfs3(root);
    return cnt3;
}

// ͳ�ƶ�����������
int f4(TreeNode* root){
    if(root == NULL)
        return 0;
    int left_depth = f4(root->left);
    int right_depth = f4(root->right);
    return max(left_depth, right_depth) + 1;
}



// ͳ�ƶ������Ŀ��
int f5(TreeNode* root){
    if(!root)
        return 0;
    queue<TreeNode*> Q;
    TreeNode* tmp;
    int remain = 1;
    int nextlevel = 0;
    int max_width = 0;
    Q.push(root);
    while(!Q.empty()){
        tmp = Q.front();
        Q.pop();
        remain--;
        if(tmp->left){
            Q.push(tmp->left);
            nextlevel++;
        } 
        if(tmp->right){
            Q.push(tmp->right);
            nextlevel++;
        }
        if(remain == 0){
            if(nextlevel > max_width)
                max_width = nextlevel;
            remain = nextlevel;
            nextlevel = 0;
        }
    }
    return max_width;
}

int f5_clean(TreeNode *root)
{
    if(!root)
        return 0;
    int max = 0;
    queue<TreeNode*> Q;
    Q.push(root);
    while(!Q.empty())
    {
        int count = Q.size();
        if(count > max)
            max = count;
        for(int i = 0; i < count; i++)
        {
            TreeNode* cur = Q.front();
            Q.pop();
            if(cur->left)
                Q.push(cur->left);
            if(cur->right)
                Q.push(cur->right);
        }
    }
    return max;
}

// �Ӷ�������ɾȥ����Ҷ�ڵ�


// ����ָ���ڵ�*p���ڵĲ��


// ����������и��ڵ��е����Ԫ�ص�ֵ


// ������������ÿ���ڵ��������Ů


// ������������һ�ö����������нڵ������ֵ���ڵ����ڲ��