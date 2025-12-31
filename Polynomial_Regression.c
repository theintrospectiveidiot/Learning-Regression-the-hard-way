#include<stdio.h>
#include<math.h>

void Disguised_Linear_Regression(float C[],float y,float x,float eta,int degree,int lambda)
{
int i;
float z=0;

for(i=0;i<=degree;i++)
{
z += C[i]*powf(x,i);
}
for(i=0;i<=degree;i++)
{
C[i] = C[i] + eta*((y - z)*(powf(x,i)) - lambda*C[i]);
}
printf("y = %f\tz = %f\n",y,z);
}

int main()
{
int degree = 4,i,j;
FILE* g;

g = popen("gnuplot -persist","w");

fprintf(g,"set title 'Polynomial Regression'\n");
fprintf(g,"set xlabel 'X'\n");
fprintf(g,"set ylabel 'Y'\n");
fprintf(g,"set key off\n");

float I[100];
float O[100];

for(i=0;i<10;i++)
{
I[i] = i;
O[i] = powf(I[i],4) + powf(-1,i);
}

//for(i=0;i<100;i++){fprintf(g,"%f %f\n",I[i],O[i]);}

float C[degree+1];

for(i=0;i<=degree;i++)
{
C[i] = 0.0f;
}

float eta = 0.00000001f,rmse,z=0,lambda = 0.01f;

for(i=0;i<1000;i++)
{
 for(j=9;j>=0;j--)
 {
 Disguised_Linear_Regression(C,O[j],I[j],eta,degree,lambda);
 }
}

fprintf(g,"plot (%f*x**2)+(%f*x)+%f with lines\n",C[2],C[1],C[0]);

pclose(g);
for(i=0;i<=degree;i++){printf("C[%d] = %f\n",i,C[i]);}
}
