#include "mt64.h"
/* инициализирует mt[NN] начальным числом */
void init_genrand64(struct mt19937_64* context, unsigned long long seed)
{
    context->mt[0] = seed;
    for (context->mti=1; context->mti<NN; context->mti++)
        context->mt[context->mti] =  (6364136223846793005ULL * (context->mt[context->mti-1] ^ (context->mt[context->mti-1] >> 62)) + context->mti);
}



/* инициализировать массивом с длиной массива */
/* init_key — массив для инициализации ключей */
/* key_length — его длина */
void init_by_array64(struct mt19937_64* context, unsigned long long init_key[],
                     unsigned long long key_length)
{
    unsigned long long i, j, k;
    init_genrand64(context, 19650218ULL);
    i=1; j=0;
    k = (NN>key_length ? NN : key_length);
    for (; k; k--) {
        context->mt[i] = (context->mt[i] ^ ((context->mt[i-1] ^ (context->mt[i-1] >> 62)) * 3935559000370003845ULL))
                         + init_key[j] + j; /* non linear */
        i++; j++;
        if (i>=NN) { context->mt[0] = context->mt[NN-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=NN-1; k; k--) {
        context->mt[i] = (context->mt[i] ^ ((context->mt[i-1] ^ (context->mt[i-1] >> 62)) * 2862933555777941757ULL))
                         - i; /* non linear */
        i++;
        if (i>=NN) { context->mt[0] = context->mt[NN-1]; i=1; }
    }

    context->mt[0] = 1ULL << 63; /* MSB is 1; assuring non-zero initial array */
}

/* генерирует случайное число на интервале [0, 2^64-1] */
unsigned long long genrand64_int64(struct mt19937_64* context)
{
#if 0

		int i;
		unsigned long long x;
		static unsigned long long mag01[2]={0ULL, MATRIX_A64};

		if (mti >= NN) { /* generate NN words at one time */

			/* if init_genrand64() has not been called, */
			/* a default initial seed is used     */
			if (mti == NN+1)
				init_genrand64(5489ULL);

			for (i=0;i<NN-MM;i++) {
				x = (mt[i]&UM)|(mt[i+1]&LM);
				mt[i] = mt[i+MM] ^ (x>>1) ^ mag01[(int)(x&1ULL)];
			}
			for (;i<NN-1;i++) {
				x = (mt[i]&UM)|(mt[i+1]&LM);
				mt[i] = mt[i+(MM-NN)] ^ (x>>1) ^ mag01[(int)(x&1ULL)];
			}
			x = (mt[NN-1]&UM)|(mt[0]&LM);
			mt[NN-1] = mt[MM-1] ^ (x>>1) ^ mag01[(int)(x&1ULL)];

			mti = 0;
		}

		x = mt[mti++];

		x ^= (x >> 29) & 0x5555555555555555ULL;
		x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
		x ^= (x << 37) & 0xFFF7EEE000000000ULL;
		x ^= (x >> 43);

		return x;
#else
    /* Это измененная реализация. */
    size_t i;
    size_t j;
    unsigned long long result;

    if (context->mti >= NN) {/* генерировать NN слов за один раз */
        size_t mid = NN / 2;
        unsigned long long stateMid = context->mt[mid];
        unsigned long long x;
        unsigned long long y;


        for (i = 0, j = mid; i != mid - 1; i++, j++) {
            x = (context->mt[i] & UM) | (context->mt[i + 1] & LM);
            context->mt[i] = context->mt[i + mid] ^ (x >> 1) ^ ((context->mt[i + 1] & 1) * MATRIX_A64);
            y = (context->mt[j] & UM) | (context->mt[j + 1] & LM);
            context->mt[j] = context->mt[j - mid] ^ (y >> 1) ^ ((context->mt[j + 1] & 1) * MATRIX_A64);
        }
        x = (context->mt[mid - 1] & UM) | (stateMid & LM);
        context->mt[mid - 1] = context->mt[NN - 1] ^ (x >> 1) ^ ((stateMid & 1) * MATRIX_A64);
        y = (context->mt[NN - 1] & UM) | (context->mt[0] & LM);
        context->mt[NN - 1] = context->mt[mid - 1] ^ (y >> 1) ^ ((context->mt[0] & 1) * MATRIX_A64);

        context->mti = 0;
    }

    result = context->mt[context->mti];
    context->mti = context->mti + 1;

    result ^= (result >> 29) & 0x5555555555555555ULL;
    result ^= (result << 17) & 0x71D67FFFEDA60000ULL;
    result ^= (result << 37) & 0xFFF7EEE000000000ULL;
    result ^= (result >> 43);

    return result;
#endif
}


/* генерирует случайное число на интервале [0, 2^63-1] */
long long genrand64_int63(struct mt19937_64* context)
{
    return (long long)(genrand64_int64(context) >> 1);
}

/* генерирует случайное число на [0,1]-реальном интервале */
double genrand64_real1(struct mt19937_64* context)
{
    return (genrand64_int64(context) >> 11) * (1.0/9007199254740991.0);
}

/* генерирует случайное число на [0,1)-реальном интервале */
double genrand64_real2(struct mt19937_64* context)
{
    return (genrand64_int64(context) >> 11) * (1.0/9007199254740992.0);
}

/* генерирует случайное число на (0,1)-реальном интервале */
double genrand64_real3(struct mt19937_64* context)
{
    return ((genrand64_int64(context) >> 12) + 0.5) * (1.0/4503599627370496.0);
}