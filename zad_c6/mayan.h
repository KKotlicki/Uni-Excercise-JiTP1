// Rajmund Kozuszek (121528)
#pragma once
#include <string>

const unsigned int mayan_base = 20;

char uint2md(unsigned int digit_value);
unsigned int md2uint(char mayan_digit);

unsigned int mayan2uint(const std::string& digits);
std::string uint2mayan(unsigned int value);
