#include <stdio.h>
#include <conio.h>
#define MAX_VERTICES 100
typedef struct {
	int n; /* n: so dinh */
	/* ma tran dinh – dinh */
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

/* Khoi tao do thi G co n dinh */
void init_graph(Graph* G, int n) {
	int i, j;
	G->n = n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			G->A[i][j] = 0;
}

/* Them cung e = (x, y) vao do thi G */
void add_edge(Graph* G, int x, int y) {
	G->A[x][y]	+=	1; 
}

/* Kiem tra y co ke voi x khong */
	int adjacent(Graph* G, int x, int y) {
	return G->A[x][y] != 0;
}

/* Tinh bac cua dinh x: deg(x) don cung */
int degree(Graph* G, int x) {
	int y, deg = 0;
	for (y = 1; y <= G->n; y++)
		if (G->A[x][y] > 0)
			deg++;
	return deg;
} 

/* Tinh bac cua dinh x: deg(x), truong hop da cung */
//int degree(Graph* G, int x) {
//	int y, deg = 0;
//	for (y = 1; y <= G->n; y++)
////		if (adjacent(G, x ,y))
//		deg += G->A[x][y];
//	return deg;
//}

