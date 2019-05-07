#include <stdio.h>
#define MAX 100
typedef struct{
	int u,v;
	int w;
}Edge;
typedef struct{
	Edge edge[MAX];
	int n;
	int m;
}Graph;
int parent[MAX];
void init_graph(Graph *G, int n){
	int i,j;
	G->n=n;
	G->m=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			G->edge[i*j].u=G->edge[i*j].v=G->edge[i*j].w=0;
}
void add_edge(Graph *G, int u, int v, int w){
	G->edge[G->m].u=u;
	G->edge[G->m].v=v;
	G->edge[G->m].w=w;
	G->m++;
}
int findRoot(int u){
	if(parent[u]==u) return u;
	return findRoot(parent[u]);
}
void Swap(Edge *a, Edge *b){
	Edge temp;
	temp =*a;
	*a=*b;
	*b=temp;
}
void Sort_Edge(Graph *G){
	int i,j;
	for(i=0;i<G->m-1;i++)
		for(j=G->m-1;j>=i+1;j--)
			if(G->edge[j-1].w>G->edge[j].w) Swap(&G->edge[j-1],&G->edge[j]);
}
int Kruskal(Graph *G, Graph *T){
	//sap xap cac cung cua G theo thu tu tang dan
	Sort_Edge(G);
	//Khoi tao T rong
	init_graph(T,G->n);
	int u;
	for(u=1;u<=G->n;u++)
		parent[u]=u;
	int sum_w=0;
	//Duyet qua cac cung cua G (da sap xep)
	int e,v,w;
	for(e=0;e<G->m;e++){
		u=G->edge[e].u;
		v=G->edge[e].v;
		w=G->edge[e].w;
		int root_u = findRoot(u);
		int root_v = findRoot(v);
		if(root_u!=root_v){
			add_edge(T,u,v,w);
			//Gop 2 BPLT root_u va root_v lai
			parent[root_v]=root_u;
			sum_w+=w;
		}			
	}
	return sum_w;
}

int main(){
	Graph G,T;
	int n,m,u,v,w,e;
	freopen("dt.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e=0;e<m;e++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
	}
	int sum_w=Kruskal(&G,&T);
	printf("%d\n",sum_w);
	for(e=0;e<T.m;e++)
		if(T.edge[e].u>T.edge[e].u)
			printf("%d %d %d\n",T.edge[e].u,T.edge[e].u,T.edge[e].w);
		else 	printf("%d %d %d\n",T.edge[e].v,T.edge[e].u,T.edge[e].w);
}

