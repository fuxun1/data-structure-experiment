#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

//学生信息结构 
typedef struct{
char student_id[9];
char student_name[11];
int score;
int time;
}Student;

//双向循环链表结构 
typedef struct DuLNode{
Student data;
struct DuLNode *prior;
struct DuLNode *next;
}DuLNode,*DuLinkList;

//创建空链表（头节点）
DuLinkList InitList(){
DuLNode *L=(DuLNode *)malloc(sizeof(DuLNode));
if(L==NULL){
return NULL;}
//只有一个头节点，所以next和prior指针都指向自身 
L->next=L;
L->prior=L;
return L; 
} 

//创建数据节点
DuLNode * CreateNode(Student e){
DuLNode *newNode=(DuLNode*)malloc(sizeof(DuLNode));
if (newNode==NULL){
return NULL;
}
newNode->data=e;
//将创建的新节点的next和prior指针暂时初始化为空 
newNode->next=NULL;
newNode->prior=NULL;
return newNode;
} 

// 在链表尾部插入新节点（保持数组的顺序）
void InsertTail(DuLinkList L, DuLNode *newNode) {
    DuLNode *tail = L->prior;  // 尾节点是头节点的前驱（循环链表特性） 
    newNode->next = L;         // 新节点的next指向头节点 
    newNode->prior = tail;     // 新节点的prior指向原尾节点 
    tail->next = newNode;      // 原尾节点的next指向新节点 
    L->prior = newNode;        // 头节点的prior指向新节点（更新尾节点） 
}


//从文件读取学生数据 
void ReadFile(DuLinkList L,const char *filename){	//文件名以指针形式传入 
	// 修复：使用传入的filename参数而非硬编码，增强通用性
	FILE *fp=fopen(filename,"r");
	if(fp==NULL){
		printf("文件打开失败\n");
		return ; 
	}
	Student temp;
	// 修复：判断是否成功读取4个字段，避免不完整数据干扰
	while(fscanf(fp,"%s %s %d %d",temp.student_id,temp.student_name,&temp.score,&temp.time)==4){
		DuLNode *newNode=CreateNode(temp);
		if(newNode!=NULL){  // 增加节点创建失败的判断
			InsertTail(L,newNode);
		}
	}
	fclose(fp);
} 

//定义输出链表函数
void PrintList(DuLinkList L){
	if(L->next==L){
		printf("链表为空\n");
		return ;
	}
	DuLNode *p=L->next;
	printf("学号\t\t姓名\t\t成绩\t\t所用时间\n");
	while(p!=L){
		printf("%s\t%s\t\t%d\t\t%d\t\n",p->data.student_id,p->data.student_name,p->data.score,p->data.time);
		p=p->next;
	}
	printf("\n");
} 

//快速排序自定义比较函数 （按成绩降序，成绩相同按时间升序）
int CompareStudent(const void *a,const void *b) {
	//定义两个指针指向两个Student结构体(强制类型转换）  
	Student *s1=(Student *)a;
	Student *s2=(Student *)b;
	if(s1->score!=s2->score){
		return s2->score-s1->score;
	}else{
		return s1->time-s2->time;
	}
	
}

void SortList(DuLinkList L){
	if(L->next==L){
		return ;
	}
	int count = 0;
	DuLNode *p=L->next;
	//统计结点数量 
	while(p!=L){
		count++;
		p=p->next;
	}
//动态创建数组存所有学生数据
//这里*arr等价于arr[] 
//数组中元素数量为节点数，每个元素又存了学生的学号、姓名、成绩、时间数据 
Student *arr=(Student *)malloc(count * sizeof(Student)) ;
// 增加内存分配失败的判断
if(arr==NULL){
	printf("内存分配失败\n");
	return;
}
p=L->next;
//把链表数据复制到数组中
for(int i=0;i<count;i++) {
	arr[i]=p->data;
	p=p->next;
}
//快速排序
qsort(arr,count,sizeof(Student),CompareStudent);
// 修复：清空原链表时正确处理头节点指针（可选）
//说白了就是从第一个数据节点开始一个个释放 
p=L->next;
DuLNode *temp;
while(p!=L){
	temp=p;
	p=p->next;
	free(temp);
} 
// 恢复头节点循环状态（关键修复：确保清空后是标准空链表）
L->next=L;
L->prior=L;
// 重新插入排序后的节点
for(int i=0;i<count;i++){
	DuLNode *newNode=CreateNode(arr[i]);
	if(newNode!=NULL){  // 增加节点创建失败的判断
		InsertTail(L,newNode); 
	}
}
free(arr);

}

int main(){
	DuLinkList L=InitList();
	if(L==NULL) {
		printf("链表初始化失败\n");
		return 1; 
	}
	ReadFile(L,"student.txt");
	printf("===排序前的学生信息===\n");
	PrintList(L);
	SortList(L);
	printf("===排序后的学生信息===\n");
	PrintList(L);
	return 0; 
}
