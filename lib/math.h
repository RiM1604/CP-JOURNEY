#ifndef MATH
#define MATH

const long long mod = 1e9 + 7;

inline long long bin_pow(long long a, long long b)
{
    long long res = 1;

    while (b)
    {
        if (b % 2 == 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;

        b /= 2;
    }
    return res;
}

inline long long ll_bin_pow(int a, int b)
{
    long long res = 1;

    while (b)
    {
        if (b % 2 == 1)
        {
            res = (res * a);
        }
        a = (a * a);

        b /= 2;
    }
    return res;
}


inline long long nCr(long long n, long long r)
{
    long long n_r_factorial_mod = 1, r_factorial_mod = 1, n_factorial_mod = 1, temp_factorial = 1;

    if (r == 0 || r == n)
        return 1;

    int i;
    for (i = 1; i <= n; ++i)
    {
        temp_factorial = temp_factorial * i % mod;

        if (i == r)
            r_factorial_mod = temp_factorial;
        else if (i == n - r)
            n_r_factorial_mod = temp_factorial;
        else if (i == n)
            n_factorial_mod = temp_factorial;
    }
    
    return ((n_factorial_mod * bin_pow(n_r_factorial_mod, mod - 2) % mod) * bin_pow(r_factorial_mod, mod - 2) % mod);
}

const int pi[51] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 5, 1, 0};

#endif