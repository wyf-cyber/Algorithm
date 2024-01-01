#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

struct Node {
    string info;
    Node* left;
    Node* right;
};
/*
Rules:
1.表达式树中非叶子节点存储运算符
2.叶子结点存储运算数
3.当前分支节点所在子树的运算结果等于该分支节点左右子树的运算结果按照当前节点存储的运算符运算的结果
4.使用后缀表达式建树
5.使用栈存储树的节点，每遇到一个数字节点，直接入栈，遇到运算符节点，出栈两个元素并将当前节点的右左指针指向这两个节点，然后将新节点入栈
6.出栈栈中最后一个节点，该节点即为树的根节点
*/
Node* buildTree(const vector<string>& postfix) {
    stack<Node*> ops;
    for (int i = 0; i < postfix.size(); i++) {
        Node* node = new Node();
        node->info = postfix[i];
        if (postfix[i] == "+" || postfix[i] == "-" || postfix[i] == "*" || postfix[i] == "/") {
            Node* node2 = ops.top();
            ops.pop();
            Node* node1 = ops.top();
            ops.pop();
            node->left = node1;
            node->right = node2;
        }
        ops.push(node);
    }
    return ops.top();
}

int traversal(Node* root) {
    if (root == nullptr) return 0;
    if (root->info == "+") {
        return traversal(root->left) + traversal(root->right);
    }
    else if (root->info == "-") {
        return traversal(root->left) - traversal(root->right);
    }
    else if (root->info == "*") {
        return traversal(root->left) * traversal(root->right);
    }
    else if (root->info == "/") {
        return traversal(root->left) / traversal(root->right);
    }
    return stoi(root->info);
}

vector<string> divide(string s) {
    bool isNum = false;
    int temp = 0;
    vector<string> ans;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            if (isNum) {
                // 前一个是数，将数存入数组
                ans.push_back(to_string(temp));
                isNum = false;
                temp = 0;
            }
            ans.push_back(string(1, s[i]));
        }
        else {
            // 当前字符是数据
            isNum = true;
            temp = temp * 10 + (s[i] - '0');
            if (i == s.length() - 1) {
                // 最后一个了 
                ans.push_back(to_string(temp));
            }
        }
    }
    return ans;
}
/*
Rules:
1.遇到数字直接加入后缀表达式
2.遇到+-将符号栈中所有"("前的运算符出栈后入栈
3.遇到乘除将符号栈中所有"("前的乘除运算符出栈后入栈
4.遇到右括号将符号栈中所有"("前的运算符和左括号出栈
*/
vector<string> shift(const vector<string>& infix) {
    // output postfix
    vector<string> postfix;
    stack<string> ops;         // 符号栈
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] == "+" || infix[i] == "-") {
            if (ops.empty()) {
                ops.push(infix[i]);
                continue;
            }
            else {
                string temp = ops.top();
                while (temp != "(") {
                    postfix.push_back(temp);
                    ops.pop();
                    if (ops.empty()) {
                        break;
                    }
                    else {
                        temp = ops.top();
                    }
                }
            }
            ops.push(infix[i]);
        }
        else if (infix[i] == "*" || infix[i] == "/") {
            if (ops.empty()) {
                ops.push(infix[i]);
                continue;
            }
            else {
                string temp = ops.top();
                while (temp != "(" && temp != "+" && temp != "-") {
                    postfix.push_back(temp);
                    ops.pop();
                    if (ops.empty()) {
                        break;
                    }
                    else {
                        temp = ops.top();
                    }
                }
                ops.push(infix[i]);
            }
        }
        else if (infix[i] == "(") {
            ops.push(infix[i]);
        }
        else if (infix[i] == ")") {
            if (ops.empty()) {
                continue;
            }
            else {
                string temp = ops.top();
                while (temp != "(") {
                    postfix.push_back(temp);
                    ops.pop();
                    if (ops.empty()) {
                        break;
                    }
                    else {
                        temp = ops.top();
                    }
                }
                if (!ops.empty()) ops.pop();   // 左括号出栈
            }
        }
        else {
            // 是数字
            postfix.push_back(infix[i]);
        }
    }
    // 将栈中剩余所有元素出栈
    while (!ops.empty()) {
        string t = ops.top();
        postfix.push_back(t);
        ops.pop();
    }
    return postfix;
}

/*
Rules:
1.读取到数字，将数字入栈
2.读取到运算符，将栈中最上层的两个数出栈并运算，然后将结果入栈
3.遍历后缀表达式完成后将栈中剩余的唯一一个元素出栈（即运算结果）
*/
int calculating(const vector<string>& postfix) {
    stack<int> nums;
    for (int i = 0; i < postfix.size(); i++) {
        if (postfix[i] == "+") {
            int op2 = nums.top();
            nums.pop();
            int op1 = nums.top();
            nums.pop();
            nums.push(op1 + op2);
        }
        else if (postfix[i] == "-") {
            int op2 = nums.top();
            nums.pop();
            int op1 = nums.top();
            nums.pop();
            nums.push(op1 - op2);
        }
        else if (postfix[i] == "*") {
            int op2 = nums.top();
            nums.pop();
            int op1 = nums.top();
            nums.pop();
            nums.push(op1 * op2);
        }
        else if (postfix[i] == "/") {
            int op2 = nums.top();
            nums.pop();
            int op1 = nums.top();
            nums.pop();
            nums.push(op1 / op2);
        }
        else {
            nums.push(stoi(postfix[i]));
        }
    }
    return nums.top();
}

int main() {
    string s = "52-23+4*6/2-(66*2)";
    vector<string> elms = divide(s);
    cout << "infix: ";
    for (int i = 0; i < elms.size(); i++) {
        cout << elms[i] << " ";
    }
    cout << endl;
    cout << "Postfix: ";
    vector<string> postfix = shift(elms);
    for (int j = 0; j < postfix.size(); j++) {
        cout << postfix[j] << " ";
    }
    cout << " = " << calculating(postfix)<< endl;
    cout << "Traversal result: " << traversal(buildTree(postfix)) << endl;
}