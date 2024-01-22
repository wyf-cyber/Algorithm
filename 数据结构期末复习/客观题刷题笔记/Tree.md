# 树-数据结构期末复习笔记
## 一、树的存储结构
1. 双亲存储结构
~~~cpp
#include <vector>
struct PNode {
    char val;
    int parent;  // 指向双亲节点的伪指针，root节点中该值为-1
    PNode() : val(''), parent(-1){}
    PNode(char c, int pnode) : val(c), parent(pnode){}
};  
// 顺序存储
// 当前树中所有的节点均存储在数组Tree中
vector<PNode> Tree[MAXSIZE];
~~~
2. 孩子链存储结构
~~~cpp
// 链式存储
struct SonNode {
    char val;
    vector<SonNode*> children;  // 设置动态数组存储指向各个孩子节点的指针
    SonNode() {}
    SonNode(char c) : val(c) {}
};
~~~
3. 长子兄弟存储结构
~~~cpp
// 链式存储结构
struct EBNode {
    char val;
    EBNode* elderChild;  // 长子指针
    EBNode* brother;     // 兄弟指针
    EBNode() : val(''), elderChild(nullptr), brother(nullptr) {}
    EBNode(char c, EBNode* child, EBNode* bro) : val(c), elderChild(child), brother(bro) {}
};
~~~
## 二、树的逻辑结构
1. 树形表示法
2. 括号表示法
例如A(B(C,D),E(F(G)))，括号表示法中根节点的所有子孙节点用括号括起来，兄弟节点之间用逗号隔开。由于结构具有层次性和统一性，括号表示法的相关问题适合用递归解决
3. 凹入表示法
注意所有柱形右对齐，层次越低的节点柱形越长
1. 文氏图表示法
利用集合之间的包含关系表示树的层次结构

### Example One:括号表示法建树
输入一个由括号表示法表示的树，并据此建立一棵以双亲存储结构存储的树
~~~cpp
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

struct PNode {
    string val;
    int parent;
    PNode() : val("null"), parent(-1) {}
    PNode(string c, int p) : val(c), parent(p) {}
};
struct CNode {
    int val;
    vector<CNode*> children;
};
// 12(1,32(1,2,3))
// 12(1(4(33,5),32(1,2,3)))
void trans(vector<string> s, vector<PNode*>& tree, int parent = -1) {
    // change the array into tree format
    if(s.size() == 0) return;
    // cope with the current root
    PNode* node = new PNode(s[0], parent);
    tree.push_back(node);
    // find out the pointer for root
    int n = tree.size() - 1;
    // cope with the subTree
    stack<int> stk; // push when meet the "(" and pop when meet the ")"
    vector<string> substr;
    for(int i = 2; i < s.size() - 1; i++) {
        // ignore the first ( and the last ")"
        if(stk.empty() && s[i] == ",") {
            // begin next subTree
            trans(substr, tree, n);
            // clean the substr for the next subTree
            vector<string> temp;
            substr = temp;
            continue;
        }
        substr.push_back(s[i]);
        if(s[i] == "(") stk.push(1);
        else if(s[i] == ")") stk.pop();
    }
    // cope with the last subTree
    trans(substr,tree,n);
}
// print the PNode Tree
void printTree(vector<PNode*> tree) {
    // root first
    if(tree.empty()) {
        cout << "The tree is empty." << endl;
        return;
    }
    for(int i = 0; i < tree.size(); i++) {
        cout << tree[i]->val << " " << tree[i]->parent << endl;
    }
}
int main() {
    char c;
    string s;
    getline(cin, s);
    cout << "The input is: " << s << endl;
    bool isNum = false;  // record the former character is number or not.
    vector<string> input;
    for(char i : s) {
        if(i == '(' || i == ')' || i==',') {
            isNum = false;
            string temp = "";
            temp.append(1,i);
            input.push_back(temp);
        } else if(isNum) {
            // this character is a number and the former is a number too
            string temp = input[input.size() - 1];
            temp.append(1,i);
            input[input.size() - 1] = temp;
        } else {
            // this character is a number but the former isn't a number
            isNum = true;
            string temp = "";
            temp.append(1,i);
            input.push_back(temp);
        }
    }
    vector<PNode*> tree;
    trans(input,tree);
    printTree(tree);
}
~~~