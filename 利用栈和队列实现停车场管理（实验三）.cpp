//实验3 利用栈和队列实现停车场管理
/*
1.停车场设计为一个栈，汽车让路设计为另一个栈（其实与停车场栈一样），便道上的汽车用队列表示（汽车进出便道用队列来实现）； 
接收命令（A入D出）和车号，需要判断停车场栈是否已满，若不满则入栈，若满则在便道等候； 
2.汽车离开停车场，其他比这辆车后进的车辆为它让路，进入临时栈SqStack2，等这辆车出停车场后，
临时栈中的汽车再出栈回到停车场栈。然后看便道队列是否为空，若不空，
则说明有汽车等候，从队头取出汽车号，让该车入停车场栈。 
3.重复1、2直到为退出命令（车号为0或负数）
*/
//功能：手动输入不同车号和进出命令，直到最后输入0退出，最后输出此时便道和停车场的车辆状态 

#include<iostream>
using namespace std;

#define MAXSIZE 5	//最大栈长度
#define MAXQSIZE 100	//最大队列长度 
#define OK 1
#define ERROR 0
typedef int ElemType;

//定义停车场栈SqStack
typedef struct{
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack; 


//定义便道队列 
typedef struct{
	ElemType *base;	//base指针指向队列的首地址，base可代指队列
	int front; 	//队头下标 
	int rear;	//队尾下标 
}SqQueue;





//构造一个空栈 
int InitStack(SqStack &S){ 
	S.base=new ElemType[MAXSIZE];
	if(!S.base){
		cout<<"空间分配失败"<<endl;
		exit(1);
	} 
	S.top=S.base;
	S.stacksize=MAXSIZE;
	cout<<"内存分配成功"<<endl;
	return OK; 
}

//判断顺序栈是否为空(空栈条件为top指针等于base指针) 
bool StackEmpty(SqStack S){
	if(S.top==S.base){
		return true;
	}else{
		return false;
	}
} 

//判断顺序栈是否为满（返回ture为满）
bool StackFull(SqStack &S) {
	if(S.top-S.base==S.stacksize){
		return true;
	}else{
		return false;
	}
}

//顺序栈的入栈
int Push(SqStack &S,ElemType e){
	if(S.top-S.base==S.stacksize){
		return ERROR;
	}
	*S.top=e;
	S.top++;
	return OK;
}

//顺序栈的出栈
int Pop(SqStack &S,ElemType &e){
	if(S.top==S.base){
		return ERROR;
	}
	S.top--;
	e=*S.top;
	return OK;
}

//求顺序栈的长度
int StackLength(SqStack S){
	return S.top-S.base;
}

//队列的初始化
int InitQueue(SqQueue &Q){
	Q.base=new ElemType[MAXQSIZE];	 
	if(!Q.base){
		return ERROR;
	}
	Q.front=Q.rear=0;
	return OK;
} 

//判断循环队列是否为空
bool QueueEmpty(SqQueue Q){
	if(Q.front==Q.rear){
		return true;
	}else{
		return false;
	}
} 

//求循环队列的长度
int QueueLength(SqQueue Q){
	return((Q.rear-Q.front+MAXQSIZE)%MAXQSIZE);
	//实际就是(MAXQSIZE - front) + rear，然后为了保证一般情况（即rear>=front）也适用于此公式就再对MAXQSIZE取模
	//因为当rear>=front时，rear-front就已经得到元素个数，再加MAXQSIZE就多了，所以再通过%MAXQSIZE去掉 
	//总之，Q.rear-Q.front+MAXQSIZE其实就已经得到结果，%MAXQSIZEW只是为了统一两种情况 
}

//循环队列的入队
int EnQueue(SqQueue &Q,ElemType e){
	if((Q.rear+1)%MAXQSIZE==Q.front){	//判断队列是否已满（循环队列要留一个位置，所以只剩队尾一个位置就算满了） 
		return ERROR;
	}
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;		//队尾指针rear指向下一个位置
	return OK; 
} 

//循环队列的出队
int DeQueue(SqQueue &Q,ElemType &e){
	//先判断队列是否为空
	if(Q.front==Q.rear) {
		return ERROR;
	}
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXQSIZE;	//队头指针+1 
	return OK;
}

//进车函数
void EnterCar(int carNum,SqStack &S,SqQueue &Q){
		//如果停车场栈未满 
		if(!StackFull(S)){
			Push(S,carNum);
		}else{
			EnQueue(Q,carNum);	//栈满则入队 
		}		
} 

//出车函数
void ExitCar(int carNum,SqStack &S1,SqStack &S2,SqQueue &Q){
	int temp;
	int flag=0; 	//标记，判断是否在停车场栈中能否找到要出的车，找到了就更改为1; 
	//不断的把栈顶元素拿出来再存入临时栈S2，直至最后把需要出车的车辆拿出但是不存入S2（相当于现实中车直接开走），直接break; 
	ElemType *p=S1.base;
	while(p<S1.top){
		if(*p==carNum){
			flag=1;
			break;
		}
		p++;
	}
	if(!flag){
		cout<<"未找到车号"<<carNum<<" "<<"无法出车"<<endl;
		return;
	}
	int len=StackLength(S1);
	for(int i=0;i<len;i++){
		if(StackEmpty(S1)){
			break;
		}
		Pop(S1,temp);
		if(temp!=carNum){
			Push(S2,temp);
		}else if(temp==carNum){
			cout <<"车号 "<<carNum<<"已离开停车场"<<endl;
			break;
		}
	}
	//出车之后，再把临时栈S2中的元素一个个入栈
	while(!StackEmpty(S2)){
		Pop(S2,temp);
		Push(S1,temp);
	} 
	//出车之后，停车场栈顶空出一个位置，判断队列中是否有车，有车就把队头元素入栈
	//因为是循环队列，所以队头元素入栈后其余队中元素不用平移 
	if(!QueueEmpty(Q)){
		DeQueue(Q,temp);
		Push(S1,temp);
		cout<<"便道中车号"<<temp<<"进入停车场"<<endl;
	}
} 

//输出函数（从栈底输出）：用于最后显示停车场状态 
void PrintStack(SqStack S){
	ElemType *p=S.base;
	cout << "停车场中的车辆（从栈底到栈顶）：" << endl;
	while(p<S.top){
		cout<<*p<<endl;
		p++;
	}
}

//输出函数（从队头开始输出）：用于最后显示辅道状态 
void PrintQueue(SqQueue Q){
	int i=Q.front;
	cout<<"便道中的车辆："; 
	while(i!=Q.rear) {
		cout<<Q.base[i]<<" ";
		i=(i+1)%MAXQSIZE; 
	}
	cout<<endl;
}

int main(){
	char cmd;	//命令
	int carNum;	//车号
	SqStack S1,S2;	//停车场栈和临时栈 
	SqQueue Q;
	//栈和队列初始化 
	InitStack(S1);
	InitStack(S2);
	InitQueue(Q);
	//不断输入命令和车号直到输入为0或负数跳出循环 
	cout<<"请输入命令和车号："<<endl;
	while (cin >> cmd) {
    	if (cmd == '0') break;  // 只看命令是否为'0'
    	cin >> carNum;
    	if (cmd == 'A') {
        EnterCar(carNum, S1, Q);
    	} else if (cmd == 'D') {
        ExitCar(carNum, S1, S2, Q);
    	}
	}
	cout << "程序结束" << endl;
	PrintStack(S1);
	PrintQueue(Q);
	
	return 0;
}
 


