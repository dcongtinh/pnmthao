#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAX 100
typedef struct {
	char TenDV[20];
	float TL, GT;
	int PA,SL;
} DoVat;

DoVat * dsdv; 
int n; 
int x[MAX]; 
float W; 
float CT; 
float TGT; 
float GiaLNTT; 
float TLConLai; 

DoVat * ReadFromFile(float *W, int *n){
	FILE *f;
	f=fopen("CaiBalo2.INP", "r");
	fscanf(f, "%f", W); 
	DoVat *dsdv;
	dsdv=(DoVat*)malloc(sizeof(DoVat));
	int i=0;
	while (!feof(f)){
		fscanf(f, "%f%f%d",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].SL);
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
	DoVat Temp;
	Temp = *x;
	*x = *y;
	*y = Temp;
}

void BubbleSort(DoVat *dsdv, int n){
	int i,j;
	for(i=0; i<=n-2; i++)
		for (j=n-1; j>=i+1; j--){
			float DGJ = dsdv[j].GT/dsdv[j].TL;
			float DGJ_1 = dsdv[j-1].GT/dsdv[j-1].TL;
			if (DGJ > DGJ_1)
				swap(&dsdv[j],&dsdv[j-1]);
		}
}

void InDSDV(DoVat *dsdv ,int n, float W){
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	printf("|---|--------------------|---------|---------|---------|---------|---------|\n");
	printf("|%-3s|%-20s|%-9s|%-9s|%-9s|%-9s|%-9s|\n", "STT", " Ten Do Vat","T.Luong", "Gia Tri" ,"So Luong", "Don Gia", "P. An");
	printf("|---|--------------------|---------|---------|---------|---------|---------|\n");
	for(i=0;i<n;i++){
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
	printf("|---|--------------------|---------|---------|---------|---------|---------|\n");
	printf("Trong luong cua ba lo= %9.1f\n",W);
	printf("Tong trong luong= %9.1f, Tong gia tri= %9.1f\n", TongTL,TongGT);
}

void init(){
	TLConLai = W;
	CT = TLConLai*dsdv[0].GT/dsdv[0].TL; 
	GiaLNTT = 0.0;
	TGT = 0.0;
} 


void GhiNhanKyLuc(){
	int i;
	if(GiaLNTT < TGT){
		GiaLNTT = TGT;
		for(i=0;i<n;i++)
			dsdv[i].PA=x[i];
	}
}

void Try(int i){
	int j; 
	for(j = ((TLConLai/dsdv[i].TL) > dsdv[i].SL) ? dsdv[i].SL : (TLConLai/dsdv[i].TL); j>=0; j--){
		TGT = TGT + j*dsdv[i].GT;
		TLConLai = TLConLai - j*dsdv[i].TL;
		CT = TGT + TLConLai*dsdv[i+1].GT/dsdv[i+1].TL;
		if(CT>GiaLNTT){ 
			x[i]=j;
			if((i==n-1)||(TLConLai==0)) 
				GhiNhanKyLuc();
			else
				Try(i+1); 
		}
		
		x[i] = 0;
		TGT = TGT - j*dsdv[i].GT;
		TLConLai = TLConLai + j*dsdv[i].TL;
	}
}

int main(){
	dsdv = ReadFromFile(&W, &n);
	BubbleSort(dsdv,n);
	init();
	Try(0);
	InDSDV(dsdv,n,W);
	free(dsdv);

}
