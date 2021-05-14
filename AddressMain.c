#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    char name[20];//����
    char sex[20];//�Ա�
    char phone[20];//�ֻ���
    char address[20];//סַ
    struct Node* next;
}aNode,*LiAddress;

LiAddress head = NULL;//ͷָ��

/*******��������*******/
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
/*******��������*******/
int main()
{
    menu();                 //�˵�
    while(1)
    {
        switch (choice())   //ѡ��
        {
        case 1:Create();    //����
            break;
//        case 2:Add();       //���@@@
//            break;
//        case 3:Del();       //ɾ��(������ɾ�������ֻ���ɾ�������)@@
//            break;
//        case 4:Modify();    //�޸�@
//            break;
//        case 5:Sort();      //����
//            break;
//        case 6:Query();     //��ѯ(��������ѯ�����ֻ��Ų�ѯ)@
//            break;
//        case 7:Display();   //��ʾ@@
//            break;
        case 8:Save();      //����
            break;
        case 9:Load();      //��
            break;
        case 10:exit(0);    //�˳�
        }
    }
}
/***********��������************/
void menu()
{
    printf("������ӭʹ��ͨѶ¼����ϵͳ����\n");
    printf("1.����ͨѶ¼\t2.�����ϵ�ˡ�\n");
    printf("3.ɾ����ϵ��\t4.�޸���ϵ�ˡ�\n");
    printf("5.ͨѶ¼����\t6.��ѯ��ϵ�ˡ�\n");
    printf("7.��ʾ��ϵ��\t8.����ͨѶ¼��\n");
    printf("9.��ȡͨѶ¼\t10.�˳�ϵͳ ��\n");
    printf("������������������������������\n");
}
int choice()
{
    int choice;
    printf("��ѡ����ģ�飺");
    while(1)
    {
        scanf("%d",&choice);
        if(choice>=1&&choice<=10)
            break;
        else
            printf("�������ֲ���ȷ�����������룺");
    }
    return  choice;
}

void Create()
{
    aNode *New,*rear;
    printf("\n˵��:����������Ϊ0ʱ�������\n\n");
    while(1)
    {
        New=(aNode *)malloc(sizeof(aNode));

        /*********����ѧ����Ϣ*********/
        printf("��������:");
        scanf("%s",New->name);

        //�˳�ѭ��
        if(strcmp(New->name,"0")==0)
        {
            printf("\n");
            free(New);
            break;
        }

        printf("�����Ա�:");
        scanf("%s",New->sex);
        printf("�����ֻ���:");
        scanf("%s",New->phone);
        printf("����סַ:");
        scanf("%s",New->address);
        New->next=NULL;
        /*********����ѧ����Ϣ*********/

        if(head == NULL)
            head = rear = New;
        else
            rear->next = New;
        printf("\n");
    }
    printf("ͨѶ¼�����ɹ�\n");
}

void Save()
{
    FILE *fp;
    LiAddress p = head;
    if((fp=fopen("C:\\Users\\Administrator\\Desktop\\Address book.txt","a"))==NULL)
    {
        printf("ͨѶ¼����ʧ�ܣ�\n");
        return;
    }
    while(p!=NULL)
    {
        fprintf(fp,"%s %s %s %s\n",p->name,p->sex,p->phone,p->address);
        p=p->next;
    }
    printf("\nͨѶ¼����ɹ���\n\n");
    fclose(fp);
}

void Load()
{
    FILE *fp;
    aNode *New,*p = head;
    if((fp=fopen("C:\\Users\\Administrator\\Desktop\\Address book.txt","r"))==NULL)
    {
        printf("ͨѶ¼��ȡʧ�ܣ�\n");
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
    printf("\nͨѶ¼��ȡ�ɹ���\n\n");
    fclose(fp);
}


