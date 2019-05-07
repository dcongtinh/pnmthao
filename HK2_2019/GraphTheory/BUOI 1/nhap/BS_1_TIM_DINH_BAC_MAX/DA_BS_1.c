#include<stdio.h>
#define MAX_VERTICES 100
#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct {
ElementType data[MAX_ELEMENTS];
    int size;
} List;

void make_null(List* L) {
    L->size = 0;
}

void push_back(List* L, ElementType x) {
    L->data[L->size] = x;
    L->size++;
}

ElementType element_at(List* L, int i) {
    return L->data[i-1];
}

int count_list(List* L) {
    return L->size;
}

typedef struct {
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph* G, int n) {
	int i, j;
	G->n = n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			G->A[i][j] = 0;
}

void add_edge(Graph* G, int x, int y) {
	G->A[x][y] = 1; 
	G->A[y][x] = 1;
}

int adjacent(Graph* G, int x, int y) {
    return G->A[x][y]!=0;
}
// TH khong Da Cung
int degree(Graph* G, int x) {
	int e, deg = 0;
	for (e = 1; e <= G->n; e++)
		if (G->A[x][e] == 1)
			deg++;
	return deg;
}

List neighbors(Graph* G, int x){
 	int y;
	List list;
	make_null(&list);
	for (y = 1; y <= G->n; y++)
		if (adjacent(G, x, y) && y != x)
			push_back(&list, y);
	return list;
}
/* Dinh có bac lon nhat */
void count(Graph* G){
 	int dinh, i, max = 0;
	for (i = 1; i <= G->n; i++){
		if(degree(G, i) > max){
			max = degree(G, i);
			dinh = i;
		}
	}
	printf("%d %d\n", dinh, max);
}
int main(){
	Graph G;
	int n, m, u, v, e;
	freopen("dothi.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	count(&G);
}
