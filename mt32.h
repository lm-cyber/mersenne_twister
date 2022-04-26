#ifndef MERSENNE_TWISTER_MT32_H
#define MERSENNE_TWISTER_MT32_H
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* постоянный вектор а */
#define UPPER_MASK 0x80000000UL /* старшие значащие биты w-r */
#define LOWER_MASK 0x7fffffffUL /* наименее значащие r биты */
#include "stdlib.h"
struct mt19937_32 {
    unsigned long mt[N];
    size_t mti=N;
};
void init_genrand(unsigned long seed, mt19937_32 *mt32);
void init_by_array(unsigned long init_key[], int key_length,mt19937_32 *mt32);
unsigned long genrand_int32(mt19937_32 *mt34);
long genrand_int31(mt19937_32 *mt34);
double genrand_real1(mt19937_32 *mt34);
double genrand_real2(mt19937_32 *mt34);
double genrand_real3(mt19937_32 *mt34);
double genrand_res53(mt19937_32 *mt34);
#endif