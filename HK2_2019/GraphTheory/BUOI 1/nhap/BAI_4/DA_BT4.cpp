#include<stdio.h>
#define  Max_Vertices 100
typedef struct{
	int n; // n: so dinh
	/* Ma tran dinh-dinh*/
	int A[Max_Vertices][Max_Vertices];
}Graph;
// Khoi tao do thi n dinh, m cung
void init_graph(Graph *G, int n){
	int i,j;
	G->n=n;
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
		  G->A[i][j]=0;
}
/* Them cung e=(x,y) vao do thi G
void add_edges(Graph *G, int x, int y){
	G->A[x][y]=1; //x ke y
	G->A[y][x]=1; //y ke x
}*/

// Them cung e=(x,y) vao do thi G, TRUONG HOP DA CUNG
void add_edges(Graph *G, int x, int y){
	G->A[x][y]+=1; //x ke y
	G->A[y][x]+=1; //y ke x
}

// Kiem tra xem y co ke voi x hay khong?
int adjacent (Graph *G, int x, int y){
	return G->A[x][y];
}
/*/ Tinh bac cua dinh x: deg(x) 
int degree(Graph *G, int x){
	int y, deg=0;
	for(y=1; y<=G->n; y++)
		if(G->A[x][y]>0)
			deg++;
		return deg;
}*/
// Tinh bac cua dinh x: deg(x), TRUONG HOP DA CUNG 
int degree(Graph *G, int x){
	int y, deg=0;
	for(y=1; y<=G->n; y++)
		deg+=G->A[x][y];
	return deg;
}
int main(){
	Graph G;
	int n=4,v;
	init_graph(&G,n);
	add_edges(&G,1,2);
	add_edges(&G,1,3);
	add_edges(&G,1,3);
	add_edges(&G,3,4);
	add_edges(&G,1,4);
	for(v=1;v<=n;v++)
		printf("deg(%d)=%d\n",v,degree(&G,v));

}


