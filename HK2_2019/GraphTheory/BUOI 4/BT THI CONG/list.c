#include <stdio.h>
#define MAX_ELEMENTS 100

typedef int Position;
typedef int ElementType;
typedef struct {
	ElementType data[MAX_ELEMENTS];
	Position size;
} List;

void make_null(List* L) {
	L->size = 0;
}

Position EndList(List L){
	return L.size+1;
}

void insert_list(ElementType x, Position p, List* L){
	if (L->size == 500)
		printf("full");
	else if ( (p<1) || (p>EndList(*L)))
		printf("Position la tro");
	else{
		Position q;
		for(q=EndList(*L)-1+1; q>p-1; q--)
			L->data[q] = L->data[q-1];
		L->data[p-1] = x;
		L->size++;
	}
}


void push_back(List* L, ElementType x) {
	L->data[L->size] = x;
	L->size++;
}

ElementType element_at(List* L, int i) {
	return L->data[i-1];
}

int count_list(List* L) {
	return L->size;
}

void copy(List* S1, List* S2){
	make_null(S1);
	*S1 = *S2;
}
