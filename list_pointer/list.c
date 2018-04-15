#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>

#define N 3

typedef struct node
{
   char name[20];
   struct node*link;
}stud;

stud * creat(int n) /*建立单链表的函数*/
{

   stud*p,*h,*s;

   int i;

   if((h=(stud*)malloc(sizeof(stud)))==NULL)

   {

     printf("不能分配内存空间!");

      exit(0);

   }

  h->name[0]='\0';

  h->link=NULL;

   p=h;

  for(i=0;i<N;i++)

   {

     if((s=(stud *) malloc(sizeof(stud)))==NULL)

     {

       printf("不能分配内存空间!");

        exit(0);

     }

    p->link=s;

    printf("请输入第%d个人的姓名:",i+1);

    scanf("%s",s->name);

    s->link=NULL;

     p=s;

   }

   return(h);

}

stud * search(stud *h,char *x) /*查找函数*/

{

   stud *p;

   char *y;

   p=h->link;

  while(p!=NULL)

   {

    y=p->name;

    if(strcmp(y,x)==0)

      return(p);

     else p=p->link;

   }

   if(p==NULL)

     printf("没有查找到该数据!");

}

stud * search2(stud *h,char*x)

/*另一个查找函数，返回的是上一个查找函数的直接前驱结点的指针，

h为表头指针，x为指向要查找的姓名的指针

其实此函数的算法与上面的查找算法是一样的，只是多了一个指针s，并且s总是指向指针p所指向的结点的直接前驱，

结果返回s即是要查找的结点的前一个结点*/

{

   stud *p,*s;

   char *y;

   p=h->link;

   s=h;

  while(p!=NULL)

   {

    y=p->name;

    if(strcmp(y,x)==0)

      return(s);

     else

     {

      p=p->link;

       s=s->link;

     }

   }

   if(p==NULL)

   printf("没有查找到该数据!");

}

void insert(stud *p) /*插入函数，在指针p后插入*/

{

   char stuname[20];

   stud *s; /*指针s是保存新结点地址的*/

   if((s= (stud*) malloc(sizeof(stud)))==NULL)

   {

    printf("不能分配内存空间!");

     exit(0);

   }

   printf("请输入你要插入的人的姓名:");

  scanf("%s",stuname);

  strcpy(s->name,stuname); /*把指针stuname所指向的数组元素拷贝给新结点的数据域*/

  s->link=p->link; /*把新结点的链域指向原来p结点的后继结点*/

   p->link=s;/*p结点的链域指向新结点*/

}

 

void del(stud *x,stud *y) /*删除函数，其中y为要删除的结点的指针，x为要删除的结点的前一个结点的指针*/

{

  stud *s;

  s=y;

 x->link=y->link;

  free(s);

}

 
void print(stud *h)

{

   stud *p;

   p=h->link;

   printf("数据信息为：\n");

  while(p!=NULL)

   {

    printf("%s \n",&*(p->name));

    p=p->link;

   }

}

 

 

void quit()

{

  exit(0);

}

void menu(void)

{

   system("cls");

   printf("\t\t\t单链表C语言实现实例\n");

   printf("\t\t|----------------|\n");

   printf("\t\t| |\n");

   printf("\t\t| [1] 建 立 新 表 |\n");

   printf("\t\t| [2] 查 找 数 据 |\n");

   printf("\t\t| [3] 插 入 数 据 |\n");

   printf("\t\t| [4] 删 除 数 据 |\n");

   printf("\t\t| [5] 打 印 数 据 |\n");

   printf("\t\t| [6] 退 出 |\n");

   printf("\t\t| |\n");

   printf("\t\t| 如未建立新表，请先建立！ |\n");

   printf("\t\t| |\n");

   printf("\t\t|----------------|\n");

   printf("\t\t 请输入你的选项(1-6):");

}


list_main()

{

    int choose;

    stud*head,*searchpoint,*forepoint;

    char fullname[20];

 

    while(1)

    {

      menu();

     scanf("%d",&choose);

     switch(choose)

      {

        case 1:

          head=creat(N);

          break;

        case 2:

                      printf("输入你所要查找的人的姓名:");

          scanf("%s",fullname);

          searchpoint=search(head,fullname);

          printf("你所查找的人的姓名为:%s",*&searchpoint->name);

          printf("\n按回车键回到主菜单。");

          getchar();getchar();

          break;

        case 3:printf("输入你要在哪个人后面插入:");

          scanf("%s",fullname);

          searchpoint=search(head,fullname);

          printf("你所查找的人的姓名为:%s",*&searchpoint->name);

          insert(searchpoint);

          print(head);

          printf("\n按回车键回到主菜单。");

          getchar();getchar();

          break;

        case 4:

                      print(head);

          printf("\n输入你所要删除的人的姓名:");

          scanf("%s",fullname);

          searchpoint=search(head,fullname);

          forepoint=search2(head,fullname);

          del(forepoint,searchpoint);

          break;

        case 5:

                      print(head);

          printf("\n按回车键回到主菜单。");

          getchar();getchar();

          break;

        case6:quit();

          break;

        default:

                      printf("你输入了非法字符!按回车键回到主菜单。");

          system("cls");

           menu();

           getchar();

      }

   }

}