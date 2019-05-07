#include <stdio.h>
#define oo 9999999
typedef int Position;
typedef int ElementType;
typedef struct {
	ElementType data[100];
	Position size;
} List;
void make_null(List* L) {
	L->size = 0;
}
void push_back(List* L, ElementType x) {
	L->data[L->size] = x;
	L->size++;
}
ElementType element_at(List* L, int i) {
	return L->data[i-1];
}
//-------------------------------------------------
typedef int datatype;
typedef struct {  
	datatype data[100];  
	int front, rear; 
} Queue;  
void make_null_queue(Queue* Q) { 
	Q->front = 0;  
	Q->rear = -1; 
}  
int empty(Queue* Q) { 
	return Q->front > Q->rear; 
} 
void push(Queue* Q, int x) {  
	Q->rear++;  
	Q->data[Q->rear] = x; 
}  
int top(Queue* Q) {  
	return Q->data[Q->front]; 
}  
void pop(Queue* Q) {  
	Q->front++; 
}  

//-------------------------------------------------
typedef struct {
	int n; 
	int A[100][100];
} Graph;
void init_graph(Graph* G, int n) {
	int i, j;
	G->n = n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			G->A[i][j] = 0;
}
void add_edge(Graph* G, int x, int y) {
	G->A[x][y]	+=	1; 
}
int adjacent(Graph* G, int x, int y) {
	return G->A[x][y] != 0;
}
List neighbors(Graph* G, int x) {
	int y;
	List list;
	make_null(&list);
	for (y = 1; y <= G->n; y++)
		if (adjacent(G, x, y))
			push_back(&list, y);
	return list;
}
//-------------------------------------------------
int min(int a, int b){
	if(a>=b) return b;
	else return a;
}
int max(int a, int b){
	if (a>b) return a;
	else return b;
}
int d[100];

void topo_sort(Graph *G,List *L){
	int d[100];
	int x, u;
	Queue Q;
	make_null_queue(&Q);
	for (u = 1; u <= G->n; u++)	
		d[u] = 0;
	for (x = 1; x <= G->n; x++)
	    for (u = 1; u <= G->n; u++)
 			if (G->A[x][u] != 0)
 				 d[u]++;
 	for(u=1;u<=G->n;u++)
 		if(d[u]==0)	push(&Q,u);
  	make_null(L);
 	while(!empty(&Q)){
 		int u = top(&Q);
 		pop(&Q);
 		push_back(L,u);
 		List list = neighbors(G,u);
 		for(x=1; x<=list.size; x++){
 			int v = element_at(&list,x);
 			d[v]--;
 			if(d[v]==0)
 				push(&Q,v);
		 }
	 }	
}

int main() {
	Graph G;
	int n, u, x, v, i, j ;
	List L;
	FILE* file = fopen("dt.txt", "r");
	fscanf(file,"%d", &n);
	init_graph(&G, n+2); 
	d[n+1] = 0;
	for (u = 1; u <= n; u++) {
		fscanf(file,"%d",&d[u]); 
		do {
			fscanf(file,"%d", &x);
			if (x > 0) add_edge(&G, x, u);
		}while (x > 0);
	}
	//--Kiem tra du lieu doc tu file, xoa sau khi kiem tre ket qua dung
	for (i = 1; i <= n; i++) printf("%d ",d[i]);
	printf("\n");
	for (i = 1; i <= n; i++)  {
		for (j = 1; j <= n; j++)
			printf("%d ", G.A[i][j]);
		printf("\n");
	}
	//------------------------------------------------------------------
	//--Noi dinh n+1 voi dinh khong co cung di den no
	for (u = 1; u <= n; u++) {
		int deg_neg = 0;
		for (x = 1; x <= n; x++)
			if (G.A[x][u] > 0)
				deg_neg++;
		if (deg_neg == 0)
			add_edge(&G, n+1, u); 
	}
	//--Noi dinh khong co cung di ra den dinh n+2
	for (u = 1; u <= n; u++) {
		int deg_pos = 0;
		for (v = 1; v <= n; v++)
			if (G.A[u][v] > 0)
				deg_pos++;
		if (deg_pos == 0)
			add_edge(&G, u, n+2); 
	}
	//--Kiem tra du lieu doc tu file, xoa sau khi kiem tre ket qua dung
	printf("\n");
	for (i = 1; i <= n+2; i++)  {
		for (j = 1; j <= n+2; j++)
			printf("%d ", G.A[i][j]);
		printf("\n");
	}
	//------------------------------------------------------------------
	topo_sort(&G,&L);
	int t[100];
	//Kiem tra L, sau do xoa
	printf("\n");
	for (i = 1; i <= L.size; i++) 
		printf("%d ",element_at(&L, i));
	printf("\n");
	//Xac dinh thoi diem som nhat
	t[n+1] = 0; 
	for (j = 2; j <= L.size; j++) {
		int u = element_at(&L, j);
		t[u] = 0; 
		for (x = 1; x <= G.n; x++)
			if (G.A[x][u] > 0)
				t[u] = max(t[u], t[x] + d[x]);
	}
	//Xac dinh thoi diem tre nhat
	int T[100];
	T[n+2] = t[n+2];
	for (j = L.size - 1; j >= 1; j --) {
		int u = element_at(&L, j);
		T[u] = oo;
		for (v = 1; v <= G.n; v++)
			if (G.A[ u][v] > 0)
				T[u] = min(T[u], T[v] - d[u]);
	}
	for(u=1; u<=G.n; u++)
		printf("t[%d]: %d \t T[%d]: %d\n",u,t[u],u,T[u]);
}

