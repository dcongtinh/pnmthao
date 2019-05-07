#include<stdio.h>
#define MAX 100
typedef struct {
	int data[MAX];
	int front,rear;
}Queue;
void make_null_queue(Queue *Q){
	Q->front=0;
	Q->rear=-1;
}
void push(Queue *Q, int x){
	Q->rear++;
	Q->data[Q->rear]=x;  
}
int top (Queue *Q){
	return Q->data[Q->front];
}
void pop(Queue *Q){
	Q->front++;
}
int empty(Queue *Q){
	return Q->front > Q->rear;
}
//-----------------------------------------
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
//------------------------------------
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
int adjcent(Graph G,int x,int y){
	int e;
	for(e=1;e<=G.n;e++)
		if(G.A[x][y]==1	&& G.A[y][x]==1) return 1;
	return 0;
}

List neighbors(Graph *G,int x){
	int y;
	List L;
	make_null(&L);
	for (y=1;y<=G->n;y++)
		if(adjcent(*G,x,y)) 
			push_back(&L,y);
	return L;
}
//----------------------------------------------
int mark[MAX];
int parent[MAX];
void breath_first_sreach(Graph *G, int k) {
	Queue L;
	int j;
	make_null_queue(&L);
	push(&L,k);
	mark[k]=1;
	while(!empty(&L)) {
		int x = top(&L);
		pop(&L);
		List List = neighbors(G,x);
		for(j=1;j<=List.size;j++) {
			int y=element_at(&List,j);
			if(mark[y]==0){
				parent[y]=x;
				mark[y]=1;
				push(&L,y);
			}
		}
	}
}

void duyet(Graph *G) {
	int i,j;
	for(j=1;j<=G->n;j++) {
		mark[j]=0;
		parent[j]=0;
	}
	breath_first_sreach(G, 1);
	for (i = 1; i <= G->n; i++ )
		if (mark[i] == 0)
			breath_first_sreach(G,i);
}

int main(){
	Graph G;
	int n,m,e,u,v,i;
	FILE* f=fopen("bai1.txt","r");
	fscanf(f,"%d%d",&n,&m);
	intit_graph(&G,n);
	for(e=1;e<=m;e++){
		fscanf(f,"%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	duyet(&G);
	for(i=1; i<=n; i++)
 		printf("%d %d\n", i, parent[i]);
}
