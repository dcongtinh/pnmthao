/*KIEM TRA TINH LIEN THONG CUA DO THI VO HUONG */
#include <stdio.h>
typedef struct {
    int A[100][100];
    int n;
} Graph;

void init_graph(Graph* G, int n) {
    G->n = n;
    memset(G->A, 0, sizeof(G->A));
}
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
/* Kiem tra y co ke voi x khong */
int adjacent(Graph* G, int x, int y) {
	return G->A[x][y] != 0;
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
/* Bien ho tro */
int mark[100];
/* Duyet de quy dinh x */
void traversal(Graph* G, int x) {
	/* Neu dinh x da duyet, khong lam gi ca */
	if (mark[x] == 1)
		return;
	/* Nguoc lai, duyet no */
	//printf("Duyet %d\n", x);
	mark[x] = 1; // Danh dau da duyet no
	
	/* Lay cac dinh ke cua no và duyet cac dinh ke */
	List list = neighbors(G, x);
	int j;
	for (j = 1; j <= list.size; j++) {
		int y = element_at(&list, j);
		traversal(G, y);
	}
}

void depth_first_search(Graph* G) {
	/* Khoi tao mark, chua dinh nao duoc xet */
	int j;
	for (j = 1; j <= G->n; j++)
		mark[j] = 0;
	traversal(G, 1);
}

int connected(Graph* G){
	depth_first_search(G);
	int j, Result = 1;
    for (j = 1; j <= G->n; ++j)
        if (mark[j] == 0)
            Result = 0;
    return Result;
}

int main() {
    Graph G;
    int m, n, e, i;
    freopen("Input_02.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (e = 1; e <= m; e++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G.A[u][v] = G.A[v][u] = 1;
    }

    printf("%d\n", connected(&G));
    return 0;
}
