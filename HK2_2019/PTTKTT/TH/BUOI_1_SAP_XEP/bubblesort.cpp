#include <stdio.h>
/*Khai bao*/
typedef int keytype;
typedef float othertype;
typedef struct {
	keytype key;
	othertype otherfields;
} recordtype;
/*Doi cho*/
void Swap(recordtype &x, recordtype &y){
	recordtype temp;
	temp = x;
	x = y;
	y = temp;
}
void Bubblesort(recordtype a[],int n){
	int i,j;
	for(i=0; i<=n-2;i++)
			for(j= n-1;j>=i+1;j--)
				if(a[j].key< a[j-1].key) 
					Swap(a[j],a[j-1]);
}
int main(){
	int n,i;
	recordtype a[100];
	FILE* file = fopen("dayso.inp", "r");
	fscanf(file, "%d",&n);
	printf("Day truoc khi sap xep theo kieu Bubble_Sort bien the la:\n\n");
	for (i = 0; i <= n-1; i++){
		fscanf(file, "%d", &a[i]);
		printf("%d ",a[i]);
	}
	printf("\n");
	Bubblesort(a,n);
	printf("Day sau khi sap xep theo kieu Bubble_Sort la:\n\n");
	for(i=0; i<=n-1; i++)
		printf("%d ",a[i]);
}
