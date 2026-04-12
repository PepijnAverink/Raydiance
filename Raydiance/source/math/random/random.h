#pragma once
#include <random>

namespace Raydiance
{
    namespace Math
    {
        // Inline ensures one instance across all translation units
        inline std::mt19937 rng(std::random_device{}());
    }
}