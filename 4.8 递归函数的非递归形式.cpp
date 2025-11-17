#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int ElemType;

//定义栈元素
typedef struct{
    int m;
    int n;
}StackElemType; //栈元素类型

//定义栈（顺序栈）
typedef struct{
    StackElemType *top;
    StackElemType *base;
    int stacksize;  //栈的大小
}SqStack;

//初始化栈操作
int InitStack(SqStack &S){
    S.base= new StackElemType[MAXSIZE];
    if(!S.base){
    cout<<"内存分配失败"<<endl;
    return ERROR;
    }
    S.top=S.base;
    S.stacksize=MAXSIZE;
    cout<<"内存分配成功"<<endl;
    return OK;
}

//入栈操作
void Push(SqStack &S,StackElemType e){
    if(S.top-S.base==S.stacksize)return;
    *S.top=e;
    S.top++;
}

//出栈操作
void Pop(SqStack &S,StackElemType &e){
    if(S.top==S.base)return;
    S.top--;
    e=*S.top;
}

//判断栈空函数
bool StackEmpty(SqStack S){
    if(S.top==S.base)return true;
    else return false;
}

/*算法描述：让初始(m,n)入栈，不断循环获取栈顶元素，判断栈顶元素中的m是否大于0，如果>0,再让子问题入栈
直至栈顶元素的m等于0，退出循环
再到求累计和部分，先把栈顶元素弹出(g(0,m)=0),再进入循环，只要栈不为空，
就不断拿出栈顶元素同时将其n累加，得到结果返回*/
int stackBasedGCalculation(SqStack &S,StackElemType e){
    int result=0;
    Push(S,e);
    while(true){
        StackElemType TopElem=*(S.top-1);   //拿栈顶元素副本
        if(TopElem.m>0){
            StackElemType t;
            t.m=TopElem.m-1;
            t.n=TopElem.n*2;
            Push(S,t);
        }else{
            break;
        }
    }
    Pop(S,e);
    while(!StackEmpty(S)){
        Pop(S,e);
        result+=e.n;
    }
    return result;
}

int main(){
    SqStack S;
    InitStack(S);
    StackElemType e;
    cout<<"请输入参数m,n:"<<endl;
    cin>>e.m>>e.n;
    int k=stackBasedGCalculation(S,e);
    cout<<"g(m,n)="<<k<<endl;

    return 0;

}