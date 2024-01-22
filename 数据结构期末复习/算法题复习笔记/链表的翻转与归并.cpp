#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int data) : val(data), next(nullptr) {}
};

/*
先将原链表头结点的next指针指向其本身，表示建立一个空的循环链表，
然后将原链表中的节点逐个用头插法插入新链表中
*/
void reverse(Node* L) {
    Node* p = L->next;
    Node* q;
    L->next = L;
    while(p != L) {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}

void divide(Node* L) {
    Node* cur = L->next;
    Node* pre = L;
    if (cur) {
        cur = cur->next;
        pre = pre->next;
    }
    while (cur) {
        if (cur->val < 0) {
            // 将该节点从链表中删除
            pre->next = cur->next;
            // 将该节点用头插法插入链表
            cur->next = L->next;
            L->next = cur;
            cur = pre->next;  // 移动cur到下一个节点
        }
        else {
            cur = cur->next;
            pre = pre->next;
        }
    }
}