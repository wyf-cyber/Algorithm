#include <iostream>
#include <vector>
using namespace std;

struct BTNode {
    int val;
    BTNode* left;
    BTNode* right;
    BTNode(int data): val(data),left(NULL),right(NULL){}
};

int f(BTNode* root, vector<pair<int, BTNode*>>& nodes) {
    if(root == NULL) return 0;
    int leftSum = f(root->left, nodes);
    int rightSum = f(root->right, nodes);
    int sum = leftSum + rightSum + root->val;
    pair<int, BTNode*> temp(sum, root);
    nodes.push_back(temp);
    return sum;
}

BTNode* fun(BTNode* root) {
    vector<pair<int, BTNode*>> nodes;
    f(root, nodes);
    pair<int, BTNode*> maxSub(INT_MIN, nullptr);
    for(int i = 0; i < nodes.size(); i++) {
        if(maxSub.first < nodes[i].first) {
            maxSub = nodes[i];
        }
    }
    return maxSub.second;
}