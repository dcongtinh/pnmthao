#include <stdio.h>
#define MAXN 100
#define INF 9999999
typedef struct {
	int u, v; 
	int w; 
} Edge;

typedef struct {
	int n, m; 
	Edge edges[100]; 
} Graph;
int pi[MAXN]; // Luu chieu dai ngan nhat tu s den dinh dang xet
int p[MAXN]; // Luu dinh lien truoc tren duong di ngan nhat tu s den dinh dang xet

void init_graph(Graph* G, int n) {
	G->n = n;
	G->m = 0;
}

void add_edge(Graph* G, int u, int v, int w) {
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
	G->m++;
}

void BellmanFord(Graph* G, int s) {
	int i, j, it,k;
	for (i = 1; i <= G->n; i++) 
		pi[i] = INF; 
	pi[s] = 0; 
	p[s] = -1; 
	for (it = 1; it < G->n; it++) {
		for (k = 0; k < G->m; k++) {
			int u = G->edges[k].u; 
			int v = G->edges[k].v; 
			int w = G->edges[k].w; 	
			if (pi[u] + w < pi[v]) { 
				pi[v] = pi[u] + w; 
				p[v] = u;
			}
		}
	}
}

int main(){
	Graph G;
	int n, m, u, v, w, e, i;
		freopen("dt.txt", "r", stdin); 
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	BellmanFord(&G,1);
	for(i=1;i<=G.n;i++)
		printf("pi[%d] = %d, p[%d] = %d\n",i,pi[i],i,p[i]);
}