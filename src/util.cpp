#include "util.hpp"

float Utility::ReLU(float value)
{
    return value < 0 ? 0 : value;
}