#include <stdio.h>
#define MAX 100
#define NO_EDGE 0
#define INF 9999999
typedef struct{
	int C[MAX][MAX];
	int F[MAX][MAX];
	int n;
}Graph;
typedef struct{
	int dir;
	int pre;
	int sigma;
}Label;
Label labels[MAX];
void init_graph(Graph *G,int n){
	G->n=n;
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			G->C[i][j]=0;
			G->F[i][j]=0;
		}
}
int min(int a, int b){
	return a<b ? a:b;
}
//--------------------------------------------
typedef struct {
	int data[MAX];
	int front, rear;
} Queue;
void make_null_queue(Queue* Q) {
	Q->front = 0;
	Q->rear = -1;
}
void enqueue(Queue* Q, int x) {
	Q->rear++;
	Q->data[Q->rear] = x;
}
int top(Queue* Q) {
	return Q->data[Q->front];
}
void dequeue(Queue* Q) {
	Q->front++;
}
int empty_queue(Queue* Q) {
	return Q->front > Q->rear;
}

int FordFullkerson(Graph *G, int s, int t){
	Queue Q;
	int u,v,sum_flow=0;
	do{
		//B1: gan nhan s
		//1.1 xoa tat ca cac nhan
		for(u=1;u<=G->n;u++)
			labels[u].dir=0;
		//1.2 gan nhan s: (+,s,oo)
		labels[s].dir=+1;
		labels[s].pre=s;
		labels[s].sigma=INF;
		//1.3 Khoi tao Q rong, dua s vao Q
		make_null_queue(&Q);
		enqueue(&Q,s);
		//B2,3
		int found=0;
		while(!empty_queue(&Q)){
			int x = top(&Q); dequeue(&Q);
			for(v=1;v<=G->n;v++){
				//xet gan nhan cho cac dinh ke cua x, cung thuan
				if(labels[v].dir==0 && G->C[x][v] != NO_EDGE && G->F[x][v] < G->C[x][v]){
					labels[v].dir=+1;
					labels[v].pre=x;
					labels[v].sigma=min(labels[x].sigma, G->C[x][v] - G->F[x][v]);
					enqueue(&Q,v);
				}
				//xet gan nhan cho cac dinh ke cua x, cung nghich
				if(labels[v].dir==0 && G->C[v][x] != NO_EDGE && G->F[v][x] > 0){ 
					labels[v].dir=-1;
					labels[v].pre=x;
					labels[v].sigma=min(labels[u].sigma, G->F[v][x]);
					enqueue(&Q,v);
				}
			}
			if(labels[t].dir!=0){
				found =1;
				break;
			}
		}
		if(found==1){
			// B 4,5,6 - tang luong
			int x =t;
			int sigma= labels[t].sigma;
			sum_flow +=sigma;
			while(x!=s){
				int u = labels[x].pre;
				if(labels[x].dir>0)//tang luong
					G->F[u][x]+=sigma;
				else //giam luong
					G->F[u][x]-=sigma;
				x=u;
			}
		}
		else break;
	} while(1);
	return sum_flow;
}
int main(){
	Graph G;
	int n,m,u,v,e,c;
	freopen("dt.txt","r",stdin);
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e=0;e<m;e++){
		scanf("%d%d%d",&u,&v,&c);
		G.C[u][v]=c;
	}
	int max_flow=FordFullkerson(&G,1,n);
	printf("Max flow: %d\n",max_flow);
	printf("X0: ");
	for(u=1 ;u<=n;u++)
		if(labels[u].dir!=0) printf("%d ",u);
	printf("\n");
	printf("Y0: ");
	for(u=1;u<=n;u++)
		if(labels[u].dir==0) printf("%d ",u);
}


