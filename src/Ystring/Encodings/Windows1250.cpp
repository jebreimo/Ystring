//****************************************************************************
// Copyright © 2016 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2016-01-11.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Windows1250.hpp"

#include "CodePageFactory.hpp"

namespace Ystring { namespace Encodings
{
    namespace
    {
        typedef std::pair<uint8_t, char32_t> P;
        const P SpecialChars[] = {
                P(0x80, 0x20AC), P(0x82, 0x201A), P(0x84, 0x201E),
                P(0x85, 0x2026), P(0x86, 0x2020), P(0x87, 0x2021),
                P(0x89, 0x2030), P(0x8A, 0x0160), P(0x8B, 0x2039),
                P(0x8C, 0x015A), P(0x8D, 0x0164), P(0x8E, 0x017D),
                P(0x8F, 0x0179), P(0x91, 0x2018), P(0x92, 0x2019),
                P(0x93, 0x201C), P(0x94, 0x201D), P(0x95, 0x2022),
                P(0x96, 0x2013), P(0x97, 0x2014), P(0x99, 0x2122),
                P(0x9A, 0x0161), P(0x9B, 0x203A), P(0x9C, 0x015B),
                P(0x9D, 0x0165), P(0x9E, 0x017E), P(0x9F, 0x017A),
                P(0xA1, 0x02C7), P(0xA2, 0x02D8), P(0xA3, 0x0141),
                P(0xA5, 0x0104), P(0xAA, 0x015E), P(0xAF, 0x017B),
                P(0xB2, 0x02DB), P(0xB3, 0x0142), P(0xB9, 0x0105),
                P(0xBA, 0x015F), P(0xBC, 0x013D), P(0xBD, 0x02DD),
                P(0xBE, 0x013E), P(0xBF, 0x017C), P(0xC0, 0x0154),
                P(0xC3, 0x0102), P(0xC5, 0x0139), P(0xC6, 0x0106),
                P(0xC8, 0x010C), P(0xCA, 0x0118), P(0xCC, 0x011A),
                P(0xCF, 0x010E), P(0xD0, 0x0110), P(0xD1, 0x0143),
                P(0xD2, 0x0147), P(0xD5, 0x0150), P(0xD8, 0x0158),
                P(0xD9, 0x016E), P(0xDB, 0x0170), P(0xDE, 0x0162),
                P(0xE0, 0x0155), P(0xE3, 0x0103), P(0xE5, 0x013A),
                P(0xE6, 0x0107), P(0xE8, 0x010D), P(0xEA, 0x0119),
                P(0xEC, 0x011B), P(0xEF, 0x010F), P(0xF0, 0x0111),
                P(0xF1, 0x0144), P(0xF2, 0x0148), P(0xF5, 0x0151),
                P(0xF8, 0x0159), P(0xF9, 0x016F), P(0xFB, 0x0171),
                P(0xFE, 0x0163), P(0xFF, 0x02D9)
        };

        CodePageFactory factory(std::begin(SpecialChars),
                                std::end(SpecialChars),
                                Encoding::WINDOWS_1250);
    }

    CodePage makeWindows1250()
    {
        return factory.makeCodePage();
    }
}}