// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;

// 定义二叉树节点结构体
struct TreeNode {
    char value; // 存储操作数或操作符
    TreeNode *left, *right;
    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

// 检查是否为操作符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 比较操作符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 构建表达式树
TreeNode* buildExpressionTree(const string& expression) {
    stack<TreeNode*> operandStack;
    stack<char> operatorStack;

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];

        if (ch >= '0' && ch <= '9') { // 数字
            operandStack.push(new TreeNode(ch));
        } else if (ch == '(') { // 左括号
            operatorStack.push(ch);
        } else if (ch == ')') { // 右括号
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                TreeNode* root = new TreeNode(operatorStack.top());
                operatorStack.pop();
                root->right = operandStack.top(); operandStack.pop();
                root->left = operandStack.top(); operandStack.pop();
                operandStack.push(root);
            }
            operatorStack.pop(); // 弹出'('
        } else if (isOperator(ch)) { // 操作符
            while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(ch)) {
                TreeNode* root = new TreeNode(operatorStack.top());
                operatorStack.pop();
                root->right = operandStack.top(); operandStack.pop();
                root->left = operandStack.top(); operandStack.pop();
                operandStack.push(root);
            }
            operatorStack.push(ch);
        }
    }

    // 处理剩余的操作符
    while (!operatorStack.empty()) {
        TreeNode* root = new TreeNode(operatorStack.top());
        operatorStack.pop();
        root->right = operandStack.top(); operandStack.pop();
        root->left = operandStack.top(); operandStack.pop();
        operandStack.push(root);
    }

    return operandStack.top();
}

// 后序遍历计算表达式值
int evaluate(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return root->value - '0'; // 叶节点，返回数字

    int leftValue = evaluate(root->left);
    int rightValue = evaluate(root->right);

    switch (root->value) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/': return leftValue / rightValue;
        default: return 0;
    }
}

int main() {
    string input;
    while (getline(cin, input) && input != "=") {
        // 去掉等号
        input.pop_back();
        TreeNode* expTree = buildExpressionTree(input);
        cout << evaluate(expTree) << endl;
        // 清理内存
        // 这里可以添加清理表达式树的逻辑
    }
    return 0;
}