//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 06.11.2015
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf8Encoder.hpp"

#include <iterator>
#include "../Utf8/EncodeUtf8.hpp"

namespace Ystring { namespace Conversion {

    Utf8Encoder::Utf8Encoder()
        : AbstractEncoder(Encoding::UTF_8)
    {}

    void Utf8Encoder::doEncode(const char32_t*& srcBeg,
                               const char32_t* srcEnd,
                               std::string& dst)
    {
        auto out = back_inserter(dst);
        while (srcBeg != srcEnd)
        {
            Utf8::addUtf8(out, *srcBeg);
            ++srcBeg;
        }
    }

}}