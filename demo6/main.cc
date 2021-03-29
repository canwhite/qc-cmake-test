#include <stdio.h>
#include <stdlib.h>


// 改为选择引入
#ifdef HAVE_POW
    #include <math.h>
#else
    #include "math/MathFunctions.h"
#endif 


int main(int argc, char *argv[])
{
    if (argc < 3){
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);

    // double result = power(base, exponent);
    // 根据USE_MYMATH是否存在，算出不同的result
#ifdef HAVE_POW
    printf("Now we use the standard library. \n");
    double result = pow(base, exponent);
#else
    printf("Now we use our own Math library. \n");
    double result = power(base, exponent);

#endif


    printf("%g ^ %d is %g\n", base, exponent, result);
    return 0;
}