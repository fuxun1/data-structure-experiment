#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef char ElemType;

/*算法描述：定义一个栈和一个字符数组，输入字符序列存入字符数组（以#为结束符）
将字符数组元素一个个入栈，再出栈存入一个新的与原字符数组等大的字符数组，
实现字符数组的逆序，比较这两个字符数组每一个位置上的元素是否相等（长度一定相等，无需考虑）*/

//定义栈的存储结构
typedef struct{
    ElemType *base;
    ElemType *top;
    int stacksize;
}Sqstack;

//栈初始化
int InitSqstack(Sqstack &S){
    S.base=new ElemType[MAXSIZE];   //分配内存
    if(!S.base){
        cout<<"内存分配失败"<<endl;
        return ERROR;
    }
    S.top=S.base;
    S.stacksize=MAXSIZE;
    cout<<"内存分配成功"<<endl;
    return OK;
}

//判断栈空函数
bool StackEmpty(Sqstack S){
    return S.top==S.base;
}

//入栈
int Push(Sqstack &S,ElemType e){
    if((S.top-S.base)==S.stacksize){
        cout<<"栈满了"<<endl;
        return ERROR;
    }
    *S.top=e;
    S.top++;
    return OK;
}

//出栈
int Pop(Sqstack &S,ElemType &e){
    if(S.top==S.base){
        cout<<"栈空了"<<endl;
        return ERROR;
    }
    e=*(--S.top);
    return OK;
}

//主函数（动态数组手动扩容）
int main(){
    int n=10;
    char *arr=new char[n];  //arr指向动态数组
    int i=0;
    char ch;
    Sqstack S;
    InitSqstack(S);
    cout<<"请输入字符序列（以#为结束符）："<<endl;
    while(true){
        cin>>ch;
        if(ch=='#'){
            break;
        }else{
            arr[i]=ch;
            i++;
        }
        //判断是否需要扩容
        if(i>=(n-1)){
            int new_n=n*2;
            char *new_arr=new char[new_n];  //创建更大的数组
            //将原数组内容复制过来
            for(int j=0;j<n;j++){
                new_arr[j]=arr[j];
            }
            delete[] arr;
            arr=new_arr;    //让arr指向新数组
            n=new_n;    //更新n的值
        }
    }
    //最终字符数组里有i个元素
    //将字符序列全部入栈(i个字符而不是n个，n只是大小但数组不一定就是满的)
    for(int j=0;j<i;j++){
        Push(S,arr[j]);
    }
    //辅助数组用来存储arr[]的逆序
    char *arr1=new char[n];
    ElemType e;
    int k=0;
    int flag=0;
    while(!StackEmpty(S)){
        Pop(S,e);
        arr1[k]=e;
        k++;
    }
    //比较两个字符数组是否相等
    for(int j=0;j<i;j++){
        if(arr[j]!=arr1[j]){
            flag=1;
            break;
        }
    }
    //输出结果
    if(flag==1){
        cout<<"该字符序列不是回文字符序列"<<endl;
    }else{
        cout<<"该字符序列是回文字符序列"<<endl;
    }

    return 0;
    
}