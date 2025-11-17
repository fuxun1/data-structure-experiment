#include<iostream>
using namespace std;

#define MAXSIZE 10
#define OK 1
#define ERROR 0
typedef int ElemType;

//循环队列，length记录内含元素个数，rear指向队尾元素位置

//循环队列数据存储结构
typedef struct{
    ElemType  *base;    //指向队列内存首地址
    int rear;       //指向队尾元素
    int length;     //队列元素个数
}CirQueue;

//循环队列初始化
void InitCirQueue(CirQueue &Q){
    Q.base=new ElemType[MAXSIZE];   //分配空间
    Q.rear=-1;
    Q.length=0;
}

//入队操作
void EnQueue(CirQueue &Q,ElemType e){
    if(Q.length==MAXSIZE){
        cout<<"队列已满"<<endl;
        return;
    }
    Q.rear=(Q.rear+1)%MAXSIZE;
    Q.base[Q.rear]=e;
    Q.length++;
}

//计算队头位置
int Getfront(CirQueue &Q){
    return (Q.rear-Q.length+1+MAXSIZE)%MAXSIZE;
}

//获取队头元素(不删除)
 int getHead(CirQueue Q,ElemType &e){
    if(Q.length==0){
        cout<<"队列为空"<<endl;
        return ERROR;
    }
    e=Q.base[Getfront(Q)];
    return OK;
 }

//出队操作
ElemType DeQueue(CirQueue &Q,ElemType &e){
    if(Q.length==0){
        cout<<"队列为空"<<endl;
        return ERROR;
    }else{
        //通过rear和length计算队头元素位置，即队头元素位置=(rear-length+1+MAXSIZE)%MAXSIZE
        e=Q.base[Getfront(Q)];
        Q.length--;
        return e;
    }
}

//队列打印输出（重要）
int Print(CirQueue Q){
    if(Q.length==0){
        cout<<"队列为空"<<endl;
        return ERROR;
    }
    int front=Getfront(Q);  //front为队头元素位置
    for(int i=0;i<Q.length;i++){
        int index=(front+i)%MAXSIZE;
        cout<<Q.base[index]<<" ";
    }
    cout<<endl;
    return OK;
}

//主函数
int main(){
    CirQueue Q;
    InitCirQueue(Q);
    ElemType e;
    int i=5;
    cout<<"请输入入队元素：";
    while(i>0){
        cin>>e;
        EnQueue(Q,e);
        i--;
    }
    int k=DeQueue(Q,e);
    cout<<"出队元素为："<<k<<endl;
    cout<<"此时队列为：";
    Print(Q);


    return 0;
}