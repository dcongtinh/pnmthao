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
//------------------------------------------
typedef struct {
	int n;
	int A[MAX][MAX];
} Graph;
void init_graph(Graph* G, int n) {
	G->n = n;
	int i, j;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
	 		G->A[i][j] = 0;
}
void add_edge(Graph* G, int u, int v) {
	G->A[u][v] = 1; 
	G->A[v][u] = 1; 
}
int adjacent(Graph* G, int x, int y) {
	return G->A[x][y] != 0;
}
List neighbors(Graph* G, int x) {
	int y;
	List list;
	make_null_list(&list);
	for (y = 1; y <= G->n; y++)
		if (adjacent(G, x, y))
			push_back(&list, y);
	return list;
}
//---------------------------------------
int mark[MAX];
void traversal(Graph* G, int x) {
	if (mark[x] == 1)
		return;
	mark[x] = 1; 
	List list = neighbors(G, x);
	int j;
	for (j = 1; j <= list.size; j++) {
		int y = element_at(&list, j);
		traversal(G, y);
	}
}
void depth_first_search(Graph* G) {
	int j;
	for (j = 1; j <= G->n; j++)
		mark[j] = 0;
	traversal(G, 1);
}
int main() {
    Graph G;
	int n, m, u, v, e;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	depth_first_search(&G);
    int j, Result = 0;
    for (j = 1; j <= G.n; j++) 
        if (mark[j] == 0) 
            Result = 1;
    if(Result == 0) printf("DUOC");
    else printf("KHONG");
}

