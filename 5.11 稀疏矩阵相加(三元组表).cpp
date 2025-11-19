#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int ElemType;

//定义三元组表结点结构
typedef struct{
    int row,col;    //行数、列数
    ElemType e; //对应的值
}Triple;

//定义三元组顺序表
typedef struct{
    Triple data[MAXSIZE+1]; //数组用来存储三元素表
    int mu,nu,tu;      //分别对应矩阵行数列数和非零元素个数
}TsMaTrix;

//初始化三元组表
void InitTsMaTrix(TsMaTrix &M){
    M.mu=0;
    M.nu=0;
    M.tu=0;
    //data[1]~data[MAXSZIE]的i,j,e全部置零
    for(int k=1;k<=MAXSIZE;++k){
        M.data[k].row=0;
        M.data[k].col=0;
        M.data[k].e=0;
    }
}

//输入原始矩阵，存储在三元组表M中的函数
void createTsMaTrix(TsMaTrix &M){
    int a,b;
    cout<<"请输入矩阵的行数、列数："<<endl;
    cin>>a>>b;
    M.mu=a;
    M.nu=b;
    cout<<"请输入矩阵元素（从上至下，从左至右）:"<<endl;
    for(int i=1;i<=M.mu;i++){
        for(int j=1;j<=M.nu;j++){
            ElemType t;
            cin>>t;
            if(t!=0){   //三元组表只存非零元素
                M.data[M.tu+1].row=i;
                M.data[M.tu+1].col=j;
                M.data[M.tu+1].e=t;
                M.tu++;
            }
        }
    }
}

//稀疏矩阵相加算法(将稀疏矩阵A和B相加并以C存储，ABC都是三元表形式)
//矩阵相加要求A、B 必须同型（行列一样）,结果C的行列数也必须与原矩阵相同
void Add(TsMaTrix &C,TsMaTrix A,TsMaTrix B){
    C.mu=A.mu;
    C.nu=A.nu;
    C.tu=0;
    int i=1;    //i控制遍历A
    int j=1;    //j控制遍历B
    while(i<=A.tu&&j<=B.tu){
        //如果A中的元素在B之前
        if(A.data[i].row<B.data[j].row||
            (A.data[i].row==B.data[j].row&&A.data[i].col<B.data[j].col)){
                C.data[++C.tu]=A.data[i];
                i++;
        }else if(B.data[j].row<A.data[i].row||  //如果B在A之前
            (B.data[j].row==A.data[i].row&&B.data[j].col<A.data[i].col)){
                C.data[++C.tu]=B.data[j];
                j++;
        }else{  //第三种情况，行列数相同，即直接将值相加即可
            int sum=A.data[i].e+B.data[j].e;
            if(sum!=0){
                C.data[++C.tu].row = A.data[i].row;
                C.data[C.tu].col = A.data[i].col;
                C.data[C.tu].e = sum;
                i++;
                j++;
            }
        }
    }
    //处理剩余元素，两个while循环没有先后之分，因为要么A被处理完要么B被处理完，至多一个三元表有剩余
    while(i<=A.tu){
        C.data[++C.tu]=A.data[i];
        i++;
    }
    while(j<=B.tu){
        C.data[++C.tu]=B.data[j];
        j++;
    }

}

//三元组表按照行列扫描输出
void Print(TsMaTrix M){
    cout<<"矩阵相加结果为："<<endl;
    int k=1;
    for(int i=1;i<=M.mu;++i){
        for(int j=1;j<=M.nu;++j){
            if(k<=M.tu&&M.data[k].row==i&&M.data[k].col==j){
                cout<<M.data[k].e<<" ";
                k++;
            }else{
                cout<<0<<" ";
            }
        }
        //一行结束换行
        cout<<endl;
    }
}

int main(){
    TsMaTrix A,B,C;
    InitTsMaTrix(C);
    createTsMaTrix(A);
    createTsMaTrix(B);
    Add(C,A,B);
    Print(C);

    return 0;

}
