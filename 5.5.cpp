#include <iostream>
#include <stack>
#include <string>
#include <algorithm> 
using namespace std;

string prefixToPostfix(string prefix) {
    stack<string> stk;
    // 前缀式从右向左扫描
    reverse(prefix.begin(), prefix.end());
    for (char c : prefix) {
        if (isalpha(c)) { // 操作数直接入栈
            stk.push(string(1, c));
        } else { // 运算符：弹出两个操作数拼接
            string op1 = stk.top(); stk.pop();
            string op2 = stk.top(); stk.pop();
            stk.push(op1 + op2 + c);
        }
    }
    return stk.empty() ? "" : stk.top();
}

int main() {
    string prefix = "+*AB-CD"; 
    cout << prefixToPostfix(prefix) << endl; // 输出：AB*CD-+
    return 0;
}