#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d = 0) : data(d), next(nullptr) {}
};

class Queue {
private:
    Node* rear; // 仅指向队尾节点
public:
    Queue() : rear(nullptr) {}

    // 初始化队列
    void initQueue() {
        rear = nullptr;
    }

    // 入队
    void enQueue(int x) {
        Node* newNode = new Node(x);
        if (rear == nullptr) {
            rear = newNode;
            rear->next = rear;
        } else {
            newNode->next = rear->next;
            rear->next = newNode;
            rear = newNode;
        }
    }

    // 出队（返回队头元素）
    int deQueue() {
        if (rear == nullptr) {
            cerr << "队列为空！" << endl;
            return -1;
        }
        Node* frontNode = rear->next;
        int val = frontNode->data;
        if (frontNode == rear) {
            rear = nullptr;
        } else {
            rear->next = frontNode->next;
        }
        delete frontNode;
        return val;
    }
};

int main() {
    Queue q;
    q.initQueue();
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);
    cout << q.deQueue() << endl; // 输出1
    cout << q.deQueue() << endl; // 输出2
    return 0;
}