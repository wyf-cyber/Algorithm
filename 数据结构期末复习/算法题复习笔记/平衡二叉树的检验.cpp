#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

int check(TreeNode* root) {
    if(root == nullptr) return 0;
    int leftH = check(root->left);
    if(leftH == -1) return -1;
    int rightH = check(root->right);
    if(rightH == -1) return -1;
    if(abs(leftH-rightH) > 1) return -1;
    int higher = leftH > rightH ? leftH : rightH;
    return higher + 1;
}

bool isBalanceTree(TreeNode* root) {
    int res = check(root);
    if(res == -1) return false;
    return true;
}