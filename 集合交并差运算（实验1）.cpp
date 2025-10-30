//正整数集合的交、并和差运算（数据结构第一次实验报告）
//2025.9.25
//c++
#include <iostream>
using namespace std;

/*有序链表部分*/ 
 
// 元素类型
typedef int ElemType;

// 结点类型（结点中有数据域和指针域）
typedef struct NodeType {
    ElemType data;		// 数据域：存储节点的实际数据
    NodeType *next;		// 指针域：存储下一个节点的地址，实现节点间的“链接”，类型是NodeType*，即指向NodeType类型的指针 
} NodeType, *LinkType;	 //这里的*是类型修饰符，表明LinkType是指向节点的指针类型 

// 有序链表类型
typedef struct {
    LinkType head, tail;	//头指针和尾指针，分别指向链表的头结点和尾结点 
    int size;				//记录有序表中元素的总个数（链表当前的长度） 
    int curpos;				//当前被操作的元素在有序表中的位置 
    LinkType current;		//当前指针，指向链表中第curpos个元素 
} OrderedList;

// 状态定义，用于表示函数执行成功或失败 
#define TRUE 1
#define FALSE 0
typedef int status;
// 预设最大值
#define MAXINT 32767

// 初始化有序链表（创建一个空的有序链表）
status InitList(OrderedList &L) {
    L.head = new NodeType;
    if (!L.head) return FALSE;
    L.head->data = 0;	//头节点不存储有效数据（有序表的实际元素从后续节点开始）
    L.head->next = NULL;	//初始化时链表为空（除了头节点外没有其他元素），所以头节点之后没有节点，next 指向 NULL
    L.current = L.tail = L.head;	//	此时只有一个头结点也是尾结点，所以当前指针（current）、头指针、尾指针都指向头结点 
    L.curpos = L.size = 0;	//curpos=0并非表示记录的头节点，因为curpos只记录有效元素并且从1开始，curpos=0表示“初始位置” 
    return TRUE;
}

// 销毁链表
void DestroyList(OrderedList &L) {
    while (L.head->next) {		//循环条件：当下一个结点的地址不为空时（即后面还有有效结点） 
        LinkType p = L.head->next;	//用指针p暂存下一个结点的地址 
        L.head->next = p->next;		/*p->next表示的是p所指结点的下一个结点的地址，p本身又是下一个结点的地址,
        所以相当于下下个结点的地址，跳过p所指的结点*/ 
        delete p;	//释放 p 指向的节点（即第一个有效节点）的内存。
    }
    delete L.head;	//释放头节点的内存（头节点是初始化时单独创建的，需要单独释放）
    // 好习惯：将指针置空，防止野指针
    L.head = L.tail = L.current = NULL;
    L.size = L.curpos = 0;
}

// 获取有序链表中第i个元素
ElemType GetElem(OrderedList L, int i) {
    if ((i < 1) || (i > L.size)) return MAXINT;
    // 注意：这里的 L 是按值传递，修改它的 current 和 curpos 不会影响外部的链表
    // 如果想优化，应传递引用，但要小心维护状态
    LinkType p = L.head->next;
    for(int j = 1; j < i; j++) {
        p = p->next;
    }
    return p->data;
}

// 定位元素位置（从1开始计数）
int LocatePos(OrderedList &L, ElemType e) {
    if (!L.head) return 0;
    LinkType p = L.head->next;
    int pos = 1;	//记录元素位置 
    while (p) {
        if (p->data == e) {
            return pos;	//如果找到了，返回元素位置 
        }
        p = p->next;	//遍历有效结点直到e第一次出现为止 
        pos++;			//往下个结点找的同时位置也要+1 
    }
    return 0; // 未找到
}

