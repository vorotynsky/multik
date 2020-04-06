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

#include "numeric.hpp"

namespace multik::types
{
    struct GraphicsTypeInfo
    {
        int size, count;
    };

    template <typename T>
    struct Single
    {
        static int size();
        static int count();
        static GraphicsTypeInfo info();
    };

    template <typename T, tsize_t dimensions>
    struct Vector 
    {
        static int size();
        static int count();
        static GraphicsTypeInfo info();
    };

    template <typename T, tsize_t dimensions>
    struct Matrix 
    {
        static int size();
        static int count();
        static GraphicsTypeInfo info();
    };

    using Bool   = Single<bool>;
    using Int    = Single<int>;
    using Int2   = Vector<int, 2>;
    using Int3   = Vector<int, 3>;
    using Int4   = Vector<int, 4>;
    using Float  = Single<float>;
    using Float2 = Vector<float, 2>;
    using Float3 = Vector<float, 3>;
    using Float4 = Vector<float, 3>;
    using Mat3   = Matrix<float, 3>;
    using Mat4   = Matrix<float, 4>;
}

#include "Graphics.inl"
