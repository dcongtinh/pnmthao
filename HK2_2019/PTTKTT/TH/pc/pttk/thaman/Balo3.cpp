#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct {
	float tl,gt;
	int pa;
	char tendv[20];
}dv;
dv* docfile(float *w, int *n){
	FILE *f;
	f=fopen("CaiBalo3.INP","r");
	fscanf(f,"%f",w);
	dv* dsdv;
	dsdv=(dv*)malloc(sizeof(dv));
	int i=0;
	while(!feof(f)){
		fscanf(f,"%f%f",&dsdv[i].tl,&dsdv[i].gt);
		fgets(dsdv[i].tendv, 20, f);
		dsdv[i].tendv[strlen(dsdv[i].tendv)-1]='\0';
		dsdv[i].pa=0;
		i++;
		dsdv=(dv*)realloc(dsdv,sizeof(dv)*(i+1));
	}
	*n=i;
	fclose(f);
	return dsdv;
}
void swap(dv *a, dv* b){
	dv tam;
	tam=*a;
	*a=*b;
	*b=tam;
}
void noibot(dv *dsdv, int n){
	int i,j;
	for(i=0; i<=n-2; i++)
		for(j=n-1; j>=i+1; j--){
			float dgj=dsdv[j].gt/dsdv[j].tl;
			float dgj_1=dsdv[j-1].gt/dsdv[j-1].tl;
			if(dgj>dgj_1)
				swap(&dsdv[j], &dsdv[j-1]);
		}
}
void in(dv * dsdv, int n, float w){
	int i;
	float tonggt=0.0, tongtl=0.0;
	printf("|---|--------------------|---------|---------|---------|---------|\n");
	printf("|%-3s|%-20s|%-9s|%-9s|%-9s|%-9s|\n","STT","TenDV","TLuong","GiaTri","DonGia","PAn");
	printf("|---|--------------------|---------|---------|---------|---------|\n");
	for(i=0;i<n;i++){
		printf("|%-3d",i+1);
		printf("|%-20s",dsdv[i].tendv);
		printf("|%-9.1f",dsdv[i].tl);
		printf("|%-9.1f",dsdv[i].gt);
		printf("|%-9.1f",dsdv[i].gt/dsdv[i].tl);
		printf("|%-9d|\n",dsdv[i].pa);
		tonggt=tonggt+dsdv[i].pa*dsdv[i].gt;
		tongtl=tongtl+dsdv[i].pa*dsdv[i].tl;
	}
	printf("|---|--------------------|---------|---------|---------|---------|\n");
	printf("Tong trong luong cua ba lo= %9.1f\n",w);
	printf("Tong trong luong cac vat duoc chon= %9.1f\n",tongtl);
	printf("Tong gia tri= %9.1f\n",tonggt);
}
void thaman(dv*dsdv, int n, float w){
	int i;
	for(i=0;i<n;i++){
		dsdv[i].pa=w/dsdv[i].tl;
		if(dsdv[i].pa>1) dsdv[i].pa=1;
		w= w - dsdv[i].pa * dsdv[i].tl;
	}
}

int main(){
	int n;
	float w;
	dv* dsdv;
	dsdv=docfile(&w, &n);
    noibot(dsdv,n);
	thaman(dsdv,n,w);
	in(dsdv,n,w);
	free(dsdv);
}
	