// 插入元素
void InsertElem(OrderedList &L, ElemType e) {
    // 查找插入位置，p 指向待插入位置的前一个节点
    LinkType p = L.head;
    while (p->next && p->next->data < e) {
        p = p->next;
    }
    // 创建新节点
    LinkType s = new NodeType;
    s->data = e;
    // 插入
    s->next = p->next;	/*到达p结点要在其后插入，本来是p结点的指针域要指向下一个结点，
						但是要在p结点和下一个结点之间插入 一个s新结点，那么s结点的指针域就得指向p结点指针域指向的地方
						即把p结点的指针域赋值给s结点的指针域*/ 
    p->next = s;	//再把p结点的下一个结点设置为s，代表插入操作 
    // 如果插在尾部，更新 tail（尾结点）
    if (p == L.tail) {
        L.tail = s;
    }
    L.size++;
}

// 删除元素 （按位置） 
void DeleteElem(OrderedList &L, int i) {
    if ((i < 1) || (i > L.size)) return;

    // 找到待删除节点的前一个节点 pre
    LinkType pre = L.head;
    for (int j = 1; j < i; j++) {
        pre = pre->next;
    }
    
    LinkType q = pre->next; // q 是要删除的节点

    // 修改指针
    pre->next = q->next;		//同样道理，q结点要被删，原先q结点的指针域就要赋值给q的前一个结点pre的指针域 

    // 如果删除的是尾节点，更新 tail
    if (L.tail == q) {
        L.tail = pre;
    }

    delete q;
    L.size--;
}

// 输出结点
void output(LinkType p) {
    cout << p->data << ",";
}

// 遍历链表
void ListTraverse(OrderedList &L, void (*visit)(LinkType)) {
	/*函数指针，指向一个 “接收参数为 LinkType、返回值为 void” 的函数。
作用：一次遍历，多种操作
规定了 “遍历每个节点时要执行的操作” 的格式，传不同函数执行不同操作，比如打印、求和、修改等
但是传入的函数都必须接收一个结点指针*/ 
    if (L.head) {
        LinkType p = L.head->next;
        while (p) {
            visit(p);	//只要当前结点存在，调用visit函数指针所指向的函数，接收节点指针p作为参数传入 
            p = p->next;
        }
    }
}

/*集合部分*/ 
/*集合（OrderedSet）和有序链表（OrderedList）在存储结构上有很多共性（比如都需要有序存储、支持遍历、插入等操作）。
通过这种 “类型别名 + 函数封装” 的方式：
无需重新设计数据结构：直接复用 OrderedList 的存储结构（head、tail、size 等成员），避免重复开发；
复用已有操作函数：集合的创建、销毁逻辑和链表完全一致，直接调用链表的 InitList 和 DestroyList 即可；
语义更清晰：用 OrderedSet 表示集合，比 OrderedList 更贴合 “集合” 的业务场景，让代码可读性更高。*/

// 集合类型定义
typedef OrderedList OrderedSet;		/* 将有序链表（OrderedList）复用为有序集合（OrderedSet）
通过简单的类型别名和函数封装，实现了集合的基本操作（创建空集、销毁集合）*/

// 构造空集
status CrtNullSet(OrderedSet &T) {		//创建一个空的有序集合T 
    return InitList(T);
}

// 销毁集合
void DestroySet(OrderedSet &T) {
    DestroyList(T);
}

// 添加元素 (集合中不能有重复元素)（向集合 T 中添加元素 e）
void AddElem(OrderedSet &T, ElemType e) {
    //调用 LocatePos 函数检查元素 e 是否存在于集合中。LocatePos 返回 0 表示元素不存在
    if (e > 0 && LocatePos(T, e) == 0) { // 仅当元素不存在时才插入
        InsertElem(T, e);	//调用有序链表的插入函数 InsertElem 将 e 插入集合
    }
}

// 删除元素
void DelElem(OrderedSet &T, ElemType e) {
    int k = LocatePos(T, e);
    if (k != 0) {
        DeleteElem(T, k);
    }
}

