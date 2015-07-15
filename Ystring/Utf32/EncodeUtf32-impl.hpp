//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-11
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iterator>
#include "../Utilities/Endian.hpp"
#include "../Utilities/Union32.hpp"

namespace Ystring { namespace Utf32 {

using Ystring::Utilities::IsBigEndian;
using Ystring::Utilities::IsLittleEndian;
using Ystring::Utilities::swapEndianness;

template <typename OutIt, bool SwapBytes>
OutIt addUtf32(OutIt out, uint32_t codePoint)
{
    swapEndianness<SwapBytes>(codePoint);
    *out = codePoint;
    return ++out;
}

template <typename OutIt>
OutIt addUtf32(OutIt out, uint32_t codePoint)
{
    return addUtf32<OutIt, false>(out, codePoint);
}

template <typename OutIt>
OutIt addUtf32LE(OutIt out, uint32_t codePoint)
{
    return addUtf32<OutIt, IsBigEndian>(out, codePoint);
}

template <typename OutIt>
OutIt addUtf32BE(OutIt out, uint32_t codePoint)
{
    return addUtf32<OutIt, IsLittleEndian>(out, codePoint);
}

template <bool SwapBytes, typename FwdIt, typename ChrType>
size_t encodeUtf32(FwdIt& begin, FwdIt end, uint32_t codePoint, ChrType)
{
    if (begin == end)
        return 0;
    swapEndianness<SwapBytes>(codePoint);
    *begin++ = codePoint;
    return 1;
}

template <bool SwapBytes, typename FwdIt>
size_t encodeUtf32(FwdIt& begin, FwdIt end, uint32_t codePoint, uint8_t)
{
    if (std::distance(begin, end) < 4)
        return 0;
    Ystring::Utilities::Union32 word(codePoint);
    swapEndianness<SwapBytes>(word);
    *begin++ = word.i8[0];
    *begin++ = word.i8[1];
    *begin++ = word.i8[2];
    *begin++ = word.i8[3];
    return 4;
}

template <bool SwapBytes, typename FwdIt>
size_t encodeUtf32(FwdIt& begin, FwdIt end, uint32_t codePoint, char)
{
    return encodeUtf32<SwapBytes>(begin, end, codePoint, uint8_t());
}

template <typename FwdIt>
size_t encodeUtf32(FwdIt& begin, FwdIt end, uint32_t codePoint)
{
    return encodeUtf32<false>(
            begin, end, codePoint,
            typename std::iterator_traits<FwdIt>::value_type());
}

template <typename FwdIt>
size_t encodeUtf32LE(FwdIt& begin, FwdIt end, uint32_t codePoint)
{
    return encodeUtf32<IsBigEndian>(
            begin, end, codePoint,
            typename std::iterator_traits<FwdIt>::value_type());
}

template <typename FwdIt>
size_t encodeUtf32BE(FwdIt& begin, FwdIt end, uint32_t codePoint)
{
    return encodeUtf32<IsLittleEndian>(
            begin, end, codePoint,
            typename std::iterator_traits<FwdIt>::value_type());
}

}}
