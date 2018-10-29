#include <vector>
#include <iostream>

typedef std::vector<int> Vector;
std::vector<Vector> vertices;
std::vector<Vector> edges;
std::vector<int> crosses;

enum Polygon
{
    concave,
    convex
};

std::ostream &operator<<(std::ostream &os, Polygon p)
{
    switch (p)
    {
    case concave:
        os << "concave";
        break;
    case convex:
        os << "convex";
        break;
    default:
        os.setstate(std::ios_base::failbit);
    }
    return os;
}

// Overloading for cross product
int operator^(const Vector &a, const Vector &b)
{
    assert(a.size() == b.size() && a.size() == 2);
    return a[0] * b[1] - a[1] * b[0];
}

// Overloading for subtraction
Vector operator-(const Vector &a, const Vector &b)
{
    assert(a.size() == b.size() && a.size() == 2);
    return Vector{b[0] - a[0], b[1] - a[1]};
}

int main()
{
    Polygon polygon = concave;
    std::string point;
    while (std::cin >> point)
    {
        vertices.push_back({point[0], point[2]});
        if (std::cin.peek() == '\n')
        {
            break;
        }
    }

    // Calculator egde of each two vertex
    assert(vertices.size() > 2);
    for (int i = 1; i < vertices.size(); ++i)
    {
        edges.push_back(vertices[i] - vertices[i - 1]);
    }
    edges.push_back(vertices.front() - vertices.back());

    // Calculate cross product of each two edge
    for (int i = 1; i < edges.size(); ++i)
    {
        crosses.push_back(edges[i - 1] ^ edges[i]);
    }
    crosses.push_back(edges.back() ^ edges.front());

    for (int i = 1; i < crosses.size(); ++i)
    {
        if (crosses[i] * crosses[i - 1] < 0)
        {
            polygon = convex;
            break;
        }
    }

    std::cout << polygon << std::endl;

    return 0;
}
