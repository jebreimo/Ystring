//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-16
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "Range.hpp"
#include "ForwardDecoder.hpp"

namespace Ystring { namespace EncodedString
{

    inline bool isMandatoryEscape(char32_t c)
    {
        return c < 32 || c == '"' || c == '\\' || (127 <= c && c < 160);
    }

    inline bool isNonAsciiEscape(char32_t c)
    {
        return c < 32 || c == '"' || c == '\\' || 127 <= c;
    }

    template <typename Appender, typename It, typename Escaper>
    void appendEscaped(Appender dst, Generic::Range<It> src,
                       bool (*isEscapable)(char32_t), Escaper escaper)
    {
        typedef typename Generic::Range<It>::ValueType Char;
        typedef typename std::make_unsigned<Char>::type UChar;

        auto first = src.begin();
        auto predicate = [&](Char c){return isEscapable(UChar(c));};
        auto last = std::find_if(first, src.end(), predicate);
        while (last != src.end())
        {
            dst.append(Generic::makeRange(first, last));
            escaper.escape(dst, (UChar)*last);
            first = ++last;
            last = std::find_if(first, src.end(), predicate);
        }
        dst.append(Generic::makeRange(first, src.end()));
    }

    template <typename Appender, typename It, typename Enc, typename Escaper>
    void appendEscaped(Appender dst, ForwardDecoder<It, Enc> src,
                       bool (*isEscapable)(char32_t), Escaper escaper)
    {
        auto first = src.begin();
        while (advanceUntil(src, isEscapable))
        {
            dst.append(Generic::makeRange(first, src.begin()));
            char32_t c;
            src.next(c);
            escaper.escape(dst, c);
            first = src.begin();
        }
        dst.append(Generic::makeRange(first, src.begin()));
    }

    template <typename It>
    bool hasUnescapedCharacters(Generic::Range<It> src,
                                bool (*isEscapable)(char32_t))
    {
        typedef typename Generic::Range<It>::ValueType Char;
        typedef typename std::make_unsigned<Char>::type UChar;
        return src.end() != std::find_if(
                src.begin(), src.end(),
                [&](Char c){return isEscapable(UChar(c));});
    }

    template <typename It, typename Enc>
    bool hasUnescapedCharacters(ForwardDecoder<It, Enc> src,
                                bool (*isEscapable)(char32_t))
    {
        return advanceUntil(src, isEscapable);
    }

}}
