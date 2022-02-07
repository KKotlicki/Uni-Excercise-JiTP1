#include <iostream>
#include <string>
#include "BatFlight.h"

using namespace std;


int main()
{
    int w; // width of the building.
    int h; // height of the building.
    cin >> w >> h; cin.ignore();
    int n; // maximum number of turns before game over.
    cin >> n; cin.ignore();
    int x0;
    int y0;
    cin >> x0 >> y0; cin.ignore();

    // game loop
    BatFlight bf(x0, y0, w, h);
    while (1) {
        string bombDir;
        cin >> bombDir; cin.ignore();

        bf.DoJump(bombDir);
        // the location of the next window Batman should jump to.
        cout << bf.curX() << " " << bf.curY() << endl;
    }
}
