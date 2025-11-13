#include <iostream>
#include <string>
using namespace std;

string deleteAllSubstring(string s, string t) {
    if (t.empty() || s.length() < t.length()) return s;
    string result;
    int len_t = t.length();
    int i = 0;
    while (i <= (int)s.length() - len_t) {
        if (s.substr(i, len_t) == t) {
            i += len_t; // 跳过匹配的子串
        } else {
            result += s[i];
            i++;
        }
    }
    // 添加剩余字符
    while (i < (int)s.length()) {
        result += s[i];
        i++;
    }
    return result;
}

int main() {
    string s = "abctabcabctt";
    string t = "abc";
    cout << deleteAllSubstring(s, t) << endl; // 输出：tttt
    return 0;
}