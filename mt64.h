//
// Created by void on 26.04.22.
//

#ifndef MERSENNE_TWISTER_MT64_H
#define MERSENNE_TWISTER_MT64_H
#include <stdio.h>
#define NN 312
#define MM 156
#define MATRIX_A 0xB5026F5AA96619E9ULL
#define UM 0xFFFFFFFF80000000ULL /* Старшие значащие 33 бита */
#define LM 0x7FFFFFFFULL /* Младший значащий 31 биты */

struct mt19937_64 {
    unsigned long long mt[NN];
    size_t mti;
};
void init_genrand64(struct mt19937_64* context, unsigned long long seed);
void init_by_array64(struct mt19937_64* context, unsigned long long init_key[], unsigned long long key_length);
unsigned long long genrand64_int64(struct mt19937_64* context);
long long genrand64_int63(struct mt19937_64* context);
double genrand64_real1(struct mt19937_64* context);
double genrand64_real2(struct mt19937_64* context);
double genrand64_real3(struct mt19937_64* context);
#endif //MERSENNE_TWISTER_MT64_H
