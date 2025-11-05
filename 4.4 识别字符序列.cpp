//4.4序列识别
//识别依次读入的以“@”为结束符的字符序列是否为形如"序列1&序列2"模式的字符序列
//2025.11.5

#include<iostream>
#include<stdlib.h>
#include <cstring>  // strcmp 在这里面
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef char  SElemType; 

//定义栈
typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

//构造空栈
int InitStack(SqStack &S){
	S.base=new SElemType[MAXSIZE];
	if(!S.base){
		cout<<"分配内存失败"<<endl;
		exit(1);
	}
	S.top=S.base;
	S.stacksize=MAXSIZE;
	cout<<"内存分配成功"<<endl;
	return OK;
} 

//入栈
int Push(SqStack &S,SElemType e){
	if((S.top-S.base)==S.stacksize){
		cout<<"栈满了"<<endl; 
	}
	*S.top=e;
	S.top++;
	return OK;
} 

//出栈
int Pop(SqStack &S,SElemType &e){
	if(S.top==S.base){
		cout<<"栈空了"<<endl;
	}
	S.top--;
	e=*S.top;
	return OK;
} 

int main(){
	SqStack S;
	InitStack(S);
	int n=10;	//字符数组初始容量 
	int i=0;
	char ch;
	char *str=new char[n];
	cout<<"请输入字符序列str："<<endl; 
	while(cin.get(ch)&&ch!='@'){
		//动态分配内存大小 
		if(i>=n-1){
			n*=2;
			char *newstr=new char[n];
			for(int j=0;j<=i;j++){
				newstr[j]=str[j];
			}
			delete[] str;
			str=newstr;
		}
		str[i++]=ch;
	} 
	str[i]='\0';
	char str2[n];
	for(int j=0;j<i;j++){
		SElemType temp;
		temp=str[j];
		Push(S,temp);
	}
	for(int j=0;j<i;j++){
		SElemType temp;
		Pop(S,temp);
		str2[j]=temp;
	}
	str2[i]='\0';
	int m=(i/2);
	if(strcmp(str,str2)==0&&str[m]=='&'){
		cout<<"str是符合规则的字符序列"<<endl;
	}else{
		cout<<"str不是符合规则的字符序列"<<endl;
	}
	
	return 0; 
}





 
