#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct BTNode {
    int val;
    BTNode* left;
    BTNode* right;
    BTNode(int data): val(data),left(NULL),right(NULL){}
};
// 构造二叉树
BTNode* buildTree() {
    BTNode* root = new BTNode(1);
    root->left = new BTNode(-15);
    root->right = new BTNode(3);
    root->left->left = new BTNode(4);
    root->left->right = new BTNode(5);
    root->right->left = new BTNode(6);
    root->right->right = new BTNode(7);
    return root;
}

// 探测树的最大深度
int getHeight(BTNode* root) {
    if(root == NULL) return 0;
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    int res = lh > rh ? lh : rh;
    return res + 1;
}

vector<pair<int, BTNode*>> levelTraversal(BTNode* root) {
    vector<pair<int, BTNode*>> ans;
    queue<BTNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            BTNode* node = q.front();
            q.pop();
            ans.push_back(pair<int, BTNode*>(node->val, node));
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return ans;
}

BTNode* f(BTNode* root) {
    vector<pair<int, BTNode*>> nodes = levelTraversal(root);
    for (int i = nodes.size() / 2 - 1; i >= 0; i--) {
        nodes[i].first = nodes[2 * i + 1].first + nodes[2 * i + 2].first + nodes[i].first;
    }
    // 找出子树和最大的节点
    pair<int, BTNode*> maxNode(INT_MIN, nullptr);
    for (int j = 0; j < nodes.size(); j++) {
        if (maxNode.first < nodes[j].first) {
            maxNode = nodes[j];
        }
    }
    return maxNode.second;
}


int main() {
    BTNode* root = buildTree();

    // 调用函数
    BTNode* result = f(root);

    // 打印结果
    std::cout << "Root of subtree with maximum sum: " << result->val << std::endl;

    // 释放内存
    // 省略释放内存的代码，根据实际情况释放节点的内存

    return 0;
}