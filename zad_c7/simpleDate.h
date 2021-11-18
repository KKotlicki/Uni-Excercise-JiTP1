// Konrad Kotlicki (310958)
#pragma once

class simpleDate {
public:
    class invalid_argument{};
    class invalid_operation{};

    simpleDate(int d = 1, int m = 1, int y = 2019);

    void print() const;
    int get_day() const {return d;};
    int get_month() const {return m;};
    int get_year() const {return y;};

    void next_day();
    void prev_day();

private:
    int d, m, y;
    bool is_valid(int d, int m, int y);
};
