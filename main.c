#include <stdio.h>
#include <math.h>
#include <string.h>

double computeSin(double x, double tol)
{
    double term=x;
    double sum=term;
    int i=1;

        while (fabs(term) > tol)
        {
            term=-term*x*x/((2*i)*(2*i+1));
            sum+=term;
            i++;
        }
    return sum;
}

double computeCos(double x, double tol)
{
    double term=1.0;
    double sum=term;
    int i=1;

    while (fabs(term)>tol)
    {
        term=-term*x*x/((2*i-1)*(2*i));
        sum+=term;
        i++;
    }
    return sum;
}

int main()
{
    int active=1;

    while (active)
    {
        char op[3];
        double num, tol;

        printf("Enter the trigonometric function\n");
        scanf("%s", op);

        if (strcmp(op, "none")==0)
            break;

        printf("Enter the input number\n");
        scanf("%lf", &num);
        printf("Enter the tolerance\n");
        scanf("%lf", &tol);

        if (strcmp(op, "sin") == 0)
            printf("%f\n", computeSin(num, tol));
        else if (strcmp(op, "cos")==0)
            printf("%f\n", computeCos(num, tol));
        else if (strcmp(op, "tan")==0)
        {
            double sinSum=computeSin(num,tol), cosSum=computeCos(num, tol);

            if (fabs(cosSum)<tol)
                printf("infinity\n");
            else
                printf("%f\n", sinSum/cosSum);
        }
    }
    return 0;
}
