#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int ElemType;

//循环链表节点结构
typedef struct Node{
    ElemType data;
    struct Node* next;
}Node,*LinkList;

//队列结构
typedef struct{
    LinkList rear;  //尾指针指向尾节点
}Queue;

//队列初始化操作
void InitQueue(Queue &Q){
    //创建头节点
    Node *head=new Node; //new用指针变量接受
    //头节点的指针域及尾指针均指向头节点（既是头节点也是尾节点）
    head->next=head;    //等号两端不能颠倒，因为只有head是new出来的有效指针
    Q.rear=head;
}

//入队列操作
void EnQueue(Queue &Q,ElemType e){
    //先创建新节点然后连接
    Node *newNode=new Node;
    newNode->data=e;
    newNode->next=Q.rear->next;
    Q.rear->next=newNode;
    //更新尾指针（尾节点）
    Q.rear=newNode;
}

//出队列操作(只剩最后一个元素出队列的情况搞了半天，多看多想几遍)
void DeQueue(Queue &Q,ElemType &e){
    //队列出队是队头元素出队，队头元素（第一个数据元素）要通过头节点寻找，头节点又要通过尾指针寻找
    //思路：把第一个数据元素的值赋值给e，然后让头节点指针指向队头元素的下一个节点即可
    if(Q.rear->next==Q.rear){   //头节点自己指向自己（无可出队元素）
        return ;
    }
    Node *head=Q.rear->next;  //尾节点指针域指向头节点
    Node *p=head->next; //p指向第一个数据节点
    e=p->data;
    head->next=p->next; //连接头节点和队头节点的下一个节点
    //特殊情况处理（只剩一个元素时）
    if(p==Q.rear){  //第一个数据节点（队头）刚好也是尾节点
        Q.rear=head;
    }
    delete p;   //再把队头节点删掉
    return;
}

//判断是否队空
bool QueueEmpty(Queue &Q){
    if(Q.rear->next==Q.rear){
        return true;
    }else{
        return false;
    }
}

//测试
int main(){
    Queue Q;
    InitQueue(Q);
    ElemType e;
    cout<<"请输入入队元素："<<endl;
    int i=5;
    while(i>0){
        cin>>e;
        EnQueue(Q,e);
        i--;
    }
    cout<<"队列为:";
    while(!QueueEmpty(Q)){
    DeQueue(Q,e);
    cout<<e<<" ";
    }


    return 0;

}