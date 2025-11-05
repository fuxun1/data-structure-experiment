//4.5 括号匹配
//2025.11.5
/*算法思路：从左到右扫描表达式，利用栈，左括号入栈，遇到右括号，如果栈为空，不合法，否则将栈顶元素弹出，
与当前右括号进行匹配，若能匹配则合法，否则不合法，依次类推， 直至扫描完毕，若栈空则合法，否则不合法*/ 

#include<iostream>
#include<stdlib.h>
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

//判断栈是否为空
bool StackEmpty(SqStack S){
	if(S.top==S.base){
		return true;
	}else{
		return false;
	}
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
		return ERROR;
	}
	S.top--;
	e=*S.top;
	return OK;
} 

//判断括号是否匹配函数
int Compare(SElemType e1,SElemType e2){
	if((e1=='('&&e2==')')||(e1=='['&&e2==']')){
		return OK;
	}else{
		return ERROR;
	}
} 

int main(){
	SqStack S;
	InitStack(S);
	int n=10;	//初始数组容量 
	char ch;
	char *str=new char[n];
	cout<<"请输入表达式（输入@表示结束）："<<endl;
	int i=0;
	while(cin.get(ch)&&ch!='@'){
		if(i>=n){
			n*=2;
			char *str2=new char[n];
			for(int j=0;j<n;j++){
				str2[j]=str[j];
			}
			delete[] str;		//把指针str所指向的那块动态分配的数组内存释放掉
			str=str2;		//让str指针现在指向str2指针所指的内存区域（这是指针赋值操作而非字符串复制） 
		}
		str[i++]=ch;
	}
	SElemType temp;
	int k;
	int flag=1;		//标志，默认值为1，0表示出现了匹配失败的情况 
	for(int j=0;j<i;j++){
		if(str[j]=='('||str[j]=='['){
			Push(S,str[j]);
		}else if(str[j]==')'||str[j]==']'){
			Pop(S,temp);
			k=Compare(temp,str[j]);
			if(k==0){
				cout<<"括号匹配不合法"<<endl;
				flag=0;
				break;
			}
		}
	}
	
	//遍历完毕后，如果栈为空（意味着入栈的全部弹出）且flag=1（意味着匹配从未失败），则括号匹配合法 
	if(StackEmpty(S)&&flag==1){
		cout<<"括号匹配合法"<<endl;
	}
	
	return 0;
	
}
 
 
