//
// Created by void on 26.04.22.
//
#include "mt64.h"
#include "mt32.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 5) {
        return 1;
    }
    int i;
    unsigned long init[4] , length = 4;
    unsigned long long init64[4];
    mt19937_32 *mt32 = new mt19937_32;

    init64[0] = strtoll(argv[1],NULL,10);
    init64[0] = strtoll(argv[2],NULL,10);
    init64[0] = strtoll(argv[3],NULL,10);
    init64[0] = strtoll(argv[4],NULL,10);

    init[0] = strtoul(argv[1],NULL,10);
    init[1] = strtoul(argv[2],NULL,10);
    init[2] = strtoul(argv[3],NULL,10);
    init[3] = strtoul(argv[4],NULL,10);
    init_by_array(init, length,mt32);
    printf("1000 genrand_int32()\n");
    for (i = 0; i < 1000; i++) {
        printf("%lu ", genrand_int32(mt32));
        if (i % 5 == 4) printf("\n");
    }
    printf("\n1000  genrand_real2()\n");
    for (i = 0; i < 1000; i++) {
        printf("%10.8f ", genrand_real2(mt32));
        if (i % 5 == 4) printf("\n");
    }
    mt19937_64 *mt64 = new mt19937_64;
    init_genrand64(mt64,time(NULL));
    init_by_array64(mt64,init64,4);

    printf("1000 64\n");
    for (i = 0; i < 1000; i++) {
        printf("%10llu ", genrand64_int64(mt64) );
        if (i % 5 == 4) printf("\n");
    }
    printf("\n1000  double\n");
    for (i = 0; i < 1000; i++) {
        printf("%10.8lf ",genrand64_real1(mt64));
        if (i % 5 == 4) printf("\n");
    }
    return 0;
}
