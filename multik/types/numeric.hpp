// Copyright 2020 Vorotynsky Maxim
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    MULTIK_NUMERIC_TYPES(signed short, NumericType::SByte)
    MULTIK_NUMERIC_TYPES(signed int, NumericType::SByte)

    MULTIK_NUMERIC_TYPES(unsigned char, NumericType::UByte)
    MULTIK_NUMERIC_TYPES(unsigned short, NumericType::UByte)
    MULTIK_NUMERIC_TYPES(unsigned int, NumericType::UByte)

    MULTIK_NUMERIC_TYPES(bool, NumericType::Boolean)
    MULTIK_NUMERIC_TYPES(float, NumericType::SFloat)
    MULTIK_NUMERIC_TYPES(double, NumericType::Double)

    #undef MULTIK_NUMERIC_TYPES
}
