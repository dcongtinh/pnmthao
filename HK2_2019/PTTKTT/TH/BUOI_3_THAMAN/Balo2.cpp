#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
	char TenDV[20];
	float TL, GT;
	int PA, SL;
}DoVat;
 DoVat* ReadFromFile (float *w, int *n){
 	FILE *f;
 	f=fopen("CaiBalo2.INP","r");
 	fscanf(f,"%f",w);
 	DoVat * dsdv;
 	dsdv=(DoVat*)malloc(sizeof(DoVat));
 	int i=0;
 	while(!feof(f)){
 			fscanf(f,"%f%f%d",&dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL);
 			fgets(dsdv[i].TenDV,20,f);
 			dsdv[i].TenDV[strlen(dsdv[i].TenDV)-1]='\0';
 			dsdv[i].PA=0;
 			i++;
 			dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
 	}
  	*n=i;
 	fclose(f);
	return dsdv;
}
 void swap(DoVat *x, DoVat *y){
  	DoVat tam;
  	tam=*x;
  	*x=*y;
  	*y=tam;
}
void noibot(DoVat *dsdv, int n){
	int i,j;
	for(i=0; i<=n-2; i++)
		for(j=n-1; j>=i+1; j--){
			float DGJ= dsdv[j].GT/dsdv[j].TL;
			float DGJ_1= dsdv[j-1].GT/dsdv[j-1].TL;
			if(DGJ>DGJ_1)
				swap(&dsdv[j], &dsdv[j-1]);
		}
}
void InDSDV(DoVat *dsdv, int n, float w){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("|---|--------------------|---------|---------|---------|---------|---------|\n");
	printf("|%-3s|%-20s|%-9s|%-9s|%-9s|%-9s|%-9s|\n", "STT", "Ten Do Vat","T. Luong", "Gia Tri","So Luong", "Don Gia", "P. An");
	printf("|---|--------------------|---------|---------|---------|---------|---------|\n");
	for(i=0; i<n; i++){
		//if(dsdv[i].PA>0){
			printf("|%-3d",i+1);
			printf("|%-20s",dsdv[i].TenDV);
			printf("|%-9.1f",dsdv[i].TL);
			printf("|%-9.1f",dsdv[i].GT);
			printf("|%-9d",dsdv[i].SL);
			printf("|%-9.1f",dsdv[i].GT/dsdv[i].TL);
			printf("|%-9d|\n",dsdv[i].PA);
			TongTL=TongTL+dsdv[i].PA * dsdv[i].TL;
			TongGT=TongGT+dsdv[i].PA * dsdv[i].GT;
		}
	
	printf("|---|--------------------|---------|---------|---------|---------|\n");	
	printf("Trong luong cua ba lo= %9.1f\n",w);
	printf("Tong trong luong cac vat duoc chon= %9.1f, Tong gia tri= %9.1f\n", TongTL, TongGT);
}
void Greedy(DoVat*dsdv, int n, float W){
	int i;
	for(i=0;i<n;i++){
		dsdv[i].PA=W/dsdv[i].TL;
		if(dsdv[i].PA>dsdv[i].SL) dsdv[i].PA=dsdv[i].SL;
		W= W - dsdv[i].PA * dsdv[i].TL;
	}
}

int main(){
	int n;
	float W;
	DoVat *dsdv;
	dsdv=ReadFromFile(&W, &n);
    noibot(dsdv,n);
	Greedy(dsdv,n,W);
	InDSDV(dsdv,n,W);
	free(dsdv);
}