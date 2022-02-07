#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

//int getNumber(double num)
//{
//    if(num < 1) return 1;
//    return floor(num);
//}

void first_move_coordinate(int max_coordinate, vector<int> &coordinates_history)
{
    int move = max_coordinate / 2;
    if(coordinates_history[0] < max_coordinate / 2.0) {
//        move = getNumber(double(max_coordinate + coordinates_history[0]) / 2.0);
        move = floor(double(max_coordinate + coordinates_history[0]) / 2.0);
    }
    if(coordinates_history[0] > max_coordinate / 2.0) {
        move = ceil(double(coordinates_history[0]) / 2.0);
    }
    coordinates_history.push_back(move);
}

void warmer_move_coordinate(vector<int> &coordinates_history)
{
    int vsize = coordinates_history.size();
    int move;
    if(coordinates_history[vsize - 1] < coordinates_history[vsize - 2]) {
//        move = getNumber((double(3 * coordinates_history[vsize - 1] - coordinates_history[vsize - 2])) / 2.0);
        move = floor((double(3 * coordinates_history[vsize - 1] - coordinates_history[vsize - 2])) / 2.0);
    }
    else if(coordinates_history[vsize - 1] > coordinates_history[vsize - 2]) {
        move = ceil((double(3 * coordinates_history[vsize - 1] - coordinates_history[vsize - 2])) / 2.0);
    }
    else
    {
        move = coordinates_history[vsize - 1];
    }

    coordinates_history.push_back(move);
}

void colder_move(vector<int> &x_coordinates_history, vector<int> &y_coordinates_history, string past_bomb_dir)
{
    int x_move;
    int y_move;

    if(past_bomb_dir == "WARMER")
    {
        int vsize = x_coordinates_history.size();
        x_move = x_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 2] - y_coordinates_history[vsize - 1];
        y_move = y_coordinates_history[vsize - 2] - x_coordinates_history[vsize - 2] + x_coordinates_history[vsize - 1];
    }
    else if(past_bomb_dir == "SAME")
    {
        x_coordinates_history.pop_back();
        y_coordinates_history.pop_back();
        int vsize = x_coordinates_history.size();
        x_move = ceil(double(x_coordinates_history[vsize - 2] + x_coordinates_history[vsize - 1] - y_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 1]) / 2.0);
        y_move = ceil(double(y_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 1] + x_coordinates_history[vsize - 2] - x_coordinates_history[vsize - 1]) / 2.0);
    }
    else if(past_bomb_dir == "COLDER")
    {
        x_coordinates_history.pop_back();
        y_coordinates_history.pop_back();
        int vsize = x_coordinates_history.size();
        x_move = ceil(double(x_coordinates_history[vsize - 2] + x_coordinates_history[vsize - 1] - y_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 1]) / 2.0);
        y_move = ceil(double(y_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 1] + x_coordinates_history[vsize - 2] - x_coordinates_history[vsize - 1]) / 2.0);
    }
    else
    {
        x_coordinates_history.pop_back();
        y_coordinates_history.pop_back();
        int vsize = x_coordinates_history.size();
        x_move = ceil(x_coordinates_history[vsize - 1]/2.0);
        y_move = ceil(y_coordinates_history[vsize - 1]/2.0);
    }

    x_coordinates_history.push_back(x_move);
    y_coordinates_history.push_back(y_move);
}

