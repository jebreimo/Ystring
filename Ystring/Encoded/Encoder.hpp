//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 05.06.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <stdint.h>

namespace Ystring { namespace Encoded {

template <typename OutIt, typename Enc>
class Encoder
{
public:
    typedef OutIt Iterator;
    typedef Enc Encoding;

    Encoder(OutIt dst, Encoding encoding)
        : m_Destination(dst),
          m_Encoding(encoding)
    {}

    void encode(uint32_t codePoint)
    {
        m_Encoding.encode(m_Destination, codePoint);
    }

    Encoding getEncoding() const
    {
        return m_Encoding;
    }

    OutIt getIterator() const
    {
        return m_Destination;
    }
private:
    OutIt m_Destination;
    Encoding m_Encoding;
};

template <typename OutIt, typename Enc>
Encoder<OutIt, Enc> makeEncoder(OutIt dst, Enc encoding)
{
    return Encoder<OutIt, Enc>(dst, encoding);
}

}}