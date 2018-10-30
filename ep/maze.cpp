
#include <iostream>
#include <string>
#include <random>
#include <stack>

#define DENSITY 5
#define RED "\033[41m"
#define GREEN "\033[42m"
#define YELLOW "\033[43m"
#define WHITE "\033[47m"

using namespace std;

class Point
{
  public:
    int X;
    int Y;

    Point()
    {
    }

    Point(int x, int y)
    {
        X = x;
        Y = y;
    }

    Point &operator=(const Point &point)
    {
        if (this == &point)
        {
            return *this;
        }

        X = point.X;
        Y = point.Y;

        return *this;
    }

    bool operator==(const Point &point) const
    {
        if (X == point.X && Y == point.Y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(const Point &point) const
    {
        return (X != point.X || Y != point.Y);
    }
};

bool solve(vector<vector<int>> &maze, Point start, Point end)
{
    stack<Point> st;

    if (maze[start.X][start.Y] != 1)
        return false;

    st.push(start);

    while (!maze.empty())
    {
        Point p = st.top();
        st.pop();
        maze[start.X][start.Y] = 2;

        // down
        if (p.X + 1 < maze.size() && maze[p.X + 1][p.Y] == 1)
        {
            st.push(Point(p.X + 1, p.Y));
        }

        // left-down
        if (p.X + 1 < maze.size() && p.Y - 1 > 0 && maze[p.X + 1][p.Y - 1] == 1)
        {
            st.push(Point(p.X + 1, p.Y - 1));
        }

        // left
        if (p.Y - 1 > 0 && maze[p.X][p.Y - 1] == 1)
        {
            st.push(Point(p.X, p.Y - 1));
        }

        // left-uo
        if (p.X - 1 > 0 && p.Y - 1 > 0 && maze[p.X - 1][p.Y - 1] == 1)
        {
            st.push(Point(p.X - 1, p.Y - 1));
        }

        // up
        if (p.X - 1 > 0 && maze[p.X - 1][p.Y] == 1)
        {
            st.push(Point(p.X - 1, p.Y));
        }

        // right-up
        if (p.X - 1 > 0 && p.Y + 1 < maze[0].size() && maze[p.X - 1][p.Y + 1] == 1)
        {
            st.push(Point(p.X - 1, p.Y + 1));
        }

        // right
        if (p.Y + 1 < maze[0].size() && maze[p.X][p.Y + 1] == 1)
        {
            st.push(Point(p.X, p.Y + 1));
        }

        // right-down
        if (p.X + 1 < maze.size() && p.Y + 1 < maze[0].size() && maze[p.X + 1][p.Y + 1] == 1)
        {
            st.push(Point(p.X + 1, p.Y + 1));
        }

        if (maze[end.X][end.Y] == 2)
            return true;
    }

    return false;
}

vector<vector<int>> generate(int width, int height)
{
    mt19937 rng;
    rng.seed(random_device()());

    default_random_engine fixed;
    uniform_int_distribution<int> distribution(0, 9);

    vector<vector<int>> maze(height, vector<int>(width));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            maze[i][j] = distribution(rng) < DENSITY ? 1 : 0;
        }
    }

    return maze;
}

void print(vector<vector<int>> maze)
{
    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[0].size(); j++)
        {
            switch (maze[i][j])
            {
            case 0:
                cout << GREEN << "  "
                     << "\033[0m";
                break;
            case 1:
                cout << YELLOW << "  "
                     << "\033[0m";
                break;
            case 2:
                cout << RED << "  "
                     << "\033[0m";
                break;
            case 3:
                cout << WHITE << "  "
                     << "\033[0m";
                break;
            }
        }

        cout << endl;
    }
}

int main()
{
    int width;
    int height;
    Point start, end;

    cout << "Please input the width:";
    cin >> width;
    cout << "Please input the height:";
    cin >> height;

    mt19937 rng;
    rng.seed(random_device()());

    uniform_int_distribution<int> distribution(0, 9);

    vector<vector<int>> maze = generate(width, height);

    print(maze);

    cout << "Please input the start point:";
    cin >> start.X >> start.Y;

    cout << "Please input the end point:";
    cin >> end.X >> end.Y;

    if (solve(maze, start, end))
        print(maze);
    else
        cout << "No answer." << endl;

    return 0;
}
