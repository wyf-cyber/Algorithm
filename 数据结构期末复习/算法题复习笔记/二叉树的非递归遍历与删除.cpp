#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct BTNode {
    int info;
    BTNode* left;
    BTNode* right;
};

// delete binary tree
void deleteOne(BTNode* root) {
    if(root == nullptr) return;
    else if(root->left == nullptr && root->right == nullptr) {
        delete root;
        return;
    }
    if(root->left) deleteOne(root->left);
    if(root->right) deleteOne(root->right);
    delete root;
}

// 二叉树的非递归遍历
// 先序遍历
vector<int> preOrderTraversal(BTNode* root) {
    stack<BTNode*> stk;
    vector<int> list;
    if(root == nullptr) return list;
    stk.push(root);
    while(!stk.empty()) {
        BTNode* node = stk.top();
        stk.pop();
        // 读取当前节点
        list.push_back(node->info); 
        // 注意左子树后进先出     
        if(node->right) stk.push(root->right);
        if(node->left) stk.push(root->left);
    }   
    return list;
}
// 中序遍历
vector<int> inOrderTraversal(BTNode* root) {
    vector<int> list;
    if(root == nullptr) return list;
    stack<BTNode*> stk;
    BTNode* cur = root;
    while(cur != nullptr || stk.empty() != true) {
        if(cur) {
            stk.push(cur);
            cur = cur->left;
        } else {
            // 左子树为空，从栈中弹出栈顶元素
            // 将中间节点加入数组并开始遍历右子树
            cur = stk.top();
            stk.pop();
            list.push_back(cur->info);
            cur = cur->right;
        }
    }
    return list;
}

// 后序遍历
vector<int> postOrderTraversal(BTNode* root) {
    vector<int> list;
    if(root == nullptr) return list;
    stack<BTNode*> stk;
    stk.push(root);
    while(!stk.empty()) {
        BTNode* node = stk.top();
        stk.pop();
        list.push_back(node->info);      
        if(node->left) stk.push(node->left);
        if(node->right) stk.push(node->right);
    }
    // 反转数组
    int n = list.size();
    for(int i = 0; i < n/2; i++) {
        int temp = list[i];
        list[i] = list[n - i - 1];
        list[n-i-1] = temp;
    }
    return list;
}