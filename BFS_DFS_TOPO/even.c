#include <stdio.h>

int printEvenAndSum(int start, int end, int sum) {

    if (start > end) {
        return sum;
    }

    
    if (start % 2 == 0) {
        printf("%d ", start);

       
        sum += start;
    }

  
    printEvenAndSum(start + 1, end, sum);
}

int main() {
    int n, sum = 0;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    sum = printEvenAndSum(1, n, sum);

    printf("\nSum of even numbers from 1 to %d is: %d\n", n, sum);

    return 0;
}
