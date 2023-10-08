# 一、概要
在LeetCode上写链表算法题时经常遇到bug，想要在自己的IDE上运行又需要自己创建测试用例，打印结果。笔者在网上搜索，发现找到的创建方法中链表的格式与LeetCode中定义链表的格式不符，无法直接使用，于是自己写了几个函数。这里列出常用工具函数方便以后使用。

# 二、语言类型
所列工具函数均使用C++语言。

# 三、LeetCode中的链表格式
几乎所有力扣链表题均使用了以下结构：

>// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
# 四、工具函数
## 1.用数组创建链表
~~~cpp
ListNode* createList(int arr[], int n) {
    // n是数组的长度
    ListNode *head = nullptr, *tail = nullptr;
    for(int i = 0; i < n; ++i) {
        auto newNode = new ListNode(arr[i],nullptr);
        if(head == nullptr) {
            head = newNode;
            tail = newNode;
        }else {
            // 更新尾指针
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}
~~~

## 2.打印链表
~~~cpp
void printList(ListNode* head) {
    ListNode* p = head;
    while(p) {
        cout << p->val << endl;
        p = p->next;
    }
    return;
}
~~~

## 3.找出数组中的众数
~~~cpp
   vector<int> searchModes(vector<int> arr) {
    vector<int> res;
    int maxcount = 0;
    int count = 0;
    sort(arr.begin(), arr.end());
    for(int i = 0; i < arr.size(); ++i) {
        if(i == 0) {
            count = 1;
            maxcount = 1;
            res.push_back(arr[0]);
        }else {
            if(arr[i-1] == arr[i]) {
                count++;
            }else {
                count = 1;
            }
            if(count == maxcount) {
                res.push_back(arr[i]);
            }else if(count > maxcount) {
                res.clear();
                maxcount = count;
                res.push_back(arr[i]);
            }
        }
    }
    return res;
}
~~~
# 五、使用效果
![使用效果](https://img-blog.csdnimg.cn/963ed5a9e35c4ec1906de1c0b16216e7.png)

