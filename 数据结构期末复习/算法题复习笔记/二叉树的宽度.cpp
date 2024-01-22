#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct BTNode {
    int val;
    BTNode* left;
    BTNode* right;
};

int getBroad(BTNode* root) {
    if(root == nullptr) return 0;
    int tempMax = 0;  // 记录当前已知的拥有最多节点的层的节点数
    queue<BTNode*> q;
    q.push(root);
    while(!q.empty()) {
        int n = q.size();
        if(n > tempMax) tempMax = n;
        for(int i = 0; i < n; i++) {
            BTNode* node = q.front();
            q.pop();
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
    }
    return tempMax;
}

BTNode* buildTree() {
    BTNode* root = new BTNode();
    BTNode* node1 = new BTNode();
    BTNode* node2 = new BTNode();
    BTNode* node3 = new BTNode();
    BTNode* node4 = new BTNode();
    BTNode* node5 = new BTNode();
    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node2->left = node4;
    node2->right = node5;
    return root;
}