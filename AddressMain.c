#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define Password "root" //管理员密码

typedef struct Node
{
    char name[20];      //姓名
    char sex[20];       //性别
    char phone[20];     //手机号
    char address[20];   //住址
    struct Node* next;
}aNode,*LiAddress;

LiAddress head = NULL;  //头指针

/*******函数声明*******/
void menu_admin();
void menu_users();
int  choice(int max);
void Create();
void Add();
void Del();
void Modify();
void Sort();
void Query();
void Display();
void Save();
void Load();

void show(aNode *p);            //显示p所指结点的信息
void swap(aNode *p,aNode *p1);  //交换p,p1的信息,用于排序
/*******函数声明*******/
int main()
{
    printf("欢迎使用通讯录管理系统！\n");
    printf("请选择登录身份(1.用户 2.管理员)");
    if(choice(2) == 1)
        menu_users();
    else
    {
        char p[20];
        printf("请输入管理员密码：");
        scanf("%s",p);
        if(strcmp(p,Password) != 0)
        {
            while(1)
            {
                printf("密码错误，请重新输入(输入0退出)：");
                scanf("%s",p);
                if(strcmp(p,"0") == 0)
                    exit(0);
                if(strcmp(p,Password) == 0)
                    break;
            }
        }
        menu_admin();
    }
}
/***********函数定义************/
void menu_admin()
{
    printf("——欢迎使用通讯录管理系统——\n");
    printf("1.创建通讯录\t2.添加联系人—\n");
    printf("3.删除联系人\t4.修改联系人—\n");
    printf("5.通讯录排序\t6.查询联系人—\n");
    printf("7.显示联系人\t8.保存通讯录—\n");
    printf("9.读取通讯录\t10.退出系统 —\n");
    printf("———————————————\n");
    while(1)
    {
        switch (choice(10))   //选择
        {
        case 1:Create();    //创建
            break;
        case 2:Add();       //添加
            break;
        case 3:Del();       //删除
            break;
        case 4:Modify();    //修改
            break;
        case 5:Sort();      //排序
            break;
        case 6:Query();     //查询
            break;
        case 7:Display();   //显示
            break;
        case 8:Save();      //保存
            break;
        case 9:Load();      //读取
            break;
        case 10:            //退出
            printf("\n感谢您的使用！\n");
            exit(0);
        }
    }
}
void menu_users()
{
    printf("——欢迎使用通讯录管理系统——\n");
    printf("1.显示联系人\t2.查询联系人—\n");
    printf("3.通讯录排序\t4.退出系统  —\n");
    printf("———————————————\n");
    Load();
    while(1)
    {
        switch (choice(4))  //选择
        {
        case 1:Display();   //显示
            break;
        case 2:Query();     //查询
            break;
        case 3:Sort();      //排序
            break;
        case 4:             //退出
            printf("\n感谢您的使用！\n");
            exit(0);
        }
    }
}
int choice(int max)
{
    int choice;
    if(max == 10)
        printf("\n请选择功能模块：");
    else
        printf("\n请选择：");
    while(1)
    {
        scanf("%d",&choice);
        if(choice>=1&&choice<=max)
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
        printf("\n通讯录保存失败！\n");
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
        printf("\n通讯录读取失败！\n");
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
    aNode *p = head,*p1;
    printf("————请选择删除方式————\n");
    printf("1.按名字删除\t2.按号码删除—\n");
    printf("3.清空通讯录\t4.取消      —\n");
    printf("———————————————\n");
    int n = choice(4);
    char str[20];
    if(n == 1){
        printf("请输入联系人姓名：");
        scanf("%s",str);
        while(strcmp(p->name,str)!=0)
        {
            p1 = p;
            p = p->next;
            if(p == NULL)
            {
                break;
            }
        }
    }else if(n == 2){
        printf("请输入联系人号码：");
        scanf("%s",str);
        while(strcmp(p->phone,str)!=0)
        {
            p1 = p;
            p = p->next;
            if(p == NULL)
            {
                break;
            }
        }
    }else if(n == 3){
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
        printf("\n通讯录为空！\n");
        return;
    }

    LiAddress p = head;
    printf("————————通讯录信息如下—————————\n");
    char *m[] = {"姓名","性别","电话号码","地址"};
    printf("—%-7s%-7s%-15s%-15s—\n",*m,*(m+1),*(m+2),*(m+3));
    while(p!=NULL)
    {
        printf("—%-7s%-7s%-15s%-15s—\n",p->name,p->sex,p->phone,p->address);
        p = p->next;
    }
    printf("————————————————————————\n");
}

void Query()
{
    if(head == NULL)   //判断通讯录是否为空
    {
         printf("\n通讯录为空！\n");
        return;
    }
    printf("请输入联系人姓名或号码：");
    char str[20];
    scanf("%s",str);
    LiAddress  p = head;
    while((strcmp(p->name,str)!=0)&&(strcmp(p->phone,str)!=0))	//对链表实行遍历
    {
        p = p->next;
        if(p == NULL)			//遍历结束且未找到要查找的联系人
        {
            printf("未找到该联系人！\n");
            return;
        }
    }
    show(p);
}

void Modify()
{
    if(head == NULL)		//判断通讯录是否为空
    {
         printf("通讯录为空！\n");
        return;
    }
    printf("请输入联系人姓名或号码：");
    char str[20];
    scanf("%s",str);
    LiAddress p=head;
    while(strcmp(str,p->name)!=0&&strcmp(str,p->phone)!=0)		//对链表实行遍历
    {
        p=p->next;
        if(p==NULL) break;
    }
    if(p==NULL)
    {
        printf("该联系人不存在！\n");
        return;
    }
    else show(p);
    printf("————选择要修改的信息————\n");
    printf("1.姓名\t2.性别\t3.号码\t4.住址—\n");
    printf("————————————————\n");
    int i = choice(4);
    switch (i)				//修改联系人信息
    {
    case 1:
        printf("名字修改为:");
        scanf("%s",p->name);
        break;
    case 2:
        printf("性别修改为:");
        scanf("%s",p->sex);
        break;
    case 3:
        printf("电话号码修改为:");
        scanf("%s",p->phone);
        break;
    case 4:
        printf("地址修改为:");
        scanf("%s",p->address);
        break;
    default:
        break;
    }
    printf("修改成功！\n");
}

void Add()
{
    aNode *rear,*p;
    if(head==NULL)
    {
        printf("\n请先创建通讯录!\n");
        return;
    }
    printf("\n说明:当输入姓名为0时输入结束\n\n");
    int count = 0;    //记录添加联系人个数
    while(1)
    {
        int flag = 1;
        aNode *Add=(aNode *)malloc(sizeof(aNode));
        printf("请输入联系人姓名：");
        scanf("%s",Add->name);
        if(strcmp(Add->name,"0")==0)    //添加结束
        {
            printf("\n");
            free(Add);
            break;
        }
        rear = head;
        while(rear != NULL)			//检验通讯录是否已有此人
        {
            if (strcmp(Add->name,rear->name) == 0)
            {
                printf("通讯录已存在该人，请重新输入！\n");
                flag = 0;
                break;
            }
            p = rear;
            rear = rear->next;
        }
        if(!flag)continue;
        printf("请输入联系人性别：");
        scanf("%s",Add->sex);
        printf("请输入联系人号码：");
        scanf("%s",Add->phone);
        printf("请输入联系人地址：");
        scanf("%s",Add->address);
        Add->next = NULL;
        p->next = Add;
        count ++;
        printf("\n");
    }
    printf("成功添加%d位联系人！\n",count);
}

void Sort()
{
    if(head==NULL)
    {
        printf("\n请先创建通讯录!\n");
        return;
    }
    int count = 0;
    aNode *p = head,*p1;
    while(p != NULL)
    {
        count ++;
        p = p->next;
    }
    printf("————请选择删除方式————\n");
    printf("1.按名字排序\t2.按号码排序—\n");
    printf("———————————————\n");
    int n = choice(2);
    if(n     == 1)
    {
        for (int i = 0; i < count; i++)
        {
            p = head;
            p1 = p->next;
            while(p1 != NULL)
            {
                if(strcmp(p->name,p1->name)>0)
                {
                    swap(p,p1);
                }
                p = p->next;
                p1 = p1->next;
            }
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            p = head;
            p1 = p->next;
            while(p1 != NULL)
            {
                if(strcmp(p->phone,p1->phone)>0)
                {
                    swap(p,p1);
                }
                p = p->next;
                p1 = p1->next;
            }
        }
    }
    printf("排序完成,排序后的结果为：\n");
    Display();
}

void swap(aNode *p,aNode *p1)
{
    aNode *temp=(aNode *)malloc(sizeof(aNode));
    strcpy(temp->name,p->name);
    strcpy(temp->sex,p->sex);
    strcpy(temp->phone,p->phone);
    strcpy(temp->address,p->address);
    strcpy(p->name,p1->name);
    strcpy(p->sex,p1->sex);
    strcpy(p->phone,p1->phone);
    strcpy(p->address,p1->address);
    strcpy(p1->name,temp->name);
    strcpy(p1->sex,temp->sex);
    strcpy(p1->phone,temp->phone);
    strcpy(p1->address,temp->address);
}

void show(aNode *p)
{
    printf("———————该联系人信息如下—————————\n");
    char *m[] = {"姓名","性别","电话号码","地址"};
    printf("—%-7s%-7s%-15s%-15s—\n",*m,*(m+1),*(m+2),*(m+3));
    printf("—%-7s%-7s%-15s%-15s—\n",p->name,p->sex,p->phone,p->address);
    printf("————————————————————————\n");
}
