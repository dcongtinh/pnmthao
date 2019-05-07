#include<stdio.h>
#include"list.cpp"
#define MAX_VERTICES 100
typedef struct{
	int n;
	List adj[MAX_VERTICES];
}Graph;
/*Khoi tao do thi G co n dinh*/
void init_graph(Graph *G, int n){
	int i,j;
	G->n=n;
	for(i=1; i<=n; i++)
		make_null_list(&G->adj[i]);
}
/*Them cung e=(x,y) vao do thi G*/
void add_edge(Graph *G, int x, int y){
	push_back(&G->adj[x],y); //y ke voi x
	push_back(&G->adj[y],x); //y ke voi x
}
/*Kiem tra y co ke voi x hay khong*/
int adjacent(Graph *G, int x, int y){
	int j;
	for(j=1; j<=G->adj[x].size; j++)
		if(element_at(&G->adj[x],j) == y)
			return 1;
	return 0;
}
/*Tinh bac cua dinh x*/
int degree(Graph *G, int x){
	return G->adj[x].size;
}
int main(){
	Graph G;
	int n,m,e,v,u;
	FILE* file=fopen("dothi.txt","r");
	fscanf(file,"%d%d",&n,&m);
	init_graph(&G,n);
	for(e=1; e<=m; e++){
		fscanf(file,"%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	for(v=1;v<=n;v++)
		printf("deg(%d)=%d\n",v,degree(&G,v));	
}

