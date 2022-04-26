#ifndef MERSENNE_TWISTER_MT32_H
#define MERSENNE_TWISTER_MT32_H
extern "C" void init_genrand(unsigned long s);
extern "C" void init_by_array(unsigned long init_key[], int key_length);
extern "C" unsigned long genrand_int32(void);
extern "C" long genrand_int31(void);
extern "C" double genrand_real1(void);
extern "C" double genrand_real2(void);
extern "C" double genrand_real3(void);
extern "C" double genrand_res53(void);
#endif