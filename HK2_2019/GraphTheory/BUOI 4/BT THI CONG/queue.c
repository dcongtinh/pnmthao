#include <stdio.h>
#include <conio.h>
#define MAX_ELEMENTS 100 

typedef int datatype;
typedef struct {  
	datatype data[MAX_ELEMENTS];  
	int front, rear; 
} Queue;  

void make_null_queue(Queue* Q) { 
	Q->front = 0;  Q->rear = -1; 
}  
int Empty(Queue Q)
{	
		return (Q.front ==-1);
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

int empty(Queue* Q) { 
	return Q->front > Q->rear; 
} 
datatype Front(Queue Q){
 	if (Empty(Q))       
	 	printf ("Hang rong");
    else  
       return Q.data[Q.front];
} 
void DeQueue(Queue *Q){	
	if (!Empty(*Q)){	
		Q->front=Q->front+1;
	   	if (Q->front>Q->rear)              				
		   make_null_queue(Q); //Dat lai hang rong
	}else printf("Loi: Hang rong!");
} 
