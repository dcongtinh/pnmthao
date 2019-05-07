#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
	int pa, tl, gt;
	char tendv[20];
}dv;
typedef int bang[50][100];
dv * docfile(int *w, int *n){
	FILE *f=fopen("balo1qhd.inp","r");
	fscanf(f,"%d",&w);
	printf("%d",w);
	/*dv *dsdv;
	dsdv=(dv*)malloc(sizeof(dv));
	int i=0;
	while(!feof(f)){
		fscanf(f,"%d%d",&dsdv[i].tl, &dsdv[i].gt);
		fgets(dsdv[i].tendv,20,f);
		dsdv[i].tendv[strlen(dsdv[i].tendv)-1]='\0';
		dsdv[i].pa=0;
		i++;
		dsdv=(dv*)realloc(dsdv,sizeof(dv)*(i+1));
	}
	*n=i;*/
	fclose(f);
	return dsdv;
}
void swap(dv *a, dv *b){
	dv tam;
	tam=*a;
	*a=*b;
	*b=tam;
}

void in(dv *dsdv, int w, int n){
	int i, tonggt=0, tongtl=0;
	printf("|---|--------------------|---------|---------|---------|---------|\n");
	printf("|%-3s|%-20s|%-9s|%-9s|%-9s|%-9s|\n","stt","tendv","tluong","gtri","p.an");
	printf("|---|--------------------|---------|---------|---------|---------|\n");
	for(i=0;i<n;i++){
		printf("|%-3d",i+1);
		printf("|%-20s",dsdv[i].tendv);
		printf("|%-9d",dsdv[i].tl);
		printf("|%-9d",dsdv[i].gt);
		printf("|%-9f",(float)dsdv[i].gt/dsdv[i].tl);
		printf("|%-9d",dsdv[i].pa);
		tonggt=tonggt+dsdv[i].pa+dsdv[i].gt;
		tongtl=tongtl+dsdv[i].pa+dsdv[i].tl;
	}
	printf("|---|--------------------|---------|---------|---------|---------|\n");
	printf("trong luong= %-9d\n",w);
	printf("tong trong luong= %-9d, tong gia tri=%-9d",tongtl, tonggt);
}
void taobang(dv *dsdv, int n, int w, bang f, bang x){
	int k, v;
	int xk, yk, fmax, xmax;
	for(v=0;v<=w;v++){
		x[0][v]=v/dsdv[0].tl;
		f[0][v]=x[0][v]*dsdv[0].gt;
	}
	for(k=1;k<n;k++)
		for(v=0;v<=w;v++){
			fmax=f[k-1][v];
			xmax=0;
			yk=v/dsdv[k].tl;
			for(xk=1;xk<=yk;xk++){
				if(f[k-1][v-xk*dsdv[k].tl]+xk*dsdv[k].gt>fmax){
					fmax=f[k-1][v-xk*dsdv[k].tl]+xk*dsdv[k].gt;
					xmax=xk;
				}
			}
			f[k][v]=fmax;
			x[k][v]=xmax;
		}
	}
void trabang(dv *dsdv, int n, int w, bang x){
	int k, v;
	v=w;
	for(k=n-1;k>=0;k--){
		dsdv[k].pa=x[k][v];
		v=v-x[k][v]*dsdv[k].tl;
	}
}
void inbang( int n, int w, bang x, bang f){
	int k,v;
	for(k=0;k<n;k++){
		for(v=0;v<=w;v++)
			printf("%4d%2d",f[k][v],x[k][v]);
		printf("\n");
	}
}
int main(){
	int n, w;
	bang x,f;
	dv *dsdv;
	dsdv=docfile(&w, &n);
	/*taobang(dsdv,n,w,f,x);
	inbang(n,w,x,f);
	trabang(dsdv,n,w,x);
	in(dsdv,n,w);
	free(dsdv);*/
}





