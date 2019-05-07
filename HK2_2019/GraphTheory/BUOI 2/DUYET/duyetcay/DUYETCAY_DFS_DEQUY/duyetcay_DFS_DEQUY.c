#include <stdio.h>
#include<stdio.h>
#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct {
    ElementType data[MAX_ELEMENTS];
    int size;
} List;

/* Tao danh sach rong */
void make_null_list(List* L) {
    L->size = 0;
}
/* Them mot phan tu vao cuoi danh sach */
void push_back(List* L, ElementType x) {
    L->data[L->size] = x;
    L->size++;
}
/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1 */
ElementType element_at(List* L, int i) {
    return L->data[i-1];
}
/* Tra ve so phan tu cua danh sach */
int count_list(List* L) {
    return L->size;
}

#define MAX_VERTEXES 100
#define MAX_EDGES 500
#define NO_EDGE 0 //hoac gia tri dac biet nao do
typedef struct {
	int n,m;
	int A[MAX_VERTEXES][MAX_VERTEXES];
} Graph;
int mark[MAX_VERTEXES];
/* Khoi tao do thi G co n dinh */
void init_graph(Graph *G, int n){
	int i,j;
	G->n=n;
	for(i=1; i<=n;i++)
		for(j=1; j<=n; j++)
		  G->A[i][j]=0;
}
// Them cung e=(x,y) vao do thi G
void add_edge(Graph *G, int x, int y){
	G->A[x][y]=1; //x lien thuoc e
	G->A[y][x]=1; //y lien thuoc e
}
// Kiem tra xem y co ke voi x hay khong?
int adjacent (Graph *G, int x, int y){
	return G->A[x][y]!=0;
}
/* Tim cac dinh ke cua dinh x */
List neighbors(Graph* G, int x) {
	int y;
	List list;
	make_null_list(&list);
	for (y = 1; y <= G->n; y++)
		if(adjacent(G, x, y))
			push_back(&list, y);
	return list;
}

int parent[MAX_VERTEXES];
/*Duyet do thi theo chieu sau - DE QUY*/
void traversal(Graph *G,int x){
	if(mark[x]==1) return;
	mark[x]=1;
	List list=neighbors(G,x); 
	int j;
	for(j=1; j<= list.size; j++){ 
		
		int y=element_at(&list,j);
		if(mark[y]==0)
			parent[y]=x;
		traversal(G,y);
		}
	}

void duyet(Graph *G){
	int i,j;
	for(j=1;j<=G->n;j++) 
	{
		mark[j]=0;
		parent[j]=0;
	}
	traversal(G, 1);
	for (i = 1; i <= G->n; i++ )  
	    if (mark[i] == 0) traversal(G,i);
	}
	
int main(){
	Graph G;
	int n, m, u, v, e,i;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n,&m);
	init_graph(&G,n);
	for (e = 1; e <= m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G,u,v);
	}
	duyet(&G);
	for(i=1;i<=n;i++)
 	printf("%d %d\n",i,parent[i]);
}
