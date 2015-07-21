//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-11
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <_types/_uint32_t.h>
#include "../Encoding.hpp"
#include "DecodeUtf32.hpp"
#include "EncodeUtf32.hpp"

namespace Ystring { namespace Utf32 {

template <bool SwapBytes>
class Utf32EncodingImpl
{
public:
    static const auto encoding = SwapBytes ? Encoding::UTF_32_BE
                                           : Encoding::UTF_32_LE;
    typedef uint32_t CanonicalType;

    template <typename FwdIt>
    bool next(uint32_t& codePoint, FwdIt& it, FwdIt last)
    {
        switch (nextUtf32CodePoint<FwdIt, SwapBytes>(codePoint, it, last))
        {
            case DecoderResult::END_OF_STRING:
                return false;
            case DecoderResult::INCOMPLETE:
                throw std::logic_error("Incomplete character.");
            case DecoderResult::INVALID:
                throw std::logic_error("Invalid character.");
            default:
                break;
        }
        return true;
    }

    template <typename BiIt>
    bool prev(uint32_t& codePoint, BiIt first, BiIt& it)
    {
        switch (prevUtf32CodePoint<BiIt, SwapBytes>(codePoint, first, it))
        {
            case DecoderResult::END_OF_STRING:
                return false;
            case DecoderResult::INCOMPLETE:
                throw std::logic_error("Incomplete character.");
            case DecoderResult::INVALID:
                throw std::logic_error("Invalid character.");
            default:
                break;
        }
        return true;
    }

    template <typename FwdIt>
    bool skipNext(FwdIt& it, FwdIt last)
    {
        return skipNextUtf32CodePoint<FwdIt>(it, last);
    }

    template <typename BiIt>
    bool skipPrev(BiIt first, BiIt& it)
    {
        return skipPrevUtf32CodePoint<BiIt>(first, it);
    }

    template <typename OutIt>
    OutIt encode(OutIt dst, uint32_t codePoint)
    {
        return addUtf32<SwapBytes>(dst, codePoint);
    }

    template <typename OutIt>
    OutIt encodeAsBytes(OutIt dst, uint32_t codePoint)
    {
        return addUtf32AsBytes<SwapBytes>(dst, codePoint);
    }
};

typedef Utf32EncodingImpl<false> Utf32Encoding;
typedef Utf32EncodingImpl<Utilities::IsBigEndian> Utf32LEEncoding;
typedef Utf32EncodingImpl<Utilities::IsLittleEndian> Utf32BEEncoding;

}}