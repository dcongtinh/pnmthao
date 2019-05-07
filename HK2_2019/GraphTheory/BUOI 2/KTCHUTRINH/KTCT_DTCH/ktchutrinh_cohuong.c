#include <stdio.h>
#define MAX 100	
typedef int ElementType;
typedef struct {
	ElementType data[MAX];
	int size;
} List;
void make_null(List* L) 
{
	L->size = 0;
}
void push_back(List* L, ElementType x) 
{
	L->data[L->size] = x;
	L->size++;
}
ElementType element_at(List* L, int i) 
{
	return L->data[i-1];
}
//-------------------------------------------
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
}
int adjacent(Graph* G, int x, int y) {
	return G->A[x][y] == 1;
}
List neighbors(Graph* G, int x) {
	int y;
	List list;
	make_null(&list);
	for (y = 1; y <= G->n; y++)
		if (adjacent(G, x, y))
			push_back(&list, y);
	return list;
}
//------------------------------
#define white 0
#define black 1
#define gray 2
int color[MAX];
int cycle;
void dfs(Graph *G, int x) {
	color[x] = gray;
	int j;
	List list = neighbors(G, x);
	for(j = 1; j <= list.size; j++) {
		int y = element_at(&list, j);
		if(color[y] == gray) {
			cycle = 1;
			return;
		  }
		if(color[y] == white) 
			dfs(G,y);
	}
	color[x] = black;
}

int contains_cycle(Graph *G) {
	int j;
	for(j = 1; j <= G->n; j++)
		color[j] = white;	
	cycle = 0;	
	for(j = 1; j <= G->n; j++)
		if(color[j] == white)
			dfs(G,j);
	return cycle;
}

int main() {
	Graph G;
	int n, m, y, u, v;
	freopen("dt5.txt", "r", stdin);	
	scanf("%d %d", &n, &m);
	init_graph(&G,n);
	for(y = 1; y <= m; y++) {
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}	
   if(contains_cycle(&G)) 
		printf("Yes");
   else
		printf("No");
}
