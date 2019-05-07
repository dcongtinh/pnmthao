#include <stdio.h>
#define MAX 100
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
//------------------------------------------
typedef struct {
	int data[MAX];
	int size;
}Stack;
void make_null_stack(Stack *S){
	S->size=0;
}
void push(Stack *S, int x){
	S->data[S->size]=x;
	S->size++;
}
int top (Stack *S){
	return S->data[S->size-1];
}
void pop(Stack *S){
	S->size--;
}
int empty(Stack *S){
	return S->size==0;
}
//------------------------------------------
typedef struct {
	int n,m;
	int A[MAX][MAX];
} Graph;

void init_graph(Graph *G, int n){
	int i,j;
	G->n=n;
	
	for(i=1; i<=n;i++)
		for(j=1; j<=n; j++)
		  G->A[i][j]=0;
}

void add_edge(Graph *G, int x, int y){
	G->A[x][y]=1; 
	G->A[y][x]=1; 
}

int adjacent (Graph *G, int x, int y){
	return G->A[x][y]!=0;
	
}

List neighbors(Graph* G, int x) {
	int y;
	List list;
	make_null_list(&list);
	for (y = 1; y <= G->n; y++)
		if(adjacent(G, x, y))
			push_back(&list, y);
	return list;
}
int mark[MAX];
void depth_first_search(Graph *G, int k){
	Stack S;
	make_null_stack(&S);
	int j;
	push(&S,k);
	while(!empty(&S))  {
		int x=top(&S);  
		pop(&S);
		if(mark[x]!=0) continue;
		printf("%d\n",x);
		mark[x]=1;
		List list=neighbors(G,x); 
		for(j=1; j<=list.size; j++) { 
			int y=element_at(&list,j);
			push(&S,y);
		}
	}
}
void duyet(Graph *G) {
	int i,j;
	for(j=1; j<=G->n; j++)
		mark[j]=0;
	depth_first_search(G,1);
	for (i=1; i<=G->n; i++)
		if (mark[i] == 0)
			depth_first_search(G,i);
}
int main(){
	Graph G;
	int n, m, u, v, e;
	FILE* f=fopen("dothi.txt","r");
    fscanf(f,"%d%d",&n,&m);
	init_graph(&G, n);
	for (e = 0; e < m; e++) {
		fscanf(f,"%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	duyet(&G);
}
