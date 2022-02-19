#include <stdio.h>
#include <math.h>

#define PI 3.1415926
double myCos(double x){
     x=fabs(x);
     //x = x -((int)(x/(2*PI))*PI);
    // x = x - (2*PI)*((int)(x/(2*PI)));
   // printf("%lf\n", x);
   
    double a[4] = {1, 0, -1, 0};
   
    int factorial = 1;
    double y = 0;
   
    int len = sizeof(a)/sizeof(double);
    int iterations = len*2;
    for(int j = 0; j < iterations; j++){
        for(int i = 1; i < len + 1; i++){
           
            y += a[(i-1)] * pow(x, len*j + (i-1)) / factorial;
            factorial *= len*j + i;
        }
    }
   
   
    return y;
}


int main()
{
    printf("%lf\n",myCos((PI/6)));

    return 0;
}
