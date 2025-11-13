#include <iostream>
#include <stack>
using namespace std;

struct State {
    int m, n;
    bool computed;
    int result;
    State(int m_, int n_) : m(m_), n(n_), computed(false), result(0) {}
};

int g_nonrecursive(int m, int n) {
    stack<State> stk;
    stk.push(State(m, n));
    while (!stk.empty()) {
        State& s = stk.top();
        if (s.m == 0) {
            s.result = 0;
            s.computed = true;
            stk.pop();
        } else if (!s.computed) {
            s.computed = true;
            stk.push(State(s.m - 1, 2 * s.n));
        } else {
            int sub = stk.top().result;
            stk.pop();
            s.result = sub + s.n;
            if (!stk.empty()) {
                stk.top().result = s.result;
            } else {
                return s.result;
            }
            stk.pop();
        }
    }
    return 0;
}

int main() {
    cout << "g(0, 5) = " << g_nonrecursive(0, 5) << endl;   // 输出0
    cout << "g(2, 1) = " << g_nonrecursive(2, 1) << endl;   // 输出3
    return 0;
}