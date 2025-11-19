//功能要求：利用串的基本操作和栈和集合的基本操作实现将前缀表达式转换为后缀表达式(操作数为单个字符字母)
/*算法描述：对表达式从右往左扫描，操作数入栈，遇到运算符时，从栈里面弹出两个操作数和这个运算符
组成一个新元素再入栈（运算符放在后面），依此类推直至将原表达式扫描完毕，再逐个出栈输出*/

#include<iostream>
#include <string>
using namespace std;

#define MAXSIZE 100 //栈的最大容量
#define MAXLEN  100    //串的最大长度
#define OK 1
#define ERROR 0


//定义串的存储架构
typedef struct{
    char ch[MAXLEN+1];
    int length;
}SString;

//定义栈的存储结构
typedef struct{
    SString* top;
    SString* base;
    int stacksize;
}SqStack;

//构造一个空栈 
int InitStack(SqStack &S){
	//在内存中找一块能存放MAXSIZE个元素的内存，并让base指针指向这块空间的首地址（等价于指向这块空间） 
	S.base=new SString[MAXSIZE];
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

//顺序栈的入栈（先判断栈是否满了，满了则报错，没满则把元素e存到top指针位置,top指针上移）
int Push(SqStack &S,SString e){
	if(S.top-S.base==S.stacksize){
		return ERROR;
	}
	*S.top=e;
	S.top++;
	//*S.top++=e;
    return OK;
}

//顺序栈的出栈（先判断栈是否空了，空了则出错，没空则先将top指针下移，再将top指针所指的元素出栈） 
int Pop(SqStack &S,SString &e){
	if(S.top==S.base){
		return ERROR;
	}
	S.top--;
	e=*S.top;
	return OK;
}

//初始化串S
void InitString(SString &S){
    S.length=0;
}

//运算符集合（使用数组(顺序表)表示）
char operators[]={'+','-','*','/','^','(',')'};
int operatorCount=7;

//操作数集合(26大写＋26小写)
char operands[52];
int operandCount=0;
void InitOperands(){
    //添加A~Z
    for(char i='A';i<='Z';i++){     //利用ASCLL表遍历
        operands[operandCount++]=i;
    }
    //添加a~z
    for(char i='a';i<='z';i++){
        operands[operandCount++]=i;
    }
}

//判断字符属于哪个集合(属于运算符返回0,,属于操作数返回1)
int getCharType(char c){
    for(int i=0;i<operandCount;i++){
        if(c==operands[i]){
            return 1;
        }
    }
    for(int i=0;i<operatorCount;i++){
        if(c==operators[i]){
            return 0;
        }
    }
    return -1;
} 

//辅助函数：将单个字符转换为SString类型方便入栈（因为栈元素类型定义为了SString类型）
void charToSString(SString &S,char c){
    S.ch[1]=c;
    S.length=1;
    S.ch[2]='\0';
    
}

//辅助函数：连接两个SString和一个运算符，形成新的SString,以串T接收
int ConcatSStrings(SString &T,SString A,SString B,char op){
    InitString(T);
    //把第一个SString放进去(先出栈的)
    for(int i=1;i<=A.length;++i){
        T.ch[T.length+1]=A.ch[i];
        T.length++;
    }
    //再把第二个SString放进去(后出栈的)
    for(int i=1;i<=B.length;++i){
        T.ch[T.length+1]=B.ch[i];
        T.length++;
    }
    //再把运算符接在后面
    T.ch[T.length+1]=op;
    T.length+=1;
    //加字符串结束符
    T.ch[T.length+1]='\0';

    return OK;
}


//主函数
int main(){
    SString S1;     //存储前缀表达式
    SqStack S2;
    InitStack(S2);
    InitString(S1);
    InitOperands();
    cout<<"请输入前缀表达式："<<endl;
    cin>>S1.ch+1;
    //计算S1的长度
    while(S1.ch[S1.length+1]!='\0'){
        S1.length++;
    }
    //对S1从右往左扫描
    for(int i=S1.length;i>0;i--){
        if(getCharType(S1.ch[i])==1){   //返回1表示操作数，入栈
            SString temp;
            InitString(temp);
            charToSString(temp,S1.ch[i]);
            Push(S2,temp);
        }else if(getCharType(S1.ch[i])==0){     //遇到运算符，从栈中弹出两个操作数连接运算符再入栈
            SString e1,e2,T;
            InitString(e1);
            InitString(e2);
            InitString(T);
            Pop(S2,e1);
            Pop(S2,e2);
            ConcatSStrings(T,e1,e2,S1.ch[i]);
            Push(S2,T);
        }
    }
    cout<<"后缀表达式形式为:"<<endl;
    SString r;
    while(!StackEmpty(S2)){
        Pop(S2,r);
        for(int i=1;i<=r.length;i++){
            cout<<r.ch[i];
        }
    }

    return 0;

}