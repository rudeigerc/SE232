#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    if (n % 2 != 1)
        return 1;

    int square[n][n];
    memset(square, 0, sizeof(square));

    int x = 0;
    int y = (n - 1) / 2;
    square[x][y] = 1;

    for (int i = 2; i <= n * n; i++)
    {
        // up and down
        x--;
        y++;

        if (x < 0)
            x += n;
        if (y >= n)
            y -= n;

        if (square[x][y] != 0)
        {
            // rollback
            x++;
            y--;
            if (x >= n)
                x -= n;
            if (y < 0)
                y += n;

            // down
            x++;
            if (x >= n)
                x -= n;
        }

        square[x][y] = i;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            std::cout << square[i][j] << '\t';
        std::cout << std::endl;
    }

    return 0;
}