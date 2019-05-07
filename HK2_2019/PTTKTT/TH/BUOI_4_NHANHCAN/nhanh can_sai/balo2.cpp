#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
	char tendv[20];
	float tl, gt;
	int pa,sl;
}dv;
dv*dsdv;
//nhanh can
#define max 100
int n;
int x[max];
float w;
float tgt;
float tlconlai;
float ct;
float gialntt;

dv* docfile(float *w, int *n){
	FILE *f;
	f=fopen("CaiBalo2.INP","r");
	fscanf(f,"%f",w);
	dv *dsdv;
	dsdv=(dv*)malloc(sizeof(dv));
	int i=0;
	while(!feof(f)){
		fscanf(f,"%f%f%d",&dsdv[i].tl,&dsdv[i].gt,&dsdv[i].sl);
		fgets(dsdv[i].tendv,20,f);
		dsdv[i].tendv[strlen(dsdv[i].tendv)-1]='\0';
		dsdv[i].pa=0;
		i++;
		dsdv=(dv*)realloc(dsdv,sizeof(dv)*(i+1));
	}
	*n=i;
	fclose(f);
	return dsdv;
}

void swap(dv *a, dv *b){
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
				swap(&dsdv[j],&dsdv[j-1]);
		}
}
void in(dv* dsdv, int n, float w){
	float tonggt=0.0, tongtl=0.0;
	printf("|---|--------------------|---------|---------|---------|---------|---------|\n");
	printf("|%-3s|%-20s|%-9s|%-9s|%-9s|%-9s|\n","stt","ten","tluong","giatri","sluong","dongia","p.an");
	printf("|---|--------------------|---------|---------|---------|---------|---------|\n");
	for(int i=0; i<n; i++){
		printf("|%-3d",i+1);
		printf("|%-20s",dsdv[i].tendv);
		printf("|%-9.1f",dsdv[i].tl);
		printf("|%-9.1f",dsdv[i].gt);
		printf("|%-9d",dsdv[i].sl);
		printf("|%-9.1f",dsdv[i].gt/dsdv[i].tl);
		printf("|%-9d|\n",dsdv[i].pa);
		tonggt=tonggt+dsdv[i].pa*dsdv[i].gt;
		tongtl=tongtl+dsdv[i].pa*dsdv[i].tl;
	}
	printf("|---|--------------------|---------|---------|---------|---------|---------|\n");
	printf("Trong luong ba lo= %9.1f\n",w);
	printf("Tong gia tri= %9.1f, Tong trong luong= %9.1f",tonggt,tongtl);
	
}	


void init(){
	tlconlai=w;
	ct=tlconlai*dsdv[0].gt/dsdv[0].tl;
	gialntt=0.0;
	tgt=0.0;
}
void ghinhankyluc(){
	int i;
	if(gialntt<tgt){
		gialntt=tgt;
		for(i=0;i<n;i++) 
			dsdv[i].pa=x[i];
	}
}
float min(float a, float b){
	if(a>b) return b;
	else return a;
}
void nhanhcan(int i){
	int j;
	for(j=min(dsdv[i].sl, tlconlai/dsdv[i].tl) ; j>=0; j--){
		tgt=tgt+j*dsdv[i].gt;
		tlconlai=tlconlai-j*dsdv[i].tl;
		ct=tgt+tlconlai*dsdv[i+1].gt/dsdv[i+1].tl;
		if(ct>gialntt){
			x[i]=j;
			if((i==n-1)||(tlconlai==0)) ghinhankyluc();
			else nhanhcan(i+1);
		}
	}
	x[i]=0;
	tgt=tgt-j*dsdv[i].gt;
	tlconlai=tlconlai+j*dsdv[i].tl;
}
int main(){
	dsdv=docfile(&w,&n);
	noibot(dsdv,n);
	init();
	nhanhcan(0);
	in(dsdv,n,w);
	free(dsdv);
	return 0;
}



