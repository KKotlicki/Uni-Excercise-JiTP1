#include <string>
#pragma once


class BatFlight
{
public:
    BatFlight(int X0, int Y0, int W, int H)
    {
        x0 = X0;
        y0 = Y0;
        w = x_max = W;
        h = y_max = H;
    }

    void DoJump(std::string bombDir)
    {
        if(bombDir.at(0) == 'U')
        {
            y_max = y0;
            y0 = get_move_coordinate(y_min, y0);
        }
        else if(bombDir.at(0) == 'D')
        {
            y_min = y0;
            y0 = get_move_coordinate(y_max, y0);
        }

        if((char) bombDir.back() == 'L')
        {
            x_max = x0;
            x0 = get_move_coordinate(x_min, x0);
        }
        else if((char) bombDir.back() == 'R')
        {
            x_min = x0;
            x0 = get_move_coordinate(x_max, x0);
        }

        bombDir_old = bombDir;
    }

    int curX(){return x0;}
    int curY(){return y0;}

private:
    int x0;
    int y0;
    int w;
    int h;
    int y_min = 0;
    int y_max;
    int x_min = 0;
    int x_max;
    std::string bombDir_old = "";

    int get_move_coordinate(int max_coordinate, int current_coordinate)
    {
        return (max_coordinate + current_coordinate) / 2;
    }
};
