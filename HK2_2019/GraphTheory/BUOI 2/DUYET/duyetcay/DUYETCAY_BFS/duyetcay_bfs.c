#include<stdio.h>
/*Khai bao queue*/
#define MAX_ELEMENTS 100
typedef struct {
	int data[MAX_ELEMENTS];
	int front,rear;
}Queue;
void make_null_queue(Queue *Q){
	Q->front=0;
	Q->rear=-1;
}
void push(Queue *Q, int x){
	Q->rear++;
	Q->data[Q->rear]=x;  
}
int top (Queue *Q){
	return Q->data[Q->front];
}
void pop(Queue *Q){
	Q->front++;
}
int empty(Queue *Q){
	return Q->front > Q->rear;
}


#define MAX_VERTIES 100
#define MAX_VERTICES 100
typedef int ElementType;
typedef struct{
	ElementType data[MAX_ELEMENTS];
	int size;
}List;
/*Tao danh sach rong*/
void make_null(List *L){
	L->size=0;
}
// Them mot phan tu vao cuoi danh sach
void push_back(List *L,ElementType x){
	L->data[L->size]=x;
	L->size++;
}
//Lay phan tu voi vi tri i phan tu bat dau o vi tri 1
ElementType element_at(List *L,int i){
	return L->data[i-1];
}
//Tra ve so phan tu cua danh sach
int count_List(List *L){
	return L->size;
}
typedef struct{
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
}Graph;
/* khoi tao do thi G*/
void intit_graph(Graph *G,int n){
	int i,k;
	G->n=n;
	for(i=1;i<=n;i++)
		for(k=1;k<=n;k++)
			G->A[i][k]=0;
}
//them cung vao do thi
void add_edge(Graph *G,int x,int y){
	G->A[x][y]=1;
	G->A[y][x]=1;
}
//Xac ddinh x co ke y khong
int adjcent(Graph G,int x,int y){
	int e;
	for(e=1;e<=G.n;e++)
	if(G.A[x][y]==1&&G.A[y][x]==1) return 1;
	return 0;
}
//tinh bac
int degree(Graph *G,int x){
	int e,dem=0;
	for(e=1;e<=G->n;e++)
	if(G->A[x][e]==1) dem++;
	return dem;
}


List neighbors(Graph *G,int x){
	int y;
	List L;
	make_null(&L);
	for (y=1;y<=G->n;y++){
		if(adjcent(*G,x,y)) push_back(&L,y);
	}
	return L;
}

int mark[MAX_VERTICES];
int parent[MAX_VERTICES];
//Duyet do thi theo chieu rong
void breath_first_sreach(Graph *G, int k){
	Queue L;
	int j;
	make_null_queue(&L);
	push(&L,k);
	mark[k]=1;
	while(!empty(&L)){
		int x = top(&L);
		pop(&L);
		List List = neighbors(G,x);
		for(j=1;j<=List.size;j++){
			
			int y=element_at(&List,j);
			if(mark[y]==0){
				parent[y]=x;
				mark[y]=1;
				push(&L,y);
			}
		}
	}
}

void duyet(Graph *G){
	int i,j;
	for(j=1;j<=G->n;j++)
		{
			mark[j]=0;
			parent[j]=0;
		}
	breath_first_sreach(G, 1);
	for (i = 1; i <= G->n; i++ ){
		if (mark[i] == 0){
			breath_first_sreach(G,i);
		}
	}
}

int main(){
	Graph G;
	int n,m,e,u,v,i;
	freopen("dt.txt", "r", stdin); 
	scanf("%d%d",&n,&m);
	intit_graph(&G,n);
	for(e=1;e<=m;e++){
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	duyet(&G);
	for(i=1;i<=n;i++)
 	printf("%d %d\n",i,parent[i]);
}
