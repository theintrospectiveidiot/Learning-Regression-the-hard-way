#include<stdio.h>

int signum(float a)
{
if(a >= 0)
	return 1;
else return 0;
}

void Perceptron_Trick(int* X,int y,float C[],float eta)
{
int i,j;
float z = C[2];

for(i=0;i<2;i++)
{
z += C[i]*X[i];
}

for(i=0;i<2;i++)
{
C[i] += (y - signum(z))*(X[i])*eta;
}
C[2] += (y - signum(z))*eta;

printf("z = %f\ty = %d\n",z,y);
}

int main()
{
int X[10][2] = {{2,2},{6,6},{7,8},{3,14},{5,4},{1,6},{16,3},{12,8},{18,14},{4,2}},Y[10] = {0,1,1,1,0,1,0,0,1,0};
float C[3] = {1.00f,1.00f,1.00f};
float eta = 0.001f;
int i,j;

for(i=0;i<1000;i++)
{
for(j=9;j>=0;j--){Perceptron_Trick(X[j],Y[j],C,eta);}
}

for(i=0;i<3;i++){printf("C[%d] = %f\n",i,C[i]);}

}
