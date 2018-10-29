#include <iostream>
#include <stack>

int main()
{
    unsigned int n, p;
    std::stack<std::pair<unsigned int, unsigned int>> params;
    std::cin >> n >> p;

    unsigned int quotient = n;
    unsigned int remainder = 0;
    int count = 0;

    while (quotient != 0)
    {
        remainder = quotient % p;
        quotient = quotient / p;
        params.push(std::pair<unsigned int, unsigned int>(remainder, count++));
    }

    while (!params.empty())
    {
        std::pair<unsigned int, unsigned int> pair = params.top();
        params.pop();
        if (pair.first != 0)
        {
            std::cout << pair.first << " * " << p << " ^ " << pair.second;
            if (!(params.empty() || (params.size() == 1 && params.top().first == 0)))
            {
                std::cout << " + ";
            }
        }
    }
    std::cout << std::endl;
    return 0;
}