// 获取集合长度
int SetLength(OrderedSet T) {
    return T.size;	//size是结构体中专门用于记录元素总个数的成员变量,可直接返回 
}

// 并集运算
void Union(OrderedSet &T, OrderedSet S1, OrderedSet S2) {
    CrtNullSet(T); // 确保 T 是一个空集
    LinkType p1 = S1.head->next;
    LinkType p2 = S2.head->next;

    while (p1 && p2) {
        if (p1->data < p2->data) {
            InsertElem(T, p1->data);
            p1 = p1->next;
        } else if (p1->data > p2->data) {
            InsertElem(T, p2->data);
            p2 = p2->next;
        } else { // 相等，只插入一次
            InsertElem(T, p1->data);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    // 处理剩余元素
    while (p1) {
        InsertElem(T, p1->data);
        p1 = p1->next;
    }
    while (p2) {
        InsertElem(T, p2->data);
        p2 = p2->next;
    }
}

// 交集运算
void Intersection(OrderedSet &T, OrderedSet S1, OrderedSet S2) {
    CrtNullSet(T);
    LinkType p1 = S1.head->next;
    LinkType p2 = S2.head->next;

    while (p1 && p2) {
        if (p1->data < p2->data) {
            p1 = p1->next;
        } else if (p1->data > p2->data) {
            p2 = p2->next;
        } else { // 相等，是交集元素
            InsertElem(T, p1->data);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
}

// 差集运算 (S1 - S2)
void Difference(OrderedSet &T, OrderedSet S1, OrderedSet S2) {
    CrtNullSet(T);
    LinkType p1 = S1.head->next;
    LinkType p2 = S2.head->next;

    while (p1 && p2) {
        if (p1->data < p2->data) {
            // s1最小的元素比s2最小的元素小，那么p1元素就一定不在 S2 中
            InsertElem(T, p1->data);
            p1 = p1->next;
        } else if (p1->data > p2->data) {
            p2 = p2->next;
        } else { // 元素相等，说明 p1 元素在 S2 中，不加入差集
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    // S1 中剩余的元素都不在 S2 中
    while (p1) {
        InsertElem(T, p1->data);
        p1 = p1->next;
    }
}

// 创建集合
void CreateSet(OrderedSet &ST) {
    CrtNullSet(ST);
    ElemType elem;
    cin >> elem;	//第一次读取用户输入的元素（启动输入流程）
    while (elem != -1) {	//将-1设定为输入结束标记 
        AddElem(ST, elem);
        cin >> elem;
    }
}

// 打印集合
void PrintSet(OrderedSet T) {		//这里按值传递，因为只需读取元素无需修改 
    cout << "{";
    ListTraverse(T, output);		//调用遍历函数 ListTraverse 遍历集合 T，并对每个元素执行 output 函数
    // 如果集合不为空，删除最后一个多余的逗号（假设output 函数对每个元素的输出格式是：元素, ）
    if (T.size > 0) {
        cout << "\b";	// \b是 “退格符”，会删除前一个字符
    }
    cout << "}";
}

int main() {
    OrderedSet S1, S2, T1, T2, T3;
    cout << "Input S1 (end with -1): ";
    CreateSet(S1);
    cout << "Input S2 (end with -1): ";
    CreateSet(S2);
    cout << "S1: ";
    PrintSet(S1);
    cout << "\nS2: ";
    PrintSet(S2);
    Union(T1, S1, S2);	//求并集 
    cout << "\nUnion: ";
    PrintSet(T1);
    Intersection(T2, S1, S2);	//求交集
    cout << "\nIntersection: ";
    PrintSet(T2);
    Difference(T3, S1, S2);		//求差集（A-B） 
    cout << "\nDifference (S1 - S2): ";
    PrintSet(T3);
    
    //销毁链表和集合，释放内存 
    DestroySet(T1);
    DestroySet(T2);
    DestroySet(T3);
    DestroySet(S1);
    DestroySet(S2);
    return 0;
} 
