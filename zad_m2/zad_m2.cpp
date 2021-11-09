#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    const double radians_per_degree = M_PI / 180.0;
    const double grads_per_degree = 10.0 / 9.0;

    double degrees;
    cout << "Enter angle in degrees: ";
    cin >> degrees;
    double radians = degrees * radians_per_degree;
    cout << "Angle in radians: " << radians << endl;
    double grads = degrees * grads_per_degree;

    // Part below was added just for excercise
    if (grads == 0.0)
    {
        cout << "Angle in grads: 0.0" << endl;
    }
    else if (grads <= 0.01)
    {
        cout << "Angle in centicentigrades: " << grads * 10000;
    }
    else if (grads <= 1.0)
    {
        cout << "Angle in centigrades: " << grads * 100;
    }
    else
    {
        double rest_in_centigrades = (grads - int(grads)) * 100;
        double rest_in_centicentigrades = (rest_in_centigrades - int(rest_in_centigrades)) * 100;
        cout << "Angle in grads: " << (int) grads << " and " << (int) rest_in_centigrades;
        cout << " centigrades and " << rest_in_centicentigrades << " centicentigrades" << endl;
    };

    return 0;
}
