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
/*Tim chot*/
int FindPivot(recordtype a[],int i, int j){
	keytype firstkey;
	int k;
	k=i+1;
	firstkey=a[i].key;
	while((k<=j)&&(a[k].key==firstkey))	k++;
	if(k>j) return -1;
	if(a[k].key<firstkey) return k;
	return i;
}
/*Phan hoach*/
int Partition(recordtype a[],int i, int j, keytype pivot){
	int L,R;
	L=i;
	R=j;
	while(L<=R){
		while (a[L].key<=pivot) L++;
		while (a[R].key>pivot) R--;
		if(L<R) Swap(a[L],a[R]);
	}
	return L;
}
/*QuickSort_Bienthe*/
void QuickSort(recordtype a[], int i, int j){
	keytype pivot;
	int pivotindex, k;
	pivotindex = FindPivot(a,i,j); // vi tri chot
	if(pivotindex != -1){
		pivot = a[pivotindex].key;
		k=Partition(a,i,j,pivot); // diem phan hoach
		QuickSort(a,i,k-1); //Mang trai
		QuickSort(a,k,j); // Mang phai
	}
}
int main(){
	int n,i;
	recordtype a[100];
	FILE* file = fopen("dayso.inp", "r");
	fscanf(file, "%d",&n);
	printf("Day truoc khi sap xep theo kieu Quick_Sort bien the la:\n\n");
	for (i = 0; i <= n-1; i++){
		fscanf(file, "%d", &a[i]);
		printf("%d ",a[i]);
	}
	printf("\n");
	QuickSort(a,0,n-1);
	printf("Day sau khi sap xep theo kieu Quick_Sort bien the la:\n\n");
	for(i=0; i<=n-1; i++)
		printf("%d ",a[i]);
}
