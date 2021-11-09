// Konrad Kotlicki (310958)
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

bool approx_equal(double first, double second, double eps = 1e-6)
{
    return abs(second - first) <= eps;
};

double hexagon_area(double edge_len)
{
    return 3.0 * (double) sqrt(3.0) * edge_len * edge_len / 2.0;
};

double circle_area(double radius)
{
    return radius * radius * M_PI;
};

int test_hexagon_area(double edge_len, double expected_area)
{
    double hexagon_area_var = hexagon_area(edge_len);
    cout << "Hexagon edge length: " << edge_len << "\nHexagon area: " << hexagon_area_var << endl;
    cout << "Expected area: " << expected_area << endl;
    cout << "Is area same as expected: " << approx_equal(hexagon_area_var, expected_area) << endl << endl;
};

int test_circle_area(double radius, double expected_area)
{
    double circle_area_var = circle_area(radius);
    cout << "Circle radius length: " << radius << "\nCircle area: " << circle_area_var << endl;
    cout << "Expected area: " << expected_area << endl;
    cout << "Is area same as expected: " << approx_equal(circle_area_var, expected_area) << endl << endl;
};

int main()
{
    cout << std::boolalpha;
    test_hexagon_area((double) pow(3, 1.0/4.0), 4.5);
    test_hexagon_area(1.0, 2.5980);
    test_hexagon_area(1.0, 2.598076);
    test_circle_area(1.0/(double) pow(M_PI, 1.0/2.0), 1);
    test_circle_area(1.0, 3.141592);
    test_circle_area(1.0, 3.141);

    return 0;
}
