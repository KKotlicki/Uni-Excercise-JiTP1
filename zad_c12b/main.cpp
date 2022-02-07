#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


void move_bat(vector<vector<int>>& bat_position, vector<vector<bool>> possible_windows, int w, int h)
{
    int sum_of_windows = 0;
    int x_sum_of_windows_coordinates = 0;
    int y_sum_of_windows_coordinates = 0;
    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            if(possible_windows[x][y])
            {
                x_sum_of_windows_coordinates += x;
                y_sum_of_windows_coordinates += y;
                sum_of_windows++;

            }
        }
    }
    double x_balance_point = (double(x_sum_of_windows_coordinates))/(double(sum_of_windows));
    double y_balance_point = (double(y_sum_of_windows_coordinates))/(double(sum_of_windows));

    double x_move = double(bat_position[1][0]);
    double y_move = double(bat_position[1][1]);

    if(sum_of_windows < w)
    {
        y_move = 2 * y_balance_point - int(bat_position[1][1]);
    }
    else if(sum_of_windows < h)
    {
        x_move = 2 * x_balance_point - int(bat_position[1][0]);
    }
    else {
        x_move = 2 * x_balance_point - int(bat_position[1][0]);
        y_move = 2 * y_balance_point - int(bat_position[1][1]);
    }

    bat_position[0][0] = int(bat_position[1][0]);
    bat_position[0][1] = int(bat_position[1][1]);
    bat_position[1][0] = round(x_move);
    bat_position[1][1] = round(y_move);

    if(x_move >= w && 0 <= y_move && y_move < h)
    {
        x_move = w - 1;
        int new_y = (double((y_move - bat_position[0][1])*(w - 1 - bat_position[0][0])))/
                (double(x_move - bat_position[0][0])) + bat_position[0][1];
        bat_position[1][1] = round(new_y);
        bat_position[1][0] = x_move;
    }
    else if(x_move < 0 && 0 <= y_move && y_move < h)
    {
        x_move = 0;
        int new_y = (double((y_move - bat_position[0][1])*(0 - bat_position[0][0])))/
                    (double(x_move - bat_position[0][0])) + bat_position[0][1];
        bat_position[1][1] = round(new_y);
        bat_position[1][0] = x_move;
    }
    else if(y_move >= h)
    {
        y_move = h - 1;
        int new_x = (double((x_move - bat_position[0][0])*(h - 1 - bat_position[0][1])))/
                    (double(y_move - bat_position[0][1])) + bat_position[0][0];

        bat_position[1][0] = round(new_x);
        bat_position[1][1] = y_move;
    }
    else if(y_move < 0)
    {
        y_move = 0;
        int new_x = (double((x_move - bat_position[0][0])*(0 - bat_position[0][1])))/
                    (double(y_move - bat_position[0][1])) + bat_position[0][0];

        bat_position[1][0] = round(new_x);
        bat_position[1][1] = y_move;
    }



}

void update_possible_windows(vector<vector<int>>& bat_position, vector<vector<bool>>& possible_windows, int w, int h, string bomb_dir)
{
    // y = m*x + b
    int x1 = int(bat_position[0][0]);
    int y1 = int(bat_position[0][1]);
    int x2 = int(bat_position[1][0]);
    int y2 = int(bat_position[1][1]);
    double x0 = (double(x1 + x2))/2.0;
    double y0 = (double(y1 + y2))/2.0;
    if (y1 == y2 && bomb_dir == "WARMER")
    {
        if (x2 > x1)
        {
            for (int x = 0; x < w; x++) {
                for (int y = 0; y < h; y++) {
                    if (double(x) >= x0) { possible_windows[x][y] = false; }
                }
            }
        }
        if (x2 < x1)
        {
            for (int x = 0; x < w; x++) {
                for (int y = 0; y < h; y++) {
                    if (double(x) <= x0) { possible_windows[x][y] = false; }
                }
            }
        }
    }
    double a = (double(x2 - x1))/(double(y1 - y2));
    // b = y0 - a*x0
    double b = y0 - a * x0;
    if (bomb_dir == "WARMER" && y1 < y2)
    {
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                if (y < floor(a * x + b + 1) && bool(possible_windows[x][y])) { possible_windows[x][y] = false;}
            }
        }
    }
    if (bomb_dir == "WARMER" && y1 > y2)
    {
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                if (y > floor(a * x + b + 1) && bool(possible_windows[x][y])) { possible_windows[x][y] = false;}
            }
        }
    }
    if (bomb_dir == "COLDER" && y1 < y2)
    {
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                if (y >= ceil(a * x + b) && bool(possible_windows[x][y])) { possible_windows[x][y] = false;}
            }
        }
    }
    if (bomb_dir == "COLDER" && y1 > y2)
    {
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                if (y <= floor(a * x + b) && bool(possible_windows[x][y])) { possible_windows[x][y] = false;}
            }
        }
    }
}

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
    //string old_bomb_dir = "UNKNOWN";
    //int possible_windows[w][h];
    vector<vector<bool>> possible_windows(w, vector<bool>(h, true));
//    for(int i = 0; i < w; i++)
//    {
//        for(int j = 0; j < h; j++)
//        {possible_windows[i][j] = 0;}
//    }
    vector<vector<int>> bat_position = {{x0, y0}, {x0, y0}};

    // game loop
    while (1) {
        string bomb_dir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bomb_dir; cin.ignore();

        update_possible_windows(bat_position, possible_windows, w, h, bomb_dir);
        if(bomb_dir == "UNKNOWN")
        {
            bat_position[0][0] = int(bat_position[1][0]);
            bat_position[0][1] = int(bat_position[1][1]);
            bat_position[1][0] = w/2;
            bat_position[1][1] = h/2;
        }
        else {
            move_bat(bat_position, possible_windows, w, h);
        }
        // if(bat_position[1][0] > 10)


        cout << bat_position[1][0] << " " << bat_position[1][1] << endl;
    }
}