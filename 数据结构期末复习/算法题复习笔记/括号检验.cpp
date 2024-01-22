#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

/*
算法思路：
建立一个栈用于存储左括号，依次从左往右读取字符串，每读取到一个左括号就将左括号进栈，每读取一个右括号
先检查栈是否为空，如果为空说明没有与之匹配的左括号，字符串不匹配，
如果栈不为空将栈顶元素出栈并与当前元素比较，如果是同一种括号，就继续向后遍历，如果不是同一种括号说明不匹配
遍历字符串后检查栈中是否为空，如果不空，则说明栈中的左括号没有与之对应的右括号，字符串不匹配
*/

bool check(const string& s) {
    if(s.length() == 0) return true;
    stack<char> stk;   // 用于存储左括号
    for(char c : s) {
        if(c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else if(c == ')') {
            if(stk.empty()) return false;
            char temp = stk.top();         // temp用于存储栈顶元素 
            stk.pop();
            if(temp != '(') return false; 
        } else if(c == ']') {
            if(stk.empty()) return false;
            char temp = stk.top();
            stk.pop();
            if(temp != '[') return false;
        } else if(c == '}') {
            if(stk.empty()) return false;
            char temp = stk.top();
            stk.pop();
            if(temp != '{') return false;
        }
    }
    if(!stk.empty()) return false;
    return true;
}


int main() {
    string s;
    while (cin >> s) {
        cout << "The sentence is " << check(s) << endl;
    }
}