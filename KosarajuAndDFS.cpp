#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include <queue>
using namespace std;

typedef struct edge
{
    char name;
    int index;
    struct edge* nxt;
}edge;

typedef struct vertex
{
    char name;
    int status;
    int bTime;
    int eTime;
    edge* next;

}vertex;
vertex graphO[10];
vertex graphR[10];
priority_queue<pair<int,int>> p;
void initializeGraph(char name,vertex graph[])
{
    int i=0;
    for(i=0;i<10;i++)
    {
        if(graph[i].name=='0')
        {
            graph[i].name=name;
            break;
        }
    }
}

void Edge(char s,char o,vertex graph[])
{
    edge* temp=(edge*)malloc(sizeof(edge));
    temp->name=o;
    temp->nxt=NULL;
    int i=0;
    int index;
    for(i=0;i<10;i++)
    {
        if(graph[i].name==o)
        {
            index=i;
            break;
        }
    }
    temp->index=index;
    for(i=0;i<10;i++)
    {
        if(graph[i].name==s)
        {
            edge* p=graph[i].next;
            if(p==NULL)
            {
                graph[i].next=temp;
            }
            else
            {
            while(p->nxt!=NULL)
            {
                p=p->nxt;
            }
            p->nxt=temp;
            }
            break;
        }
    }
}
void DFS_visit(int index,vertex graph[]);
void DFS(vertex graph[])
{
    int i;
    int time=1;
    for(i=0;i<8;i++)
    {
        if(graph[i].status==0)
        {
            graph[i].bTime=time;

            DFS_visit(graph[i].next->index,graphO);
        }
    }
}
void DFS_visitR(int index,vertex graph[]);
void DFSR(vertex graph[])
{
    int i;
    int time=1;
    while(p.size()!=0)
    {
        i=p.top().second;
        p.pop();
         if(graph[i].status==0)
        {
            graph[i].bTime=time;
            graph[i].status=1;
            edge* t=graph[i].next;
            while(t!=NULL)
            {
            if(graph[t->index].status!=1)
                DFS_visitR(t->index,graphR);
              t=t->nxt;
            }
        }
        printf(" \t %c---STRONGLY CONNECTED COMPONENT DETECTED!!!!! \n",graphR[i].name);
    }
}
void DFS_visitR(int index,vertex graph[])
{
    static int t=1;
    graph[index].bTime=++t;
    graph[index].status=1;
printf(" %c%d",graph[index].name,graph[index].bTime);

    edge* p=graph[index].next;
    while(p!=NULL)
    {
      if(graph[p->index].status!=1)
       {
        DFS_visitR(p->index,graph);
       }
       p=p->nxt;
    }
    t++;
    graph[index].eTime=t;
    printf(" %c%d ",graph[index].name,graph[index].eTime);

    //graph[index].status=1;
}

void DFS_visit(int index,vertex graph[])
{
    static int t=1;
    graph[index].bTime=++t;
    graph[index].status=1;
printf(" %c%d",graph[index].name,graph[index].bTime);

    edge* p=graph[index].next;
    while(p!=NULL)
    {
      if(graph[p->index].status!=1)
       {
        DFS_visit(p->index,graph);
       }
       p=p->nxt;
    }
    t++;
    graph[index].eTime=t;
    printf(" %c%d ",graph[index].name,graph[index].eTime);

    //graph[index].status=1;
}


int main()
{
     int i;

for(i=0;i<10;i++)
{
    graphO[i].name='0';
    graphO[i].status=0;
    graphO[i].bTime=0;
    graphO[i].eTime=0;
    graphO[i].next=NULL;
}
for(i=0;i<10;i++)
{
    graphR[i].name='0';
    graphR[i].status=0;
    graphR[i].bTime=0;
    graphR[i].eTime=0;
    graphR[i].next=NULL;
}
     initializeGraph('a',graphO);
    initializeGraph('b',graphO);
    initializeGraph('c',graphO);
    initializeGraph('d',graphO);
    initializeGraph('e',graphO);
    initializeGraph('f',graphO);
    initializeGraph('g',graphO);
    initializeGraph('h',graphO);
    Edge('a','b',graphO);
    Edge('b','e',graphO);
    Edge('e','a',graphO);
    Edge('b','f',graphO);
    Edge('b','c',graphO);
    Edge('c','d',graphO);
    Edge('d','c',graphO);
    Edge('d','h',graphO);
    Edge('h','h',graphO);
    Edge('g','h',graphO);
     Edge('f','g',graphO);
    Edge('g','f',graphO);
     Edge('e','f',graphO);





        initializeGraph('a',graphR);
    initializeGraph('b',graphR);
    initializeGraph('c',graphR);
    initializeGraph('d',graphR);
    initializeGraph('e',graphR);
    initializeGraph('f',graphR);
    initializeGraph('g',graphR);
    initializeGraph('h',graphR);
    Edge('b','a',graphR);
    Edge('e','b',graphR);
    Edge('a','e',graphR);
    Edge('f','b',graphR);
    Edge('c','b',graphR);
    Edge('d','c',graphR);
    Edge('c','d',graphR);
    Edge('h','d',graphR);
    Edge('h','h',graphR);
    Edge('h','g',graphR);
     Edge('g','f',graphR);
    Edge('f','g',graphR);
     Edge('f','e',graphR);
       for(i=0;i<8;i++)
    {
    printf("%c  ",graphO[i].name);
    }
     printf("\n");
   DFS(graphO);
     for(i=0;i<8;i++)
     {
         p.push(make_pair(graphO[i].eTime,i));
     }
   printf("\n");
    /*for(i=0;i<8;i++)
     {
         printf("%d %d ",p.top().first,p.top().second);
         p.pop();
     }*/
     printf("\n");
   DFSR(graphR);

    return 0;
}

