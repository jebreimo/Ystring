//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 27.07.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Cp437.hpp"

#include <vector>

namespace Ystring { namespace CodePage {

const std::pair<uint32_t, uint8_t> Cp437SpecialChars[] = {
        {0x263A, 1},
        {0x263B, 2},
        {0x2665, 3},
        {0x2666, 4},
        {0x2663, 5},
        {0x2660, 6},
        {0x2022, 7},
        {0x25D8, 8},
        {0x25CB, 9},
        {0x25D9, 10},
        {0x2642, 11},
        {0x2640, 12},
        {0x266A, 13},
        {0x266B, 14},
        {0x263C, 15},
        {0x25BA, 16},
        {0x25C4, 17},
        {0x2195, 18},
        {0x203C, 19},
        {0x00B6, 20},
        {0x00A7, 21},
        {0x25AC, 22},
        {0x21A8, 23},
        {0x2191, 24},
        {0x2193, 25},
        {0x2192, 26},
        {0x2190, 27},
        {0x221F, 28},
        {0x2194, 29},
        {0x25B2, 30},
        {0x25BC, 31},
        {0x2302, 127},
        {0x00C7, 128},
        {0x00FC, 129},
        {0x00E9, 130},
        {0x00E2, 131},
        {0x00E4, 132},
        {0x00E0, 133},
        {0x00E5, 134},
        {0x00E7, 135},
        {0x00EA, 136},
        {0x00EB, 137},
        {0x00E8, 138},
        {0x00EF, 139},
        {0x00EE, 140},
        {0x00EC, 141},
        {0x00C4, 142},
        {0x00C5, 143},
        {0x00C9, 144},
        {0x00E6, 145},
        {0x00C6, 146},
        {0x00F4, 147},
        {0x00F6, 148},
        {0x00F2, 149},
        {0x00FB, 150},
        {0x00F9, 151},
        {0x00FF, 152},
        {0x00D6, 153},
        {0x00DC, 154},
        {0x00A2, 155},
        {0x00A3, 156},
        {0x00A5, 157},
        {0x20A7, 158},
        {0x0192, 159},
        {0x00E1, 160},
        {0x00ED, 161},
        {0x00F3, 162},
        {0x00FA, 163},
        {0x00F1, 164},
        {0x00D1, 165},
        {0x00AA, 166},
        {0x00BA, 167},
        {0x00BF, 168},
        {0x2310, 169},
        {0x00AC, 170},
        {0x00BD, 171},
        {0x00BC, 172},
        {0x00A1, 173},
        {0x00AB, 174},
        {0x00BB, 175},
        {0x2591, 176},
        {0x2592, 177},
        {0x2593, 178},
        {0x2502, 179},
        {0x2524, 180},
        {0x2561, 181},
        {0x2562, 182},
        {0x2556, 183},
        {0x2555, 184},
        {0x2563, 185},
        {0x2551, 186},
        {0x2557, 187},
        {0x255D, 188},
        {0x255C, 189},
        {0x255B, 190},
        {0x2510, 191},
        {0x2514, 192},
        {0x2534, 193},
        {0x252C, 194},
        {0x251C, 195},
        {0x2500, 196},
        {0x253C, 197},
        {0x255E, 198},
        {0x255F, 199},
        {0x255A, 200},
        {0x2554, 201},
        {0x2569, 202},
        {0x2566, 203},
        {0x2560, 204},
        {0x2550, 205},
        {0x256C, 206},
        {0x2567, 207},
        {0x2568, 208},
        {0x2564, 209},
        {0x2565, 210},
        {0x2559, 211},
        {0x2558, 212},
        {0x2552, 213},
        {0x2553, 214},
        {0x256B, 215},
        {0x256A, 216},
        {0x2518, 217},
        {0x250C, 218},
        {0x2588, 219},
        {0x2584, 220},
        {0x258C, 221},
        {0x2590, 222},
        {0x2580, 223},
        {0x03B1, 224},
        {0x00DF, 225},
        {0x0393, 226},
        {0x03C0, 227},
        {0x03A3, 228},
        {0x03C3, 229},
        {0x00B5, 230},
        {0x03C4, 231},
        {0x03A6, 232},
        {0x0398, 233},
        {0x03A9, 234},
        {0x03B4, 235},
        {0x221E, 236},
        {0x03C6, 237},
        {0x03B5, 238},
        {0x2229, 239},
        {0x2261, 240},
        {0x00B1, 241},
        {0x2265, 242},
        {0x2264, 243},
        {0x2320, 244},
        {0x2321, 245},
        {0x00F7, 246},
        {0x2248, 247},
        {0x00B0, 248},
        {0x2219, 249},
        {0x00B7, 250},
        {0x221A, 251},
        {0x207F, 252},
        {0x00B2, 253},
        {0x25A0, 254},
        {0x00A0, 255}
};

const uint32_t* cp437ToUnicode()
{
    static std::vector<uint32_t> table;
    if (table.empty())
    {
        table.resize(256);
        for (uint32_t i = 0; i < 256; ++i)
            table[i] = i;
        for (auto it = std::begin(Cp437SpecialChars);
             it != std::end(Cp437SpecialChars); ++it)
            table[it->second] = it->first;
    }
    return &table[0];
}

std::pair<const CodePointMapping*, const CodePointMapping*>
    unicodeToCp437()
{
    return std::make_pair(std::begin(Cp437SpecialChars),
                          std::end(Cp437SpecialChars));
}

CodePage makeCp437()
{
    auto to = cp437ToUnicode();
    auto from = unicodeToCp437();
    return CodePage(to, from.first, from.second, Encoding::CP_437);
}

}}
