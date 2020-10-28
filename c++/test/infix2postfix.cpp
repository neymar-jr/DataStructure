#include <iostream>
#include <stack>
#include <unordered_map>

#define MAX_EXPRESSION_LENGTH 100

using namespace std;

unordered_map<char, int> in_stack_priority = {{';', 0}, {'(', 1}, {'*', 5}, {'/', 5}, {'%', 5}, {'+', 3}, {'-', 3}, {')', 6}};
unordered_map<char, int> in_coming_priority = {{';', 0}, {'(', 6}, {'*', 4}, {'/', 4}, {'%', 4}, {'+', 2}, {'-', 2}, {')', 1}};

bool is_letter(char ch)
 {
     return (ch >= 'A' && ch <= 'Z') || (ch >='a' && ch <= 'z');
//     return ch >= '0' && ch <= '9';
 }

/*
������ջ��ʼ��������������;����ջ��Ȼ�������׺���ʽ�ַ��������ַ�ch��
�ظ�ִ�����²��裬ֱ��ch = ��;����ͬʱջ���Ĳ�����Ҳ�ǡ�;����ֹͣѭ����
    ��ch�ǲ�����ֱ�������������һ���ַ�ch��
    ��ch�ǲ��������ж�ch�����ȼ�icp��λ��ջ���Ĳ�����op�����ȼ�isp��
        �� icp(ch) > isp(op)����ch��ջ��������һ���ַ�ch��
        �� icp(ch) < isp(op)����ջ�������
        �� icp(ch) == isp(op)����ջ������������˳����ǡ�(���Ŷ�����һ���ַ�ch��
�㷨������������м�Ϊ����ĺ�׺���ʽ��
 */
int infix2postfix(char infix[], char postfix[])
{
    stack<char> stack;

//    cout << in_stack_priority.at('(');
    int in_index = 0, post_index = 0;
    stack.push(';');
    while(stack.top() != ';' || infix[in_index] != ';')
    {
//        cout << in_index;
        if (is_letter(infix[in_index]))
        {
            postfix[post_index++] = infix[in_index++];
        }
        else
        {
            int icp = in_coming_priority.at(infix[in_index]);
            int isp = in_stack_priority.at(stack.top());
            if (icp > isp)
            {
                stack.push(infix[in_index++]);
            }
            else if (icp < isp)
            {
                postfix[post_index++] = stack.top();
                stack.pop();
            }
            else
            {
                if (stack.top() == '(')
                {
                    ++in_index;
                }
                stack.pop();
            }

        }
    }

    return post_index;
}

int op(int a1, int a2, char op)
{
    switch(op)
    {
        case '+':
            return a1 + a2;
        case '-':
            return a1 - a2;
        case '/':
            return a1 / a2;
        case '*':
            return a1 * a2;
        default:
            return 0;
    }
}

int compute_infix(char infix[]){
    int index = 0;
    stack<char> optr_stack;
    stack<int> opnd_stack;
    optr_stack.push(';');

    while(optr_stack.top() != ';' || infix[index] != ';')
    {
        if (isdigit(infix[index]))
        {
            opnd_stack.push(infix[index++] - '0');
        }
        else {
            int icp = in_coming_priority.at(infix[index]);
            int isp = in_stack_priority.at(optr_stack.top());
            if (icp > isp) {
                optr_stack.push(infix[index++]);
            } else if (icp < isp) {
                int a2 = opnd_stack.top();
                opnd_stack.pop();
                int a1 = opnd_stack.top();
                opnd_stack.pop();
                opnd_stack.push(op(a1, a2, optr_stack.top()));
                optr_stack.pop();
            } else {
                if (optr_stack.top() == '(') {
                    optr_stack.pop();
                    ++index;
                }

            }
        }
    }

    return opnd_stack.top();
}

// ������׺���ʽ
void read_infix(char infix[]){
    char ch;
    int count = 0;
    printf("��������׺���ʽ��\n");
    while((ch = getchar()) != '\n')
    {
        infix[count++] = ch;
    }
    infix[count] = ';';
}

int main()
{
    char infix[MAX_EXPRESSION_LENGTH], postfix[MAX_EXPRESSION_LENGTH];

    read_infix(infix);

//    infix2postfix(infix, postfix);
//
//    printf("%s", postfix);

    printf("���=%d\n", compute_infix(infix));

    system("pause");
    return 0;
}
