/**
 * @file math_utils.h
 * @brief Sample code so the hooks have something to format and test.
 */
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

namespace math_utils
{

/**
 * @brief Clamp value into [lo, hi].
 * @param value Input value.
 * @param lo Lower bound.
 * @param hi Upper bound, must be >= lo.
 * @return Clamped value. No side effects.
 */
constexpr int clamp(const int value, const int lo, const int hi)
{
    return value < lo ? lo : (value > hi ? hi : value);
}

} // namespace math_utils

#endif // MATH_UTILS_H
