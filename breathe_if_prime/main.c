#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>


#define LIMIT 80000001

bool primes[LIMIT] = {false};


void *atkinSieve(){
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
    pthread_t t1;
    pthread_create(&t1, NULL, atkinSieve, NULL);
    sleep(1);
    pthread_join(t1, NULL);
    printf("\33[?25l");
    for (int i = 0; i < 1000; i++){
        if (primes[i]){
            printf("%d è un numero PRIMO!!!!                     \r", i);
            fflush(stdout);
        }
        else{
            printf("%d non è primo.                              \r", i);
            fflush(stdout);
        }
        sleep(1);
    }
    printf("\n");
    printf("\33[?25h");
    return 0;
}