#include <stdio.h>
#define MAX 100
typedef int ElementType;
typedef struct {
    ElementType data[MAX];
    int size;
} List;
void make_null_list(List* L) {
    L->size = 0;
}
void push_back(List* L, ElementType x) {
    L->data[L->size] = x;
    L->size++;
}
ElementType element_at(List* L, int i) {
    return L->data[i-1];
}
//-------------------------------------------
typedef struct {
	int n,m;
	int A[MAX][MAX];
} Graph;
int mark[MAX];
void init_graph(Graph *G, int n){
	int i,j;
	G->n=n;
	for(i=1; i<=n;i++)
		for(j=1; j<=n; j++)
		  G->A[i][j]=0;
}
void add_edge(Graph *G, int x, int y){
	G->A[x][y]=1; 
	G->A[y][x]=1; 
}
int adjacent (Graph *G, int x, int y){
	return G->A[x][y]!=0;
}
List neighbors(Graph* G, int x) {
	int y;
	List list;
	make_null_list(&list);
	for (y = 1; y <= G->n; y++)
		if(adjacent(G, x, y))
			push_back(&list, y);
	return list;
}
//------------------------------------------
int parent[MAX];
void traversal(Graph *G,int x){
	if(mark[x]==1) return;
	mark[x]=1;
	List list=neighbors(G,x); 
	int j;
	for(j=1; j<= list.size; j++) { 
		int y=element_at(&list,j);
		if(mark[y]==0)
			parent[y]=x;
		traversal(G,y);
		}
	}

void duyet(Graph *G) {
	int i,j;
	for(j=1;j<=G->n;j++) {
		mark[j]=0;
		parent[j]=0;
	}
	traversal(G, 1);
	for (i = 1; i <= G->n; i++ )  
	    if (mark[i] == 0) 
		traversal(G,i);
}
	
int main(){
	Graph G;
	int n, m, u, v, e,i,j;
	FILE *file=fopen("bai1.txt","r");
	fscanf(file,"%d%d", &n,&m);
	init_graph(&G,n);
	for (e = 1; e <= m; e++) {
		fscanf(file,"%d%d", &u, &v);
		add_edge(&G,u,v);
	}
	duyet(&G);
	for(i=1;i<=n;i++)
 		printf("%d %d\n",i,parent[i]);
}
