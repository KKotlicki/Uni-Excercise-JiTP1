#include <iostream>
#include <sstream>

class error_messenger
{
	int err_cnt;
public:
	error_messenger()
	{
		err_cnt = 0;
	}
	void report_error(const std::string& msg)
	{
		std::cerr << msg << std::endl;
		++err_cnt;
	}
	int get_err_count() const
	{
	    return err_cnt;
	}
	~error_messenger()
	{
		if (err_cnt == 0)
			std::cerr << "No errors detected!\n";
		else
			std::cerr << "Number of errors: " << err_cnt << std::endl;
	}
};

template <typename T> std::string to_string(const T& src)
{
    std::stringstream ss;
    ss << src;
    return ss.str();
}
