#include "Graphics.hpp"

#include <numeric>

namespace multik::types {
    template <typename T>
    int Single<T>::size()
    {
        return sizeof(T); 
    }
    
    template <typename T>
    int Single<T>::count()
    {
        return 1; 
    }

    template <typename T>
    GraphicsTypeInfo Single<T>::info()
    {
        return { size(), count(), types::toTypeEnum<T>()};
    }

    
    template <typename T, tsize_t dimensions>
    int Vector<T, dimensions>::size()
    {
        return sizeof(T) * dimensions;
    }
    
    template <typename T, tsize_t dimensions>
    int Vector<T, dimensions>::count()
    {
        return dimensions;
    }

    template <typename T, tsize_t dimensions>
    GraphicsTypeInfo Vector<T, dimensions>::info()
    {
        return { size(), count(), types::toTypeEnum<T>()};
    }

    
    template <typename T, tsize_t dimensions>
    int Matrix<T, dimensions>::size()
    {
        return sizeof(T) * dimensions * dimensions;
    }
    
    template <typename T, tsize_t dimensions>
    int Matrix<T, dimensions>::count()
    {
        return dimensions * dimensions;
    }

    template <typename T, tsize_t dimensions>
    GraphicsTypeInfo Matrix<T, dimensions>::info()
    {
        return { size(), count(), types::toTypeEnum<T>()};
    }
}
