#include <iostream>
#include <stack>
#include <cmath>

std::bitset<UINT32_MAX> flags;

void eratosthenes(unsigned int p)
{
    for (unsigned int i = 0; i <= p; i++)
    {
        flags[i] = true;
    }

    flags[0] = false;
    flags[1] = false;

    for (int i = 2; i < p; i++)
    {
        if (flags[i])
        {
            for (u_int32_t j = i * i; j <= p; j += i)
            {
                flags[j] = false;
            }
        }
    }
}

int main()
{
    unsigned int n;
    std::cin >> n;

    eratosthenes(n);
    for (int i = 2; i <= n; i++)
    {
        if (flags[i])
        {
            for (int j = 0; (std::pow(i, j) - 1) / (i - 1) <= n; j++)
            {
                unsigned int sigma = (std::pow(i, j) - 1) / (i - 1);
                if (sigma == n)
                {
                    std::cout << "p = " << i << " k = " << j - 1 << std::endl;
                    break;
                }
            }
        }
    }
    return 0;
}
