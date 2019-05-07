#include <stdio.h>
#define MAX 100
typedef int ElementType;
typedef struct{
	ElementType data[MAX];
	int size;
}List;
void make_null(List* L){
	L->size=0;
}
void push_back(List* L, ElementType x){
	L->data[L->size]=x;
	L->size++;
}
ElementType element_at(List* L, int i){
	return L->data[i-1];
}
void copy_list(List* L1,List* L2){
	make_null(L1);
	int i;
	for(i=0; i<L2->size; i++){
		L1->data[i]=L2->data[i];
		L1->size;
	}
}
//------------------------------------
typedef struct{
	int data[MAX];
	int front,rear;
}Queue;
void make_null_queue(Queue* Q){
	Q->front = 0;
	Q->rear  = -1;
}
void push(Queue* Q, int x){
	Q->rear++;
	Q->data[Q->rear] =x;
}
int top(Queue* Q){
	return Q->data[Q->front];
}
void pop(Queue* Q){
	Q->front++;
}
int empty(Queue* Q){
	return Q->front > Q->rear;
}

typedef struct{
	int n;
	int A[MAX][MAX];
}Graph;
void init_graph(Graph* G, int n){
	int i,j;
	G->n = n;
	for(i=1; i<=G->n; i++)
		for(j=1; j<=G->n; j++)
			G->A[i][j] = 0;

}
void add_edge(Graph* G,int x, int y){
	G->A[x][y] =1;
}
void topo_sort(Graph* G,List* L){
	int d[MAX];
	int x,u;
	for(u=1; u<=G->n; u++)
		d[u]=0;
	for(x=1; x<=G->n; x++)
		for(u=1; u<=G->n; u++){
			if(G->A[x][u] !=0)
			d[u]++;
		}
	Queue Q;
	make_null_queue(&Q);
	make_null(L);
	for(u=1;u<=G->n; u++){
		if(d[u] ==0)
			push(&Q,u);
	}
	int k=0;
	while (!empty(&Q)){
		int u = top(&Q);
		pop(&Q);
		push_back(L,u);
		int v;
		for(v=1;v<=G->n; v++){
			if(G->A[u][v] !=0){
				d[v]--;
				if(d[v] ==0){
					push(&Q,v);
				}
			}
		}
	}
}
int main(){
	Graph G;
	List L;
	int n,m,u,v,e,i;
	freopen("dt.txt","r", stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e=1; e<=m; e++){
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	topo_sort(&G,&L);
	for(i=1; i<=L.size;i++)
		printf("%d ",element_at(&L,i));
	return 0;
}
