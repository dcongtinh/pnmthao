#include <stdio.h>
#define MAXN 100
typedef struct{
	int A[MAXN][MAXN];
	int n;
} Graph;
void init_graph(Graph *G, int n){
	int i,j;
	G->n = n;
	for ( i = 1 ; i <= G->n ; i++ )
    	for ( j = 1 ; j <= G->n ; j++ )
	    	G->A[i][j] = 0;
}
void add_edge(Graph *G, int u, int v, int chieu){
    if(chieu == 1)
		G->A[u][v] = 1;
	else{
	     G->A[u][v] = 1;
	     G->A[v][u] = 1;
		}
}
//-------------------------------------------------------
typedef struct{
	int size;
	int data[MAXN];
}Stack;
void make_null_stack(Stack *S){
	S->size = 0;
}
void push(Stack *S, int x){
	S->data[S->size] = x;
	S->size++;
}
int top(Stack *S){
	return S->data[S->size -1];
}

void pop(Stack *S){
	S->size --;
}
int element_at(Stack *S, int i){
	return S->data[i-1];
}
int empty(Stack *S){
	return S->size == 0;
}
//-------------------------------------------------------
int depth_first_search(Graph *G, int x ){
	int connect = 1;
	Stack S1;
	int mark[MAXN];
	int i;
	for ( i = 1 ; i <= G->n ; i++)
		mark[i] = 0;
	make_null_stack(&S1);
	push(&S1, x);
	while (S1.size > 0){
		int x = top(&S1); pop(&S1);
		if (mark[x] != 0) continue;
		mark[x] = 1;
		Stack S2; make_null_stack(&S2);
		for( i = 1 ; i <= G->n ; i++ ){
			if ( G->A[x][i] != 0 ){
				push(&S2,i);
			}
		}
		for (i = 0 ; i <= S2.size  ; i++ ){
			int y = element_at(&S2,i);
			push(&S1,y);
		}
	}
	for (i = 1 ; i <= G->n ; i ++)
		if ( mark[i] == 0){
			connect = 0;
			break;
		}		
	return connect;
}
int main(){
	Graph G;
	int n, m, u, v, w, e;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	int connect = 1;
	for(u = 1 ; u <= n ; u++)
		if(depth_first_search(&G, u) == 0 ){
			connect = 0;
			break;
		}
	if(connect == 1) 	printf("OKIE");
	else	printf("NO");	
}

