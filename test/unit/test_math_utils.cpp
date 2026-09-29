/**
 * @file test_math_utils.cpp
 * @brief Unit check for math_utils. ponytail: plain asserts, swap to
 * GoogleTest once there is more than one suite.
 */
#include "../../src/math_utils.h"

#include <cassert>

int main()
{
    assert(math_utils::clamp(5, 0, 10) == 5);
    assert(math_utils::clamp(-1, 0, 10) == 0);
    assert(math_utils::clamp(11, 0, 10) == 10);
    return 0;
}
