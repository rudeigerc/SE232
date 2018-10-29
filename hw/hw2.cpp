#include <bitset>
#include <iostream>
#include <math.h>

std::bitset<UINT32_MAX> flags;
bool flags_delta[1000000];

// Sieve of Eratosthenes
void eratosthenes(unsigned long long M, unsigned long long N)
{
    for (u_int32_t i = 2; i * i <= N; i++)
    {
        if (flags[i])
        {
            for (u_int32_t j = i * i; j * j <= N; j += i)
            {
                flags[j] = false;
            }
            for (unsigned long long j = (M + i - 1) / i * i; j <= N; j += i)
            {
                flags_delta[j - M] = false;
            }
        }
    }
}

int main()
{
    unsigned long long M, N;
    std::cin >> M >> N;

    for (u_int32_t i = 0; i * i <= N; i++)
    {
        flags[i] = true;
    }

    flags[0] = false;
    flags[1] = false;

    for (int i = 0; i <= N - M; i++)
    {
        flags_delta[i] = true;
    }

    eratosthenes(M, N);

    int prev = -1;
    int delta = INT32_MIN;

    for (int i = 0; i <= N - M; i++)
    {
        if (flags_delta[i] && i + M != 1)
        {
            if (prev >= 0 && i - prev > delta)
            {
                delta = i - prev;
            }
            prev = i;
        }
    }
    std::cout << (delta < 0 ? 0 : delta);

    return 0;
}