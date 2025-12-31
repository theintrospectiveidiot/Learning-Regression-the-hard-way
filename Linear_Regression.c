#include<stdio.h>
#include<math.h>

void Square_Trick(float* m,float* c,float* z,float* rmse,float y,float eta,float x)
{
*z = *m*(x) + *c;
*m = *m + eta*(y - *z)*x;
*c = *c + eta*(y - *z);
}

int main()
{
float f[6] = {1,2,3,5,6,7};
float l1[6] = {155,197,244,356,407,448};
float l2[6];

float m=0,c=0,eta=0.01,rmse=0,z=0;
FILE *g;
FILE *h;
FILE *p;
p = popen("gnuplot -persist","w");
h = popen("gnuplot -persist","w");
g = popen("gnuplot -persist","w");
int i,j,k;

for(i=0;i<6;i++){fprintf(p,"%f %f\n",f[i],l1[i]);}

fprintf(g,"set title 'RMSE vs Iterations'\n");
fprintf(g,"set xlabel 'No. of Iterations'\n");
fprintf(g,"set ylabel 'RMSE'\n");
fprintf(g,"plot '-' with linespoints title 'Error'\n");


fprintf(h,"set title 'Linear Regression'\n");
fprintf(h,"set xlabel 'No. of Rooms'\n");
fprintf(h,"set ylabel 'Predicted Price'\n");
fprintf(h,"set key off\n");
fprintf(h,"plot (%f*x)+%f with line linewidth 4\n",m,c);

for(i=0;i<1000;i++)
{
 fprintf(h,"replot (%f*x)+%f with line linewidth 4\n",m,c);
 for(j=5;j>=0;j--){Square_Trick(&m,&c,&z,&rmse,l1[j],eta,f[j]);
                   rmse += (l1[j]-z)*(l1[j]-z);}
 fprintf(g,"%d %f\n",i,sqrtf(rmse/6));
 rmse = 0;
}

fprintf(g,"e\n");
pclose(g);
fprintf(h,"e\n");
pclose(h);
//fprintf(p,"e\n");
pclose(p);
printf("m (weight) = %f\tc (bias) = %f\t%f\nPredicted output for x = 4: %f\n",m,c,sqrtf(rmse/6),(m*4)+c);
}
