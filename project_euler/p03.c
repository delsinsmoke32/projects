#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define dim 1000000

bool primes[dim] = {false};
unsigned long number = 600851475143;

void atkinSieve(long LIMIT){
    primes[2] = true;
    primes[3] = true;

    for (int x = 1; x * x <= LIMIT; x++){
        for (int y = 1; y * y <= LIMIT; y++){
            int n = (4 * x * x) + (y * y);
            if (n <= LIMIT && (n % 12 == 1 || n % 12 == 5)){
                primes[n] = !primes[n];
            }

            n = (3 * x * x) + (y * y);
            if (n <= LIMIT && n % 12 == 7){
                primes[n] = !primes[n];
            }

            n = (3 * x * x) - (y * y);
            if (x > y && n <= LIMIT && n % 12 == 11){
                primes[n] = !primes[n];
            }
        }
    }

    //marca tutti i multipli di quadrati come non primi
    for (int i = 5; i * i <= LIMIT; i++){
        if (primes[i] == false) continue;
        for (int j = i * i; j <= LIMIT; j += i * i){
            primes[j] = false;
        }
    }

}


int main(void){
    long square_root = (long) sqrt(number);
    atkinSieve(square_root);
    bool prime_factors[dim] = {false};
    int largest = 0;
    if (number % 2 == 0){
        prime_factors[2] = true;
        largest = 2;
    } 

    for (int i = 3; i < dim; i += 2){
        if (primes[i]){
            if (number % i == 0){
                prime_factors[i] = true;
                largest = i;
            }
        }
    } 

    printf("%d\n", largest);

}