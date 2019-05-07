#include <stdio.h>
#define MAXN 100
#define INFINITY 9999999
typedef struct {
	int u, v; 
	int w; 
} Edge;
typedef struct {
	int n, m; 
	Edge edges[100]; 
} Graph;
int pi[MAXN]; 
int p[MAXN];
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
	for (i = 1; i <= G->n; i++) {
		pi[i] = INFINITY; 
	}
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
/* Kiem tra chu trinh am */
int KTCTAM(Graph* G){ 
	int k, result = 0;
	for (k = 0; k < G->m; k++) { // Duyet qua tat ca cac cung
		int u = G->edges[k].u;
		int v = G->edges[k].v;
		int w = G->edges[k].w;
		if (pi[u] + w < pi[v]) { // Neu co the cap nhat duong di ngan nhat thi co chu trinh am
			result = 1;
		}
	}
	return result;
}

int main(){
	Graph G;
	int n, m, u, v, w, e;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	BellmanFord(&G,1);
	if(KTCTAM(&G) == 1)
		printf("YES");
	else
		printf("NO");

}
