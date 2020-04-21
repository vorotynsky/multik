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

#include <gl.h>
#include "numeric.hpp"

namespace multik::types::gl
{
    constexpr GLint boolean(bool value)
    {
        return value == true ? GL_TRUE : GL_FALSE;
    }

    template <typename T>
    constexpr GLenum type();

    template <NumericType type>
    constexpr GLenum toEnum();

    #define MULTIK_TYPE_GL_CHECK(t, gltype, glenum, nt)       \
        template<>                                            \
        constexpr GLenum type<t>() {                          \
            static_assert(sizeof(t) == sizeof(gltype));       \
            return glenum;                                    \
        }                                                     \
        template<>                                            \
        constexpr GLenum toEnum<nt>() {                       \
            return glenum;                                    \
        }
        

    MULTIK_TYPE_GL_CHECK(signed char, GLbyte, GL_BYTE, NumericType::SByte)
    MULTIK_TYPE_GL_CHECK(short, GLshort, GL_SHORT, NumericType::SShort)
    MULTIK_TYPE_GL_CHECK(int, GLint, GL_INT, NumericType::SInt)

    MULTIK_TYPE_GL_CHECK(unsigned char, GLubyte, GL_UNSIGNED_BYTE, NumericType::UByte)
    MULTIK_TYPE_GL_CHECK(unsigned short, GLushort, GL_UNSIGNED_SHORT, NumericType::UShort)
    MULTIK_TYPE_GL_CHECK(unsigned int, GLuint, GL_UNSIGNED_INT, NumericType::UInt)

    MULTIK_TYPE_GL_CHECK(bool, GLboolean, GL_BOOL, NumericType::Boolean)
    MULTIK_TYPE_GL_CHECK(float, GLfloat, GL_FLOAT, NumericType::SFloat)
    MULTIK_TYPE_GL_CHECK(double, GLdouble, GL_DOUBLE, NumericType::Double)

    #undef MULTIK_TYPE_GL_CHECK

    constexpr GLenum toEnum(NumericType type)
    {
        switch (type)
        {
        case NumericType::SByte:   return toEnum<NumericType::SByte>();
        case NumericType::SShort:  return toEnum<NumericType::SShort>();
        case NumericType::SInt:    return toEnum<NumericType::SInt>();

        case NumericType::UByte:   return toEnum<NumericType::UByte>();
        case NumericType::UShort:  return toEnum<NumericType::UShort>();
        case NumericType::UInt:    return toEnum<NumericType::UInt>();
        
        case NumericType::Boolean: return toEnum<NumericType::Boolean>();
        case NumericType::SFloat:  return toEnum<NumericType::SFloat>();
        case NumericType::Double:  return toEnum<NumericType::Double>();
        
        default:
            throw std::bad_cast();
            return GL_INVALID_ENUM;
        }
    }

}
