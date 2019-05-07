#include<stdio.h>
#define MAX 100
typedef int ElementType;
typedef struct{
	ElementType data[MAX];
	int size;
}List;

void make_null(List *L){
	L->size=0;
}

void push_back(List *L,ElementType x){
	L->data[L->size]=x;
	L->size++;
}

ElementType element_at(List *L,int i){
	return L->data[i-1];
}
//-----------------------------------------------
typedef struct{
	int n;
	int A[MAX][MAX];
}Graph;

void intit_graph(Graph *G,int n){
	int i,k;
	G->n=n;
	for(i=1;i<=n;i++)
		for(k=1;k<=n;k++)
			G->A[i][k]=0;
}

void add_edge(Graph *G,int x,int y){
	G->A[x][y]=1;
	G->A[y][x]=1;
}

int adjcent(Graph *G,int x,int y){
	return G->A[x][y]==1;
}

List neighbors(Graph *G,int x){
	int y;
	List L;
	make_null(&L);
	for (y=1;y<=G->n;y++){
		if(adjcent(G,x,y)) push_back(&L,y);
	}
	return L;
}
//------------------------------------------
int color[MAX];
int fail;
void tomau(Graph *G, int x, int c){
	if(color[x]==-1){
		color[x]=c;
		List List = neighbors(G,x);
		int j;
		for(j=1;j<=List.size;j++){
			int y=element_at(&List,j);
			tomau(G,y,!c);
		}
	}
	else if (color[x]!=c) fail=1;
}
int KTDT(Graph *G){
	int j;
	for(j=1;j<=G->n;j++) color[j]=-1;
	fail=0;
	tomau(G,1,0); 
	return !fail;
}

int main(){
	Graph G;
	int n,m,e,u,v,j;
	FILE* f=fopen("dothi.txt","r");
	fscanf(f,"%d%d",&n,&m);
	intit_graph(&G,n);
	for(e=1;e<=m;e++){
		fscanf(f,"%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	if (KTDT(&G)){
		for(j=1;j<=n;j++)
			if(color[j]==0)
				printf("%d ",j);
		printf("\n");
		for(j=1;j<=n;j++)
			if(color[j]==1)
				printf("%d ",j);	
	}
	else printf("IMPOSSIBLE");	
}
