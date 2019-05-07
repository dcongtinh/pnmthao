#include<stdio.h>
#define MAX 100
typedef struct{
	int A[MAX][MAX];
	int n;
}Graph;

void init_graph(Graph* G, int n){
	G->n = n;
	int i, j;
	for(i = 1; i <=G->n; i++)
		for(j = 1; j <=G->n; j++)
			G->A[i][j] = 0;
}

void add_edge(Graph* G, int x, int y){
	G->A[y][x] = 1;
}
//------------------------
typedef struct {
	int data[MAX];
	int size;
} List;
void make_null(List* L) {
	L->size = 0;
}
void push_back(List* L, int x) {
	L->data[L->size] = x;
	L->size++;
}
int element_at(List* L, int i){
	return L->data[i - 1];
}
void copy_list(List* L1, List* L2){
	make_null(L1);
	int i;
	for(i = 0; i < L2->size; i++)
		push_back(L1, L2->data[i]);
}
//------------------------
int rank[MAX];
int ranking(Graph* G){
	int d[MAX];
	int u, x;
	for(u = 1; u <= G->n; u++)
		d[u] = 0;
	for(x = 1; x <= G->n; x++)
		for(u = 1; u <= G->n; u++)
			if(G->A[x][u] != 0)
				d[u]++;
	List L1, L2;
	make_null(&L1);
	for(u = 1; u <= G->n; u++)
		if(d[u] == 0)
			push_back(&L1, u);
	int i, k = 1;
	while(L1.size > 0){
		make_null(&L2);
		for(i = 1; i <= L1.size; i++){
			int u = element_at(&L1, i);
			rank[u] = k;
			int v;
			for(v = 1; v <= G->n; v++)
				if(G->A[u][v] != 0){
					d[v]--;
					if(d[v] == 0)
						push_back(&L2, v);
				}
		}
		copy_list(&L1, &L2);
		k++;
	}
}
//-----------------------
int main(){
	Graph G;
	int n, m, u, v, e, i, sum = 0;
 	freopen("dt.txt", "r", stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e = 1; e <= m; e++){
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	ranking(&G);
	for(i=1; i<=G.n; i++)
		printf("%d\n",rank[i]);
	for(i=1; i<=G.n; i++)
		sum += rank[i];
	printf("%d", sum);
}
