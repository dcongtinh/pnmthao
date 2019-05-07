#include <stdio.h>
#define MAX_VERTICES 100
#define MAX_EDGES 100
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

#include <stdio.h>
#define MAX_VERTICES 100
#define MAX_EDGES 100
typedef struct{
	int n,m;
	int A[MAX_VERTICES][MAX_EDGES];
}Graph;

/*Khoi tao do thi G*/
void init_graph(Graph *G, int n, int m){
	int i,j;
	G->n=n;
	G->m=m;
	for(i=1; i<=n; i++)
		for(j=1; j<=m; j++)
			G->A[i][j]=0;
}
/*Them cung e=(x,y) vao do thi G*/
void add_edge(Graph *G, int e, int x, int y){
	G->A[x][e]+=1;
	G->A[y][e]+=1;
}
/* Kiem tra dinh y co ke voi dinh x hay khong?*/
int adjacent(Graph *G, int x, int y){
	int e;
	for(e=1; e<=G->m; e++)
		if(G->A[x][e]==1 && G->A[y][e]==1)
			return 1;
	return 0;
}

/* Tim cac dinh ke cua dinh x */
List neighbors(Graph* G, int x) {
	int y;
	List list;
	make_null_list(&list);
	for (y = 1; y <= G->n; y++)
		if (adjacent(G, x, y))
			push_back(&list, y);
	return list;
}
int main(){
	Graph G; List L;
   	int n, m, u, v, e,y;
	freopen("dothi.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n,m);
	for (e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, e, u, v);
	}
	L= neighbors(&G, 1);
	for (y = 1; y <= L.size; y++)
			if(1!=y)
				printf("%d\n", element_at(&L, y));
	
}
