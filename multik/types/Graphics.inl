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
