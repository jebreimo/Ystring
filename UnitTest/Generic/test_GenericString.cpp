//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 04.06.15
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Generic/GenericString.hpp"
#include "Ystring/Utf8/Utf8Encoding.hpp"
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace Ystring;
using Generic::makeEncodedRange;
using Utilities::makeRange;
using Utf8::Utf8Encoding;

void test_find_different_containers_same_encoding()
{
    std::string str("Abraham Brorson");
    char cmp[] = "m B";
    auto match = Generic::find(makeRange(str), makeRange(cmp),
                               Utf8Encoding());
    JT_EQUAL(std::distance(str.begin(), match.begin()), 6);
    JT_ASSERT(match.end() == str.begin() + 9);
}

void test_sizeOfLower()
{
    std::string str("\xC8\xBA");
    JT_EQUAL(Generic::sizeOfLower(makeRange(str), Utf8Encoding()), 3);
}

JT_SUBTEST("Generic",
           test_find_different_containers_same_encoding,
           test_sizeOfLower);

}
