//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-21
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "CodePage.hpp"
#include "../YstringException.hpp"
#include "../Utilities/KeyFunctionAlgorithms.hpp"
#include "Cp437.hpp"
#include "Iso8859_1.hpp"
#include "Iso8859_15.hpp"
#include "Windows1252.hpp"

namespace Ystring { namespace CodePage
{
    CodePage::CodePage(Encoding_t encoding)
        : m_Encoding(encoding),
          m_FirstSpecialChar(256)
    {}

    CodePage::CodePage(const std::pair<uint32_t, uint32_t>* fromCodePoint,
                       const uint32_t* fromChar,
                       uint16_t firstSpecialChar,
                       Encoding_t encoding)
        : m_FromCodePoint(fromCodePoint),
          m_FromChar(fromChar),
          m_Encoding(encoding),
          m_FirstSpecialChar(firstSpecialChar)
    {}

    uint32_t CodePage::toCodePoint(char c) const
    {
        auto uc = uint8_t(c);
        if (uc < m_FirstSpecialChar)
            return uc;
        return m_FromChar[uc - m_FirstSpecialChar];
    }

    uint32_t CodePage::fromCodePoint(uint32_t c) const
    {
        if (c < m_FirstSpecialChar)
            return c;
        auto n = 256u - m_FirstSpecialChar;
        auto it = Utilities::binaryFind(
                m_FromCodePoint, m_FromCodePoint + n, c,
                [](const std::pair<uint32_t, char>& p) { return p.first; });
        if (it != m_FromCodePoint + n)
            return it->second;
        return INVALID_CHAR;
    }

    Encoding_t CodePage::encoding() const
    {
        return m_Encoding;
    }

    CodePage makeCodePage(Encoding_t encoding)
    {
        switch (encoding)
        {
        case Encoding::ISO_8859_1:
            return makeIso8859_1();
        case Encoding::ISO_8859_15:
            return makeIso8859_15();
        case Encoding::WINDOWS_1252:
            return makeWindows1252();
        case Encoding::CP_437:
            return makeCp437();
        default:
            break;
        }
        YSTRING_THROW("Unsupported code page encoding.");
    }
}}
