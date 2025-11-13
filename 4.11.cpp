#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 10  

// 循环队列
typedef struct {
    int arr[MAX_CAPACITY];  // 存储元素的数组
    int rear;               // 指向队尾元素位置
    int length;             // 当前元素个数
} CircQueue;

// 初始化队列
void initQueue(CircQueue *q) {
    q->rear = -1;   
    q->length = 0;  
}

// 判断队列是否为空
int isEmpty(CircQueue *q) {
    return q->length == 0;
}

// 判断队列是否已满
int isFull(CircQueue *q) {
    return q->length == MAX_CAPACITY;
}

// 入队操作
void enQueue(CircQueue *q, int x) {
    if (isFull(q)) {
        printf("队列已满，无法入队元素 %d！\n", x);
        return;
    }
    // 计算下一个队尾位置
    q->rear = (q->rear + 1) % MAX_CAPACITY;
    q->arr[q->rear] = x;  // 存入元素
    q->length++;          // 元素个数加1
}

// 出队操作（返回队头元素，失败返回-1）
int deQueue(CircQueue *q) {
    if (isEmpty(q)) {
        printf("队列为空，无法出队！\n");
        return -1;
    }
    // 计算队头位置：(rear - length + 1 + 容量) % 容量
    int frontPos = (q->rear - q->length + 1 + MAX_CAPACITY) % MAX_CAPACITY;
    int val = q->arr[frontPos];  
    q->length--;                 
    return val;
}

// 获取队头元素（不删除，失败返回-1）
int getFront(CircQueue *q) {
    if (isEmpty(q)) {
        printf("队列为空，无队头元素！\n");
        return -1;
    }
    int frontPos = (q->rear - q->length + 1 + MAX_CAPACITY) % MAX_CAPACITY;
    return q->arr[frontPos];
}

// 打印队列元素
void printQueue(CircQueue *q) {
    if (isEmpty(q)) {
        printf("队列为空\n");
        return;
    }
    printf("队列元素（队头到队尾）：");
    int frontPos = (q->rear - q->length + 1 + MAX_CAPACITY) % MAX_CAPACITY;
    for (int i = 0; i < q->length; i++) {
        int pos = (frontPos + i) % MAX_CAPACITY;
        printf("%d ", q->arr[pos]);
    }
    printf("\n");
}

int main() {
    CircQueue q;
    initQueue(&q);

    // 测试入队
    enQueue(&q, 10);
    enQueue(&q, 20);
    enQueue(&q, 30);
    printQueue(&q);  

    // 测试出队
    printf("出队元素：%d\n", deQueue(&q));  
    printQueue(&q);  

    // 继续入队直到满
    enQueue(&q, 40);
    enQueue(&q, 50);
    enQueue(&q, 60);
    enQueue(&q, 70);
    enQueue(&q, 80);
    enQueue(&q, 90);
    enQueue(&q, 100);
    enQueue(&q, 110);
    printQueue(&q);  

    // 测试队满
    enQueue(&q, 120);  

    // 测试出队所有元素
    printf("出队顺序：");
    while (!isEmpty(&q)) {
        printf("%d ", deQueue(&q));
    }
    // 输出：20 30 40 50 60 70 80 90 100 110
    printf("\n");

    // 测试队空
    deQueue(&q);  

    return 0;
}