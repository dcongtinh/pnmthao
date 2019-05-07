#include <stdio.h>
#define MAXN 100
#define INFINITY 999999
#define NO_EDGE 0
typedef struct{
	int A[MAXN][MAXN];
	int n;
}Graph;
void init_graph(Graph *G, int n){
	int i,j;
	G->n = n;
	for ( i = 1 ; i <= G->n ; i++ )
		for ( j = 1 ; j <= G->n ; j++ )
			G->A[i][j] = 0;
}
void add_edge(Graph *G, int u, int v, int w){
G->A[u][v] = w;
    G->A[v][u] = w;
}
//---------------------------------------
int mark[MAXN];
int pi[MAXN];
int p[MAXN];
void Dijkstra(Graph *G, int s){
	int i,j,it;
	for ( i = 1 ; i <= G->n ; i++ ){
		mark[i] = 0;
		pi[i] = INFINITY;
	}
	pi[s] = 0;
	p[s] = -1;
	for ( it = 1 ; it < G->n ; it++ ){
		int min_pi = INFINITY;
		for ( j = 1 ; j <= G->n ; j++)
			if ( mark[j] == 0 && pi[j] < min_pi ){
				min_pi = pi[j];
				i = j;
			}
		mark[i] = 1;
		for ( j = 1 ; j <= G->n ; j ++)
			if ( mark[j] == 0 && G->A[i][j] != NO_EDGE)
				if ( G->A[i][j] + pi[i] < pi[j]){
					pi[j] = G->A[i][j] + pi[i];
					p[j] = i;
				}
	}
}
int main(){
	Graph G;
	int n, m, u, v, w, e;
	freopen("dt3.txt","r",stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	Dijkstra(&G,1);
	if ( pi[n] == INFINITY )	printf("%d",-1);
	else 	printf("%d",pi[n]);
	
}

