#include<stdio.h>
#define MAX 100
typedef int ElementType;
typedef struct {
ElementType data[MAX];
int size;
} List;

void make_null(List* L){
	L->size = 0;
}

void push_back(List* L, ElementType x){
	L->data[L->size] = x;
	L->size++;
}

ElementType element_at(List* L, int i){
	return L->data[i-1];
}
//---------------------------------------------
typedef struct {  
	int n; 
	int A [MAX][MAX]; 
} Graph; 

void init_graph(Graph* G, int n) {  
	int i, j;  
	G->n = n;  
	for (i = 1; i <= n; i++)   
		for (j = 1; j <= n; j++)    
			G->A[i][j] = 0; 
}
 
void add_edge(Graph* G, int x, int y){
	G->A[x][y] += 1; 
}

int adjacent(Graph* G, int x, int y){  
	return G->A[x][y] != 0;
}

List neighbors(Graph* G, int x){
	int y;
	List list;
	make_null(&list);
	for(y = 1; y <= G->n; y++)
		if (adjacent(G, x, y))
			push_back(&list, y);
	return list;
}
//-------------------------------------
typedef struct{
	int data[MAX];  
	int size; 
} Stack;  
void make_null_stack(Stack* S) {  
	S->size = 0; 
}  
void push(Stack* S, int x){  
	S->data[S->size] = x;  
	S->size++; 
}  
int top(Stack* S) {  
	return S->data[S->size - 1]; 
}  
void pop(Stack* S){
	S->size--;
}  

int min(int a,int b){
	if(a<b) return a;
	else return b;
}
int idx;
int i = 0;
int on_stack[MAX];
int num[MAX];
int min_num[MAX];
Stack S;
void strong_connect(Graph *G,int x) {
	push(&S,x);
	num[x]=idx;
	min_num[x]=idx; idx++;
	on_stack[x]=1;
	List list=neighbors(G,x);	
	int j;
	for(j=1;j<=list.size;j++){
		int y=element_at(&list,j);
		if(num[y]==-1){
			strong_connect(G,y);
			min_num[x]=min(min_num[x],min_num[y]);
		} else if(on_stack[y])
			min_num[x]=min(min_num[x],num[y]);
	}
	if(num[x]==min_num[x]){
		i = i + 1;
		int w;
		do	{
			w=top(&S); 
			pop(&S);
			on_stack[w]=0;
		} while(w!=x);
	}
}

void strong(Graph *G) {
	int j;
	make_null_stack(&S);
	for(j=1; j<=G->n; j++) {
		on_stack[j]=0;
		num[j]=-1;
	}
	idx=1;
	for(j=1; j<=G->n; j++)
		if(num[j]==-1)
			strong_connect(G,j);
	printf("%d", i);
}
int main(){
	Graph G;
	int j,x,y,m,n;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(j=1;j<=m;j++) {
		scanf("%d%d",&x,&y);
		add_edge(&G,x,y);
	}
	strong(&G);
}

