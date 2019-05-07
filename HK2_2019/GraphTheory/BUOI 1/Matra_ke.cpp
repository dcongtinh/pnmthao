#include<stdio.h>
#define MAX_VERTICES 100
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

int main(){
	Graph G;
	int n, m, u, v, e, i, j;
    freopen("dothi.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
    for(i=1; i<=n;i++)
		{
		  for(j=1; j<=n; j++)
			printf("%d ",G.A[i][j]);
		  printf("\n");
		}
}
