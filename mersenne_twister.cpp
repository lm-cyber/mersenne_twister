

#include <stdio.h>
#include <stdlib.h>

/* Параметры периода */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* постоянный вектор а */
#define UPPER_MASK 0x80000000UL /* старшие значащие биты w-r */
#define LOWER_MASK 0x7fffffffUL /* наименее значащие r биты */

static unsigned long mt[N]; /* массив для вектора состояния  */
static int mti=N+1; /* mti==N+1 означает, что mt[N] не инициализирован */

/* инициализирует mt[N] начальным числом */
extern "C" void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] =
                (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* В предыдущих версиях MSB начального числа влияют   */
        /* только старшие разряды массива mt[].                        */
        mt[mti] &= 0xffffffffUL;
        /* для > 32-битных машин */
    }
}

/* инициализировать массивом с длиной массива */
/* init_key — массив для инициализации ключей */
extern "C" void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
                + init_key[j] + j;
        mt[i] &= 0xffffffffUL; /* для WORDSIZE > 32 машин */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
                - i;
        mt[i] &= 0xffffffffUL; /* для WORDSIZE > 32 машин */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* старший бит равен 1; обеспечение ненулевого исходного массива*/
}

/* генерирует случайное число на интервале [0,0xffffffff] */
extern "C" unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* генерировать N слов за один раз */
        int kk;

        if (mti == N+1)   /* если init_genrand() не был вызван, */
            init_genrand(5489UL); /* используется начальное семя по умолчанию */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* генерирует случайное число на интервале [0,0x7ffffffff] */
extern "C" long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* генерирует случайное число на [0,1]-реальном интервале */
extern "C" double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0);
    /*2^32-1 */
}

/* генерирует случайное число на [0,1)-реальном интервале */
extern "C" double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0);
    /*  2^32 */
}

/* генерирует случайное число на (0,1)-реальном интервале */
extern "C" double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0);
    /*  2^32 */
}

/* генерирует случайное число на [0,1) с 53-битным разрешением*/
extern "C" double genrand_res53(void)
{
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6;
    return(a*67108864.0+b)*(1.0/9007199254740992.0);
}


int main(int argc, char *argv[]) {
    if (argc < 5) {
        return 1;
    }
    int i;
    unsigned long init[4] , length = 4;
    init[0] = strtoul(argv[1],NULL,10);
    init[1] = strtoul(argv[2],NULL,10);
    init[2] = strtoul(argv[3],NULL,10);
    init[3] = strtoul(argv[4],NULL,10);
    init_by_array(init, length);
    printf("1000 genrand_int32()\n");
    for (i = 0; i < 1000; i++) {
        printf("%10lu ", genrand_int32());
        if (i % 5 == 4) printf("\n");
    }
    printf("\n1000  genrand_real2()\n");
    for (i = 0; i < 1000; i++) {
        printf("%10.8f ", genrand_real2());
        if (i % 5 == 4) printf("\n");
    }
    return 0;
}
