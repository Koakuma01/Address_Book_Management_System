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
void show(aNode *p);
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
        case 3:Del();       //删除(按姓名删除、按手机号删除、清空)@@
            break;
//        case 4:Modify();    //修改@
//            break;
//        case 5:Sort();      //排序
//            break;
//        case 6:Query();     //查询(按姓名查询、按手机号查询)@
//            break;
        case 7:Display();   //显示@@
            break;
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
    printf("\n请选择功能模块：");
    while(1)
    {
        scanf("%d",&choice);
        if(choice>=1&&choice<=10)
            break;
        else
            printf("输入数字不正确，请重新输入：");
    }
    return choice;
}
void Create()
{
    head = NULL;
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
        {
            rear->next = New;
            rear = rear->next;
        }
        printf("\n");
    }
    printf("通讯录创建成功\n");
}
void Save()
{
    FILE *fp;
    LiAddress p = head;
    if((fp=fopen("C:\\Users\\Administrator\\Desktop\\Address book.txt","w"))==NULL)
    {
        printf("通讯录保存失败！\n");
        return;
    }
    while(p != NULL)
    {
        fprintf(fp,"%s %s %s %s\n",p->name,p->sex,p->phone,p->address);
        p = p->next;
    }
    printf("\n通讯录保存成功！\n");
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
    printf("\n通讯录读取成功！\n");
    fclose(fp);
}
void Del() //删除
{
    if(head == NULL){
        printf("\n通讯录为空！\n");
        return;
    }
    printf("————请选择删除方式————\n");
    printf("1.按名字删除\t2.按号码删除—\n");
    printf("3.清空通讯录\t4.取消      —\n");
    printf("———————————————\n");
    printf("请选择：");
    int choice;
    char str[20];
    scanf("%d",&choice);
    if(choice == 1){
        printf("请输入联系人姓名：");
        scanf("%s",str);
    }else if(choice == 2){
        printf("请输入联系人号码：");
        scanf("%s",str);
    }else if(choice == 3){
        aNode *p = head,*p1;
        while(p != NULL)
        {
            p1 = p;
            p = p->next;
            free(p1);
        }
        head = NULL;
        printf("\n通讯录清除成功！\n");
        return;
    }else{return;}
/******************删除操作******************/
    aNode *p = head,*p1;
    while((strcmp(p->name,str)!=0)&&(strcmp(p->phone,str)!=0))
    {
        p1 = p;
        p = p->next;
        if(p == NULL)
        {
            break;
        }
    }
    if(p == head)//删除的是头结点
    {
        show(p);
        printf("确认要删除吗？(Y/N)：");
        char ch = getche();
        printf("\n");
        if(ch=='Y'||ch=='y')
        {
            head = head->next;
            free(p);
            printf("删除成功！\n");
        }
    }
    else if(p == NULL)//未找到联系人
    {
        printf("未找到该联系人！\n");
    }
    else//找到联系人
    {
        show(p);
        printf("确认要删除吗？(Y/N)：");
        char ch = getche();
        printf("\n");
        if(ch=='Y'||ch=='y')
        {
            p1->next = p->next;
            free(p);
            printf("删除成功！\n");
        }
    }
}
void Display()//展示
{
    if(head == NULL)
    {
        printf("通讯录为空！\n");
        return;
    }

    LiAddress p = head;
    printf("———————联系人信息如下———————\n");
    printf("—姓名\t性别\t电话号码\t地址\n");
    while(p!=NULL)
    {
        printf("—%s\t%s\t%s\t%s\n",p->name,p->sex,p->phone,p->address);
        p = p->next;
    }
    printf("—————————————————————\n");
}

void show(aNode *p)
{
    printf("——————该联系人信息如下———————\n");
    printf("—姓名\t性别\t电话号码\t地址\n");
    printf("—%s\t%s\t%s\t%s\n",p->name,p->sex,p->phone,p->address);
    printf("—————————————————————\n");
}
