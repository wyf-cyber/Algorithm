#include <iostream>
#include <vector>

struct BTNode {
    int val;
    BTNode* left;
    BTNode* right;
};

void Count(BTNode* root, int& count) {
    if(root == NULL) return;
    if(root->left != NULL && root->right != NULL) {
        count++;
    }
    Count(root->left, count);
    Count(root->right, count);
}

