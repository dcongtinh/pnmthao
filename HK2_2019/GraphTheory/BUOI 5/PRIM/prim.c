#include <stdio.h>
#define INF  999999
#define MAX 100
#define NO_EDGE 0
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
void copy_list(List *L1, List *L2){
	make_null_list(L1);
	int i;
	for(i=1;i<=L2->size;i++)
		push_back(L1,element_at(L2,i));
	
}
//---------------------------------------
typedef struct{
	int A[MAX][MAX];
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
//-------------------------------------------------
int distanceFrom(int u, List* S, Graph *G){
	int min_dist = INF;
	int min_v =-1;
	int i;
	for(i=1;i<=S->size;i++){
		int v =element_at(S,i);
		if(G->A[u][v]!=NO_EDGE && min_dist>G->A[u][v]){
			min_dist=G->A[u][v];
			min_v=v;
		}
	}
	return min_v;
}
int mark[MAX];
int Prim(Graph *G, Graph *T){
	init_graph(T,G->n);
	List L;
	make_null_list(&L);
	int i,u;
	for(i=1;i<=G->n;i++)
		mark[i]=0;
	push_back(&L,1);
	mark[1]=1;
	int sum_w =0;
	for(i=1;i<=G->n-1;i++){
		int min_dist = INF, min_u, min_v;
		for(u=1;u<=G->n;u++)
			if(mark[u]==0){
				int v = distanceFrom(u,&L,G);
				if(v!=-1 && G->A[u][v]<min_dist){
					min_dist = G->A[u][v];
					min_u=u;
					min_v=v;
				}
			}	
		push_back(&L,min_u);
		mark[min_u]=1;		
		add_edge(T,min_u,min_v,min_dist);
		sum_w+=min_dist;
	}
	return sum_w;
}
//-------------------------------------
int main(){
	Graph G,T;
	freopen("dt.txt", "r", stdin); 
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	int sum_w=Prim(&G,&T);
	printf("%d\n",sum_w);
	for(u=1;u<=T.n;u++)
		for(v=u+1; v<=T.n;v++)
			if(T.A[u][v]!=NO_EDGE)	
				printf("%d %d %d\n",u,v,T.A[u][v]);
}


