#include <iostream>
using namespace std;


int getMatrixElement(int* baseAddr, int rows, int cols, int i, int j) {
    // 检查下标合法性
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        cerr << "下标越界！" << endl;
        return -1;
    }
    // 行主序地址公式：基地址 + (i * 列数 + j) * 元素大小（此处元素为int，大小固定4字节）
    int* elemAddr = baseAddr + (i * cols + j);
    return *elemAddr;
}

int main() {

    int matrix[3][4] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };
    int rows = 3, cols = 4;
    int* baseAddr = &matrix[0][0]; // 基地址（首元素地址）


    cout << "matrix[1][2] = " << getMatrixElement(baseAddr, rows, cols, 1, 2) << endl; // 输出70
    cout << "matrix[2][3] = " << getMatrixElement(baseAddr, rows, cols, 2, 3) << endl; // 输出120

    getMatrixElement(baseAddr, rows, cols, 3, 0); // 输出"下标越界！"
    return 0;
}