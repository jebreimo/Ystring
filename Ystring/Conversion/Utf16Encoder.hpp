//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-08
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "AbstractEncoder.hpp"
#include "../Utf16/EncodeUtf16.hpp"

namespace Ystring { namespace Conversion {

    template<bool SwapBytes>
    class Utf16Encoder : public AbstractEncoder
    {
    public:
        Utf16Encoder()
            : AbstractEncoder(IsBigEndian == SwapBytes
                              ? Encoding::UTF_16_LE
                              : Encoding::UTF_16_BE)
        {}

    protected:
        void doEncode(const char32_t*& srcBeg, const char32_t* srcEnd,
                      std::string& dst)
        {
            auto out = back_inserter(dst);
            while (srcBeg != srcEnd)
            {
                Utf16::addUtf16LE(out, *srcBeg);
                ++srcBeg;
            }
        }

        void doEncode(const char32_t*& srcBeg, const char32_t* srcEnd,
                      std::u16string& dst)
        {
            auto out = back_inserter(dst);
            while (srcBeg != srcEnd)
            {
                Utf16::addUtf16LE(out, *srcBeg);
                ++srcBeg;
            }
        }
    };


    typedef Utf16Encoder<IsLittleEndian> Utf16BEEncoder;
    typedef Utf16Encoder<IsBigEndian> Utf16LEEncoder;

}}