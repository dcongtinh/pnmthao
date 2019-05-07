#include <stdio.h>
#define MAXN 100
typedef struct {
	int u, v; // Dinh dau u, dinh cuoi v
	int w; // Trong so w
} Edge;

typedef struct {
	int n, m; // n: Dinh, m: cung
	Edge edges[100]; // /luu cac cung cua do thi
} Graph;

#define INFINITY 9999999
int pi[MAXN]; // Luu chieu dai ngan nhat tu s den dinh dang xet
int p[MAXN]; // Luu dinh lien truoc tren duong di ngan nhat tu s den dinh dang xet

/* Khoi tao do thi G co n dinh */
void init_graph(Graph* G, int n) {
	G->n = n;
	G->m = 0;
}
/* Them trong so cung e = (x, y) vao do thi G */
void add_edge(Graph* G, int u, int v, int w) {
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
	G->m++;
}

void BellmanFord(Graph* G, int s) {
	int i, j, it,k;
	for (i = 1; i <= G->n; i++) {
		pi[i] = INFINITY; // Chieu dai tu s den cac dinh la vo cung
	}
	pi[s] = 0; 
	p[s] = -1; // Truoc dinh s khong co dinh nao ca
	
	// Lap n hoac n-1 lan deu duoc
	for (it = 1; it < G->n; it++) {
		// Duyet qua cac cung va cap nhat (neu thoa)
		for (k = 0; k < G->m; k++) {
			int u = G->edges[k].u; // Dinh dau
			int v = G->edges[k].v; // Dinh cuoi
			int w = G->edges[k].w; // Trong so
			
			if (pi[u] + w < pi[v]) { // Chieu dai tu ((s -> u) + (u -> v)) < (s -> v)) 
				// VD :   1 -> 3 = 5
				//		  3 -> 4 = 2
				// Nhung: 1 -> 4 = 6 thi chon duong tu 1 -> 4 khong chon duong 1 -> 3 -> 4
				pi[v] = pi[u] + w; // Cap nhat lai duong di ngan nhat
				p[v] = u;
			}
		}
	}
}

int main(){
	
	freopen("dothi.txt", "r", stdin); 
	Graph G;
	int n, m, u, v, w, e,i;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	
	BellmanFord(&G,1);
	for(i=1;i<=G.n;i++)
		printf("pi[%d]=%d, p[%d]=%d\n",i,pi[i],i,p[i]);
	

}
