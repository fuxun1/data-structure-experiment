#include <iostream>
using namespace std;

// 计算二维数组元素地址（行主序）
int calcAddress(int base, int i, int j, int cols, int elemSize) {
    // 公式：LOC[i][j] = 基地址 + (i * 列数 + j) * 元素大小
    return base + (i * cols + j) * elemSize;
}

// 按列存储地址计算
int calcAddressColMajor(int base, int i, int j, int rows, int elemSize) {
    // 公式：LOC[i][j] = 基地址 + (j * 行数 + i) * 元素大小
    return base + (j * rows + i) * elemSize;
}

int main() {
    cout << "数组体积：" << 6 * 8 * 6 << "字节" << endl; // 288
    cout << "a[5][7]地址：" << calcAddress(1000, 5, 7, 8, 6) << endl; // 1282
    cout << "a[1][4]行存储地址：" << calcAddress(1000, 1, 4, 8, 6) << endl; // 1072
    cout << "a[4][7]列存储地址：" << calcAddressColMajor(1000, 4, 7, 6, 6) << endl; // 1276
    return 0;
}