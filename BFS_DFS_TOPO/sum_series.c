#include <stdio.h>
#include <math.h>

int fact(int n)
{
    if (n == 0 || n == 1)
        return 1;

    return n * fact(n - 1);
}

 double sum_of_series(int x, int n)
{
    if (n == 0)
        return 1.0;

    return pow(x, 2.0 * n) / fact(n) + sum_of_series(x, n - 1);
}

int main()
{
    int x, n;
    printf("x= ");
    scanf("%d", &x);
    printf("n= ");
    scanf("%d", &n);

    long double ans = sum_of_series(x, n);

    printf("%.3Lf", ans);

    return 0;
}
