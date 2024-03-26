#pragma once

#include <cstddef>
#include <numeric>

namespace multik::types
{
    /// Tiny size type
    using tsize_t = unsigned char;

    /// Short size type
    using ssize_t = unsigned short;


    enum NumericType {
        SByte, UByte,
        SShort, UShort,
        SInt, UInt,
        Boolean,
        SFloat,
        Double
    };

    template <typename T>
    NumericType toTypeEnum();

    #define MULTIK_NUMERIC_TYPES(t, nt)             \
        template<>                                  \
        constexpr NumericType toTypeEnum<t>() {     \
            return nt;                              \
        }

    MULTIK_NUMERIC_TYPES(signed char, NumericType::SByte)
    MULTIK_NUMERIC_TYPES(signed short, NumericType::SShort)
    MULTIK_NUMERIC_TYPES(signed int, NumericType::SInt)

    MULTIK_NUMERIC_TYPES(unsigned char, NumericType::UByte)
    MULTIK_NUMERIC_TYPES(unsigned short, NumericType::UShort)
    MULTIK_NUMERIC_TYPES(unsigned int, NumericType::UInt)

    MULTIK_NUMERIC_TYPES(bool, NumericType::Boolean)
    MULTIK_NUMERIC_TYPES(float, NumericType::SFloat)
    MULTIK_NUMERIC_TYPES(double, NumericType::Double)

    #undef MULTIK_NUMERIC_TYPES
}
