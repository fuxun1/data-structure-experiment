#include<string.h>
#include<iostream>
using namespace std;

#define MAXLEN 100
#define OK 1
#define ERROR 0
typedef char ElemType;

typedef struct{
    ElemType ch[MAXLEN+1];
    int length;
}SString;



//删除串S的第pos个字符起长度为len的子串
int StrDelete(SString &S,int pos,int len){
    if(pos<1||pos>S.length-len+1||len<0||pos>S.length)return ERROR;
    //关键是要理清下标间的关系，待删除子串之后的第一个元素位置为pos+len;
    //要删len个元素，就是把后面的所有元素前移覆盖住待删除元素
    for(int i=pos+len;i<=S.length;i++){
        S.ch[i-len]=S.ch[i];
    }
    S.length-=len;
    return OK;
}

/*算法描述：从串S的第一个字符开始与T进行匹配，若匹配成功，记录下pos位置，
从pos位置起删除长度为T.length的字串，串S长度减小，继续从当前位置进行匹配，
若匹配失败，i自增1，重复上述步骤直到扫描完完整个串S*/
int DeleteSub(SString &S,SString T){
    for(int i=1;i<=S.length-T.length+1;i++){
        int flag=0;
        for(int j=1;j<=T.length;j++){
            if(S.ch[i+j-1]!=T.ch[j]){
                flag=1;
                break;
            }
        }
        if(flag==0){
            StrDelete(S,i,T.length);    //StrDelete里面已经减了S的长度，这里就要不用再减了
            //i回退，为了继续从当前位置匹配
            i-=1;
        }        
    }
}

//初始化串S
void InitString(SString &S){
    S.length=0;
}

//主函数测试
int main(){
    SString S;
    SString T;
    InitString(S);
    InitString(T);
    cout<<"请输入串S:"<<endl;
    cin>>S.ch+1;
    //获取S的长度
    while(S.ch[S.length+1]!='\0'){
        S.length++;
    }
    cout<<"请输入串T:"<<endl;
    cin>>T.ch+1;
    //获取T的长度
    while(T.ch[T.length+1]!='\0'){
        T.length++;
    }
    DeleteSub(S,T);
    cout<<"删除所有与T相同的字串后的S为:";
    for(int i=1;i<=S.length;i++){
        cout<<S.ch[i]<<" ";
    }
    cout<<endl;
    return 0;
    
}


