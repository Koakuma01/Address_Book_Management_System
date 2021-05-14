#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    char name[20];//姓名
    char sex[20];//性别
    char phone[20];//手机号
    char address[20];//住址
    struct Node* next;
}aNode,*LiAddress;

LiAddress head = NULL;//头指针

/*******函数声明*******/
void menu();
int choice();
void Create();
void Add();
void Del();
void Modify();
void Sort();
void Query();
void Display();
void Save();
void Load();
/*******函数声明*******/
int main()
{
    menu();                 //菜单
    while(1)
    {
        switch (choice())   //选择
        {
        case 1:Create();    //创建
            break;
//        case 2:Add();       //添加@@@
//            break;
//        case 3:Del();       //删除(按姓名删除、按手机号删除、清空)@@
//            break;
//        case 4:Modify();    //修改@
//            break;
//        case 5:Sort();      //排序
//            break;
//        case 6:Query();     //查询(按姓名查询、按手机号查询)@
//            break;
//        case 7:Display();   //显示@@
//            break;
        case 8:Save();      //保存
            break;
        case 9:Load();      //打开
            break;
        case 10:exit(0);    //退出
        }
    }
}
/***********函数定义************/
void menu()
{
    printf("——欢迎使用通讯录管理系统——\n");
    printf("1.创建通讯录\t2.添加联系人—\n");
    printf("3.删除联系人\t4.修改联系人—\n");
    printf("5.通讯录排序\t6.查询联系人—\n");
    printf("7.显示联系人\t8.保存通讯录—\n");
    printf("9.读取通讯录\t10.退出系统 —\n");
    printf("———————————————\n");
}
int choice()
{
    int choice;
    printf("请选择功能模块：");
    while(1)
    {
        scanf("%d",&choice);
        if(choice>=1&&choice<=10)
            break;
        else
            printf("输入数字不正确，请重新输入：");
    }
    return  choice;
}

void Create()
{
    aNode *New,*rear;
    printf("\n说明:当输入姓名为0时输入结束\n\n");
    while(1)
    {
        New=(aNode *)malloc(sizeof(aNode));

        /*********输入学生信息*********/
        printf("输入姓名:");
        scanf("%s",New->name);

        //退出循环
        if(strcmp(New->name,"0")==0)
        {
            printf("\n");
            free(New);
            break;
        }

        printf("输入性别:");
        scanf("%s",New->sex);
        printf("输入手机号:");
        scanf("%s",New->phone);
        printf("输入住址:");
        scanf("%s",New->address);
        New->next=NULL;
        /*********输入学生信息*********/

        if(head == NULL)
            head = rear = New;
        else
            rear->next = New;
        printf("\n");
    }
    printf("通讯录创建成功\n");
}

void Save()
{
    FILE *fp;
    LiAddress p = head;
    if((fp=fopen("C:\\Users\\Administrator\\Desktop\\Address book.txt","a"))==NULL)
    {
        printf("通讯录保存失败！\n");
        return;
    }
    while(p!=NULL)
    {
        fprintf(fp,"%s %s %s %s\n",p->name,p->sex,p->phone,p->address);
        p=p->next;
    }
    printf("\n通讯录保存成功！\n\n");
    fclose(fp);
}

void Load()
{
    FILE *fp;
    aNode *New,*p = head;
    if((fp=fopen("C:\\Users\\Administrator\\Desktop\\Address book.txt","r"))==NULL)
    {
        printf("通讯录读取失败！\n");
        return;
    }
    while(1)
    {
        New=(aNode *)malloc(sizeof(aNode));
        if(fscanf(fp,"%s %s %s %s", New->name, New->sex, New->phone, New->address)!=EOF)
        {
            New->next = NULL;
            if(p == NULL)
                p = head = New;
            else
            {
                while(p->next != NULL)
                {
                    p = p->next;
                }
                p->next = New;
            }
        }
        else
        {
            free(New);
            break;
        }
    }
    printf("\n通讯录读取成功！\n\n");
    fclose(fp);
}


