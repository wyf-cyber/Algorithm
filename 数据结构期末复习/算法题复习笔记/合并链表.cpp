#include <iostream>
#include <vector>
using namespace std;

// 合并两个有序链表，空间复杂度为O(1)
typedef struct node {
    int val;
    node* next;
} LinkList;

// 将两个链表归并到ha链表中
void combine(node* ha, node* hb) {
    node* p1 = ha->next;
    node* pre = ha;
    node* p2 = hb->next;
    node* fore;
    while(p1 != NULL && p2 != NULL) {
        fore = p2->next;
        if(p1->val > p2->val) {
            pre->next = p2;
            p2->next = p1;
            pre = p2;
            p2 = fore;
        } else if(p1->val == p2->val) {
            p2 = fore;
        } else {
            p1 = p1->next;
            pre = pre->next;
        }
    }
    if(p2) pre->next = p2;
}

// 删除链表中的相同元素
void d(LinkList* head) {
    if(head->next == NULL) return;
    node* pre = head->next;
    node* cur = pre->next;
    while(cur) {
        if(cur->val == pre->val) {
            // 删除cur
            pre->next = cur->next;
            delete cur;
            cur = pre->next;
        } else {
            cur = cur->next;
            pre = pre->next;
        }
    }
}