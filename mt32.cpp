


/* Параметры периода */

#include "mt32.h"
//static unsigned long mt[N]; /* массив для вектора состояния  */
//static int mti=N+1; /* mti==N+1 означает, что mt[N] не инициализирован */

/* инициализирует mt[N] начальным числом */
void init_genrand(unsigned long seed, mt19937_32 *mt32 )
{
    mt32->mt[0]= seed & 0xffffffffUL;
    for (mt32->mti=1; mt32->mti<N; mt32->mti++) {
        mt32->mt[mt32->mti] =
                (1812433253UL * (mt32->mt[mt32->mti-1] ^ (mt32->mt[mt32->mti-1] >> 30)) + mt32->mti);
        /* В предыдущих версиях MSB начального числа влияют   */
        /* только старшие разряды массива mt[].                        */
        mt32->mt[mt32->mti] &= 0xffffffffUL;
        /* для > 32-битных машин */
    }
}

/* инициализировать массивом с длиной массива */
/* init_key — массив для инициализации ключей */
void init_by_array(unsigned long init_key[], int key_length,mt19937_32 *mt32)
{
    int i, j, k;
    init_genrand(19650218UL,mt32);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt32->mt[i] = (mt32->mt[i] ^ ((mt32->mt[i-1] ^ (mt32->mt[i-1] >> 30)) * 1664525UL))
                + init_key[j] + j;
        mt32->mt[i] &= 0xffffffffUL; /* для WORDSIZE > 32 машин */
        i++; j++;
        if (i>=N) { mt32->mt[0] = mt32->mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt32->mt[i] = (mt32->mt[i] ^ ((mt32->mt[i-1] ^ (mt32->mt[i-1] >> 30)) * 1566083941UL))
                - i;
        mt32->mt[i] &= 0xffffffffUL; /* для WORDSIZE > 32 машин */
        i++;
        if (i>=N) { mt32->mt[0] = mt32->mt[N-1]; i=1; }
    }

    mt32->mt[0] = 0x80000000UL; /* старший бит равен 1; обеспечение ненулевого исходного массива*/
}

/* генерирует случайное число на интервале [0,0xffffffff] */
unsigned long genrand_int32(mt19937_32 *mt32)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mt32->mti >= N) { /* генерировать N слов за один раз */
        int kk;

        if (mt32->mti == N+1)   /* если init_genrand() не был вызван, */
            init_genrand(5489UL,mt32); /* используется начальное семя по умолчанию */

        for (kk=0;kk<N-M;kk++) {
            y = (mt32->mt[kk]&UPPER_MASK)|(mt32->mt[kk+1]&LOWER_MASK);
            mt32->mt[kk] = mt32->mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt32->mt[kk]&UPPER_MASK)|(mt32->mt[kk+1]&LOWER_MASK);
            mt32->mt[kk] = mt32->mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt32->mt[N-1]&UPPER_MASK)|(mt32->mt[0]&LOWER_MASK);
        mt32->mt[N-1] = mt32->mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mt32->mti = 0;
    }

    y = mt32->mt[mt32->mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* генерирует случайное число на интервале [0,0x7ffffffff] */
long genrand_int31(mt19937_32 *mt32)
{
    return (long)(genrand_int32(mt32)>>1);
}

/* генерирует случайное число на [0,1]-реальном интервале */
double genrand_real1(mt19937_32 *mt32)
{
    return genrand_int32(mt32)*(1.0/4294967295.0);
    /*2^32-1 */
}

/* генерирует случайное число на [0,1)-реальном интервале */
double genrand_real2(mt19937_32 *mt32)
{
    return genrand_int32(mt32)*(1.0/4294967296.0);
    /*  2^32 */
}

/* генерирует случайное число на (0,1)-реальном интервале */
double genrand_real3(mt19937_32 *mt32)
{
    return (((double)genrand_int32(mt32)) + 0.5)*(1.0/4294967296.0);
    /*  2^32 */
}

/* генерирует случайное число на [0,1) с 53-битным разрешением*/
double genrand_res53(mt19937_32 *mt32)
{
    unsigned long a=genrand_int32(mt32)>>5, b=genrand_int32(mt32)>>6;
    return(a*67108864.0+b)*(1.0/9007199254740992.0);
}



