//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-21.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <stdexcept>
#include <string>
#include "../Encoding.hpp"
#include "../YstringException.hpp"
#include "CodePage.hpp"

namespace Ystring { namespace CodePage
{
    template <Encoding_t Encoding>
    class CodePageEncoding
    {
    public:
        static const Encoding_t encoding = Encoding;
        typedef char CanonicalType;

        CodePageEncoding()
            : m_CodePage(makeCodePage(encoding))
        {}

        CodePageEncoding(const CodePage& codePage)
            : m_CodePage(codePage)
        {}

        template<typename FwdIt>
        bool next(FwdIt& it, FwdIt last)
        {
            if (it == last)
                return false;
            ++it;
            return true;
        }

        template <typename FwdIt>
        bool next(uint32_t& codePoint, FwdIt& it, FwdIt last)
        {
            if (it == last)
                return false;
            codePoint = m_CodePage.toCodePoint(uint8_t(*it));
            ++it;
            return true;
        }

        template <typename FwdIt>
        bool skipNext(FwdIt& it, FwdIt last)
        {
            if (it == last)
                return false;
            ++it;
            return true;
        }

        template <typename BiIt>
        bool prev(uint32_t& codePoint, BiIt first, BiIt& it)
        {
            if (it == first)
                return false;
            --it;
            codePoint = m_CodePage.toCodePoint(*it);
            return true;
        }

        template <typename BiIt>
        bool skipPrev(BiIt first, BiIt& it)
        {
            if (it == first)
                return false;
            --it;
            return true;
        }

        template <typename OutIt>
        OutIt encode(OutIt dst, uint32_t codePoint)
        {
            return encodeAsBytes(dst, codePoint);
        }

        template <typename OutIt>
        OutIt encodeAsBytes(OutIt dst, uint32_t codePoint)
        {
            auto chr = m_CodePage.fromCodePoint(codePoint);
            if (chr == INVALID_CHAR)
                YSTRING_THROW(
                        "Encoding " + std::to_string(int64_t(encoding)) +
                        " doesn't support code point " +
                        std::to_string(int64_t(codePoint)));
            *dst = char(chr);
            return ++dst;
        }
    private:
        CodePage m_CodePage;
    };

    typedef CodePageEncoding<Encoding::IBM_437> Ibm437Encoding;
    typedef CodePageEncoding<Encoding::IBM_850> Ibm850Encoding;
    typedef CodePageEncoding<Encoding::LATIN_1> Latin1Encoding;
    typedef CodePageEncoding<Encoding::LATIN_5> Latin5Encoding;
    typedef CodePageEncoding<Encoding::LATIN_6> Latin6Encoding;
    typedef CodePageEncoding<Encoding::LATIN_9> Latin9Encoding;
    typedef CodePageEncoding<Encoding::WINDOWS_1250> Windows1250Encoding;
    typedef CodePageEncoding<Encoding::WINDOWS_1252> Windows1252Encoding;
}}
