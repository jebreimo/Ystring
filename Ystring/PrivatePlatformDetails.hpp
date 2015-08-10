//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-28
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <cstddef>
#include <cstdint>
#include "PlatformDetails.hpp"

namespace Ystring
{

template <typename T>
struct InternalCharType
{
    typedef T Type;
};

#define DEFINE_INTERNAL_CHAR_TYPE(type, internalType) \
    template <> \
    struct InternalCharType<type> \
    { \
        typedef internalType Type; \
    }

DEFINE_INTERNAL_CHAR_TYPE(int8_t, char);
DEFINE_INTERNAL_CHAR_TYPE(uint8_t, char);
DEFINE_INTERNAL_CHAR_TYPE(int16_t, uint16_t);
DEFINE_INTERNAL_CHAR_TYPE(int32_t, uint32_t);

#ifdef WCHAR_IS_2_BYTES
    DEFINE_INTERNAL_CHAR_TYPE(wchar_t, uint16_t);
#else
    DEFINE_INTERNAL_CHAR_TYPE(wchar_t, uint32_t);
#endif

template <typename T>
auto internal_char_type_cast(T* s)
        -> typename InternalCharType<T>::Type*
{
    typedef typename InternalCharType<T>::Type Type;
    return reinterpret_cast<Type*>(s);
}

template <typename T>
auto internal_char_type_cast(const T* s)
        -> const typename InternalCharType<T>::Type*
{
    typedef typename InternalCharType<T>::Type Type;
    return reinterpret_cast<const Type*>(s);
}

}