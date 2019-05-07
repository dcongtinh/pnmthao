#include<stdio.h>
#define  Max_Vertices 100
#define  Max_Edges 500
typedef struct{
	int n,m; // n: so dinh, m: so cung
	/* Ma tran dinh-cung*/
	int A[Max_Vertices][Max_Edges];
}Graph;
// Khoi tao do thi n dinh, m cung
void init_graph(Graph *G, int n, int m){
	int i,j;
	G->n=n;
	G->m=m;
	for(i=1; i<=n;i++)
		for(j=1; j<=m; j++)
		  G->A[i][j]=0;
}
// Them cung e=(x,y) vao do thi G
void add_edges(Graph *G, int e, int x, int y){
	G->A[x][e]=1; //x lien thuoc e
	G->A[y][e]=1; //y lien thuoc e
}
// Kiem tra xem y co ke voi x hay khong?
int adjacent (Graph *G, int x, int y){
	int e;
	for(e=1; e<=G->m; e++)
		if(G->A[x][e]==1 && G->A[y][e]==1)
			return 1;
	return 0;
}
// Tinh bac cua dinh x: deg(x)
int degree(Graph *G, int x){
	int e, deg=0;
	for(e=1;e<=G->m;e++)
		if(G->A[x][e]==1)
			deg++;
		return deg;
}
int main(){
	Graph G;
	int n,m,e,v,u;
	FILE* file=fopen("dothi.txt","r");
	fscanf(file,"%d%d",&n,&m);
	init_graph(&G,n,m);
	for(e=1; e<=m; e++){
		fscanf(file,"%d%d",&u,&v);
		add_edges(&G,e,u,v);
	}
	for(v=1;v<=n;v++)
		printf("deg(%d)=%d\n",v,degree(&G,v));	
}