void same_move(vector<int> &x_coordinates_history, vector<int> &y_coordinates_history, string past_bomb_dir, int w, int h)
{
    int vsize = x_coordinates_history.size();
    int x_move = x_coordinates_history[vsize - 1];
    int y_move = y_coordinates_history[vsize - 1];

    if(past_bomb_dir == "WARMER")
    {
        x_move = ceil(double(x_coordinates_history[vsize - 2] + x_coordinates_history[vsize - 1] + y_coordinates_history[vsize - 2] - y_coordinates_history[vsize - 1]) / 2.0);
        y_move = ceil(double(y_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 1] - x_coordinates_history[vsize - 2] + x_coordinates_history[vsize - 1]) / 2.0);

    }
    else if(past_bomb_dir == "COLDER")
    {
        x_coordinates_history.pop_back();
        y_coordinates_history.pop_back();
        vsize = x_coordinates_history.size();
        x_move = ceil(double(x_coordinates_history[vsize - 2] + x_coordinates_history[vsize - 1] - y_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 1]) / 2.0);
        y_move = ceil(double(y_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 1] + x_coordinates_history[vsize - 2] - x_coordinates_history[vsize - 1]) / 2.0);
    }
    else if(past_bomb_dir == "SAME" || past_bomb_dir == "UNKNOWN") {
        x_move = ceil(double(x_coordinates_history[vsize - 2] + x_coordinates_history[vsize - 1] -
                             y_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 1]) / 2.0);
        y_move = ceil(double(y_coordinates_history[vsize - 2] + y_coordinates_history[vsize - 1] +
                             x_coordinates_history[vsize - 2] - x_coordinates_history[vsize - 1]) / 2.0);
        if (x_coordinates_history[vsize - 1] == 0) {
            x_move = 1;
        }
        if (y_coordinates_history[vsize - 1] == 0) {
            y_move = 1;
        }
        if (x_coordinates_history[vsize - 1] == w - 1) {
            x_move = w - 2;
        }
        if (y_coordinates_history[vsize - 1] == h - 1) {
            y_move = h - 2;
        }
    }

    x_coordinates_history.push_back(x_move);
    y_coordinates_history.push_back(y_move);
}




//void out_of_range_move_fix(vector<int> &x_coordinates_history, vector<int> &y_coordinates_history, int w, int h)
//{
//    int vsize = x_coordinates_history.size();
//    while(int(x_coordinates_history.back()) >= w || int(y_coordinates_history.back()) >= h)
//    {
//        if(int(x_coordinates_history.back()) <= w)
//        {
//        x_coordinates_history[vsize - 1] = w;
//        int new_y = (double((y_coordinates_history[vsize - 1] - y_coordinates_history[vsize - 2])*(w - x_coordinates_history[vsize - 2])))/
//                (double(x_coordinates_history[vsize - 1] - x_coordinates_history[vsize - 2]));
//        if(new_y - int(new_y) >= 0.5){new_y++;}
//        y_coordinates_history[vsize - 1] = int(new_y);
//        }
//    }
//}


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
    vector<int> x_coordinates_history = {x0};
    vector<int> y_coordinates_history = {y0};
    string past_bomb_dir = "";


    // game loop
    while (1) {
        string bomb_dir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bomb_dir; cin.ignore();
        if(bomb_dir == "UNKNOWN")
        {
            first_move_coordinate(w, x_coordinates_history);
            first_move_coordinate(h, y_coordinates_history);
        }
        else if(bomb_dir == "WARMER")
        {
            warmer_move_coordinate(x_coordinates_history);
            warmer_move_coordinate(y_coordinates_history);
        }
        else if(bomb_dir == "COLDER")
        {
            colder_move(x_coordinates_history, y_coordinates_history, past_bomb_dir);
        }
        else
        {
            same_move(x_coordinates_history, y_coordinates_history, past_bomb_dir, w, h);
        }

        if(int(x_coordinates_history.back()) > w - 1)
        {
            x_coordinates_history.back() = w - 1;
        }
        if(int(x_coordinates_history.back()) < 0)
        {
            x_coordinates_history.back() = 0;
        }
        if(int(y_coordinates_history.back()) > h - 1)
        {
            y_coordinates_history.back() = h - 1;
        }
        if(int(y_coordinates_history.back()) < 0)
        {
            y_coordinates_history.back() = 0;
        }
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        past_bomb_dir = bomb_dir;
        cout << x_coordinates_history.back() << " " << y_coordinates_history.back() << endl;
    }
}