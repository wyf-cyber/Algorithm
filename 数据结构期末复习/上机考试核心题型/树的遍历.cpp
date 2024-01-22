#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct BTNode {
    int info;
    BTNode* left;
    BTNode* right;
};

void pre(BTNode* root) {
    if(root == nullptr) return;
    cout << root->info << " ";
    pre(root->left);
    pre(root->right);
}
void mid(BTNode* root) {
    if(root == nullptr) return;
    pre(root->left);   
    cout << root->info << " ";
    pre(root->right);
}
void post(BTNode* root) {
    if(root == nullptr) return;
    pre(root->left);
    pre(root->right);
    cout << root->info << " ";
}
void level(BTNode* root) {
    queue<BTNode*> q;
    q.push(root);
    while(!q.empty()) {
        int n = q.size();
        for(int i = 0; i < n; i++) {
            BTNode* node = q.front();
            q.pop();
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        cout << endl;
    } 
}
int getHeight(BTNode* root) {
    if(root == nullptr) return 0;
    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);
    return 1 + max(leftH, rightH);
}