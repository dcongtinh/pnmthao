// Bai toan nhan hai so nguyen lon
// Du lieu cho trong file D://CT174/thuc hanh/BigInteger.INP
// Giai bang phuong phap CHIA DE TRI
// Dung chuoi ky tu bieu dien cho mot so nguyen 
// moi so nguyen co n chu so, n co dang n = 2^k

// Noi dung file BigInteger.INP nhu sau
// Co 2 dong, moi dong bieu dien cho mot so nguyen, 
// ket thuc bang ky hieu xuong dong


#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef char * BigInteger;

void ReadFromFile(BigInteger x, BigInteger y)

int Sign(BigInteger x)

BigInteger Right(BigInteger x, int n)

BigInteger Left(BigInteger x, int n)
	

BigInteger ABS(BigInteger x)

BigInteger Nhan10_mu_n (BigInteger x, int n)

BigInteger Reverse(BigInteger n)          

int Zero(BigInteger n)  

int Positive(BigInteger n)

int Negative(BigInteger n)

int Not_Negative(BigInteger n)   


int Not_Positive(BigInteger n)   

// Ham xet xem 2 so co bang nhau hay kh
int Equal(BigInteger n, BigInteger m)
  
/*
 Ham xet xem so n co nho hon so m
 Ta xet cac truong hop sau
 0- neu n bang m   => Khong nho hon
 1- n am va m khong am => n<m
 2- n bang khong va m duong       => n<m
 3- n khong am va m am            => n>m
 4- n duong va m khong duong      => n>m
 5- n va m cung duong va do dai cua n nho hon m => n<m
 6- n va m cung khong am, cung do dai, xet tung ky tu cho den khi gap n[i]<m[i] thi n<m
 7- n va m cung am, thi n<m khi abs(m)<abs(n)
 
 */
 
  
 int Less_Than(BigInteger n, BigInteger m)                               


// Xet xem so n co lon hon so m hay khong
 
int Greater_Than(BigInteger n, BigInteger m)
    
int Less_Or_Equal(BigInteger n, BigInteger m)    

int Greater_Or_Equal(BigInteger n, BigInteger m)     

// Ham tru so nguyen x cho y voi gia thiet n1>=n2
// Ky tu = so + 48

BigInteger Subtract1(BigInteger x, BigInteger y)

// nhan mot so nguyen voi so 1 hoac -1
BigInteger MultS(BigInteger x, int s)

BigInteger Subtract(BigInteger x, BigInteger y)

// cong 2 so nguyen khong am
   
BigInteger Add1(BigInteger n1, BigInteger n2)

// Cong hai so bat ky

BigInteger Add(BigInteger n1, BigInteger n2)

// Cong 3 so nguyen

BigInteger Add3(BigInteger n1, BigInteger n2, BigInteger n3)
 
 
// Nhan 2 so nguyen co mot chu so 

BigInteger Mult1(BigInteger x, BigInteger y)

BigInteger Mult(BigInteger X, BigInteger Y, int n){
   BigInteger m1,m2,m3,A,B,C,D;
   int s; // Luu tru dau cua tich XY 
   s = Sign(X)*Sign(Y); 
   X = ABS(X); //Lay tri tuyet doi cua X 
   Y = ABS(Y);

   if (n == 1)  return MultS(Mult1(X,Y),s);
   
   A = Left(X, n/2);
   B = Right(X, n/2);
   C = Left(Y, n/2);
   D = Right(Y, n/2);
   m1 = Mult(A,C, n/2);
   m2 = Mult(Subtract(A,B),Subtract(D,C), n/2);
   m3 = Mult(B,D, n/2);
   
   return MultS(Add3(Nhan10_mu_n(m1,n),Nhan10_mu_n(Add3(m1,m2,m3),n/2), m3),s);
}


int main(){
    BigInteger x, y;
     x=(BigInteger)malloc(sizeof(char)*256);
	 y=(BigInteger)malloc(sizeof(char)*256);
	ReadFromFile(x,y);
	printf("\nSo nguyen X= %s\n\n",x);
	printf("So nguyen Y= %s\n\n",y);

	printf("Tong So X+Y= %s\n",Add(x,y));
	
	printf("Tich So XY= %s\n",Mult(x,y,strlen(ABS(x))));
	free(x);
	free(y);
	return 0;
}
