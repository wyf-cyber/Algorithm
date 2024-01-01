# KMP算法
## 一、KMP算法的功能
KMP算法（Knuth-Morris-Pratt算法）是一种模式匹配算法，用于从目标串找出模式串所在的位置。通过对模式串进行预处理，构建部分匹配表，KMP算法能够在匹配过程中根据已匹配的前缀信息跳过一些不必要的比较（避免目标串指针的回退），从而减少比较次数。
## 二、算法效率
KMP算法是一种稳定的字符串匹配算法，不受输入数据顺序的影响，设目标串长度为m，模式串长度为n
最坏时间复杂度为O(m+n)
## 三、算法原理
在KMP模式匹配中,当模式串位置j处字符与目标串位置i处字符比较时
- 两个字符不等,目标串位i的位移方式是 **i不改变**,j的位移方式是 j=next[j]。
- 两个字符相等，i的位移方式是 i=i+1，j的位移方式是 j=j+1

## 四、算法代码
~~~cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getNextOne(const string& t) {
    vector<int> next(t.length(), -1);
    // next[0] = -1恒成立
    if(next.size() <= 1) return next;
    // next[1] = 0 恒成立
    next[1] = 0;
    for(int i = 2; i < next.size(); i++) {
        int sublen = 1;  // 前（后）缀的长度
        int temp = 0;    // 当前满足条件的最大前（后）缀长度
        for(;  sublen < i; sublen++) {
            string front = t.substr(0, sublen);
            string rear = t.substr(i-sublen, sublen);
            if(front == rear) temp = sublen;
        }
        next[i] = temp;
    }
    return next;
}
~~~

~~~cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getNextTwo(const string& s) {
    int n = s.length();
    vector<int> next(n, 0);
    
}
~~~

~~~cpp
int KMP(const string& s, const string& t) {
    // s是目标串，t是模式串
    int n = s.length();
    int m = t.length();
    vector<int> next = getNext(t);
    int i = 0;  // 指向目标串的指针
    int j = 0;  // 指向模式串的指针
    while(i < n && j < m) {
        if(s[i] == t[j] || j == -1) {
            i++;  // 若j = -1，表示没有成功的匹配，需要继续尝试下一个为止
            j++;  // 若j = -1，表示已经回退到初始状态，将j置零，重新开始搜索
        } else {
            j = next[j]; 
        }
    }
    if(m >= j) return i-m;
    else return -1; 
}
~~~