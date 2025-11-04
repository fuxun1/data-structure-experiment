//4.3 火车调度
//2025.11.4
// 软席车厢S用0表示，硬席车厢H用1表示 
//功能：对n节车厢进行调度，要求所有的软席车厢都被调整到硬席车厢之前 

#include<iostream>
#include<stdlib.h>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef int  SElemType;

//定义栈 
typedef struct{
	SElemType *top;		//栈顶指针 
	SElemType *base;	//栈底指针 
	int stacksize; 
}SqStack;

//构造空栈
int InitStack(SqStack &S){
	S.base=new SElemType[MAXSIZE];	//开辟内存
	if(!S.base){
		cout<<"内存空间分配失败"<<endl;
		exit(1);
	}
	S.base=S.top;
	S.stacksize = MAXSIZE;
	cout<<"内存分配成功"<<endl;
	return OK;
} 

//顺序栈入栈
int Push(SqStack &S,SElemType e){
	if(S.top-S.base==S.stacksize){
		cout<<"栈满了"<<endl;
		return ERROR;
	}
	*S.top=e;
	S.top++;
	return OK;
} 

//顺序栈出栈
int Pop(SqStack &S,SElemType &e){
	if(S.top==S.base){
		cout<<"栈空了"<<endl;
		return ERROR;
	}
	S.top--;
	e=*S.top;
	return OK;
} 

//遍历n节车厢，若为软车厢，入栈后立马出栈，若为硬车厢，仅入栈，等遍历结束再依次出栈 
int main(){
	int n;
	cout<<"请输入车厢数："<<endl;
	cin>>n;
	int arr1[n];		//数组用来存储待入栈车厢
	int arr2[n];		//用来存储出栈车厢
	SqStack S; 
	InitStack(S);
	printf("请输入这%d节车厢的类别（0或1）：",n);
	for(int j=0;j<n;j++){
		cin>>arr1[j];
	} 
	int m=0;
	int temp;
	for(int k=0;k<n;k++){
		if(arr1[k]==0){
			Push(S,arr1[k]);
			Pop(S,temp);
			arr2[m]=temp;
			m++;
		}
		else if(arr1[k]==1){
			Push(S,arr1[k]);
		}
	}
	//将入栈的硬车厢出栈，存入arr2数组
	while(!(S.base==S.top)){
		Pop(S,arr2[m]);
		m++;
	} 
	
	cout<<"最后的车厢顺序为："<<endl;
	for(int i=0;i<n;i++){
		cout<<arr2[i]<<" ";
	}
	cout<<endl;
	
	return 0;
	
}
