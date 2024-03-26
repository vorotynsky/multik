#pragma once

#include "numeric.hpp"

namespace multik::types
{
    struct GraphicsTypeInfo
    {
        int Size, Count;
        NumericType Type;
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
    using Float4 = Vector<float, 4>;
    using Mat3   = Matrix<float, 3>;
    using Mat4   = Matrix<float, 4>;
}

#include "Graphics.inl"
