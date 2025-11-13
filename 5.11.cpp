#include <iostream>
#include <vector>
using namespace std;

// 三元组结构：行、列、值
struct Triple {
    int row, col, val;
    Triple(int r=0, int c=0, int v=0) : row(r), col(c), val(v) {}
};

// 稀疏矩阵三元组相加
vector<Triple> addSparseMatrix(const vector<Triple>& A, const vector<Triple>& B, int rows, int cols) {
    vector<Triple> C;
    int i = 0, j = 0;
    while (i < (int)A.size() && j < (int)B.size()) {
        Triple a = A[i], b = B[j];
        if (a.row < b.row || (a.row == b.row && a.col < b.col)) {
            C.push_back(a);
            i++;
        } else if (a.row > b.row || (a.row == b.row && a.col > b.col)) {
            C.push_back(b);
            j++;
        } else { // 行列相同，值相加
            int sum = a.val + b.val;
            if (sum != 0) C.emplace_back(a.row, a.col, sum);
            i++;
            j++;
        }
    }
    // 添加剩余元素
    while (i < (int)A.size()) C.push_back(A[i++]);
    while (j < (int)B.size()) C.push_back(B[j++]);
    return C;
}

// 打印三元组
void printTriples(const vector<Triple>& mat) {
    for (const auto& t : mat) {
        cout << "(" << t.row << "," << t.col << "," << t.val << ") ";
    }
    cout << endl;
}

int main() {
    vector<Triple> A = {{0,1,2}, {1,0,3}, {2,2,4}};
    vector<Triple> B = {{0,1,5}, {1,2,6}, {2,2,-4}};
    vector<Triple> C = addSparseMatrix(A, B, 3, 3);
    printTriples(C); // 输出：(0,1,7) (1,0,3) (1,2,6)
    return 0;
}