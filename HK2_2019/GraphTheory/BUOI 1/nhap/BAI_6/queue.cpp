#include <stdio.h>
#include <conio.h>
#define MAX_VERTEXES 100
#define MAX_EDGES 500
#define NO_EDGE 0 //hoac gia tri dac biet nao do
typedef struct {
	int n,m;
	int A[MAX_VERTEXES][MAX_EDGES];
} Graph;
#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct {
    ElementType data[MAX_ELEMENTS];
    int size;
} List;
/* Tao danh sach rong */
void make_null_list(List* L) {
    L->size = 0;
}
/* Them mot phan tu vao cuoi danh sach */
void push_back(List* L, ElementType x) {
    L->data[L->size] = x;
    L->size++;
}
/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1 */
ElementType element_at(List* L, int i) {
    return L->data[i-1];
}
/* Tra ve so phan tu cua danh sach */
int count_list(List* L) {
    return L->size;
}
/* Khoi tao do thi G co n dinh */
void init_graph(Graph *G, int n, int m){
	int i,j;
	G->n=n;
	G->m=m;
	for(i=1; i<=n;i++)
		for(j=1; j<=m; j++)
		  G->A[i][j]=0;
}
// Them cung e=(x,y) vao do thi G
void add_edge(Graph *G, int e, int x, int y){
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
/* Tim cac dinh ke cua dinh x */
List neighbors(Graph* G, int x) {
	int y;
	List list;
	make_null_list(&list);
	for (y = 1; y <= G->n; y++)
		if(adjacent(G, x, y))
			push_back(&list, y);
	return list;
}
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
	Q->data[Q->rear]==x;
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
