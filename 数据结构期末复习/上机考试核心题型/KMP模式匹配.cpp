#include <iostream>
#include <vector>
using namespace std;

vector<int> getNext(const string& s) {
    int cur = 0;    // 记录前缀串中最后一个元素的位置
    int pre = -1;   
    vector<int> next(s.length());
    next[0] = -1;
    while(cur < s.length() - 1) {
        if(pre == -1 || s[cur] == s[pre]) {
            // 当前字符成功匹配
            cur++;
            pre++;
            next[cur] = pre;  // pre在累加后赋值，才可以让失配后的模式串指针指向前缀串的后一个元素
        } else {
            // 将这一过程视为一个模式串和目标串相同的匹配过程
            // cur作为指向目标串的指针，不会回溯
            pre = next[pre]; 
        }
    }
    return next;
}

int KMP(string s, string t) {
    int i = 0;
    int j = 0;
    int m = s.size();
    int n = t.size();
    vector<int> next = getNext(t);
    while(m > i && n > j) {
        if(j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if(n <= j) {
        return i-n;   // 当前目标串指针减模式串的长度即为起始地址
    }
    return -1;
}

// 给定两个字符串s1和s2，求最长的s1前缀ss使得ss为s2的最长后缀，输出该字符串和其长度。
// 输入样例：
// aaariemann
// marjorieaaa
// 输出样例：
// aaa 3
int myFind(string s1, string s2) {
    string s = s1 + s2 + " ";
    vector<int> next = getNext(s);
    cout << s1.substr(0, next[next.size()-1]);
    return next[next.size() - 1];
}

vector<int> GetNext(string s) {
    int i = 0; 
    int j = -1;
    vector<int> next(s.length(), 0);
    next[0] = -1;
    while(i < s.length()-1) {
        if(j == -1 || s[i] == s[j]) {
            i++;
            j++;
            s[i] = j;
        } else {
            j = next[j];
        }
    }
    return next;
}
int kmp(string s, string t, vector<int> next, int start) {
    int m = s.length();
    int n = t.length();
    int i = start;
    int j = 0;
    while(i < m && j < n) {
        if(j==-1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if(j >= n) return i-n;
    else return -1;
}

int count(string s, string t) {
    int m = s.length();
    int n = t.length();
    int startIndex = -1;
    int num = 0;
    vector<int> next = GetNext(t);
    while(startIndex < m - n){
        startIndex = kmp(s,t,next,startIndex+1);
        if(startIndex == -1) break;
        else {
            num++;
        }
    }
    return num;
}
int main() {
    string s1 = "aaaesdevsefaaafsfaaaasdde";
    string s2 = "aaa";
    cout << count(s1,s2);
}