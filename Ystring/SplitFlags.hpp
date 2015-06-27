//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 18.06.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "FindFlags.hpp"

namespace Ystring {

struct SplitFlags
{
    enum Type
    {
        DEFAULTS = 0,
        CASE_INSENSITIVE = 1,
        IGNORE_EMPTY = 2,
        IGNORE_REMAINDER = 4
    };

    typedef unsigned Flags;

    static bool isCaseInsensitive(Flags flags)
    {
        return (flags & CASE_INSENSITIVE) != 0;
    }

    static bool ignoreEmpty(Flags flags)
    {
        return (flags & IGNORE_EMPTY) != 0;
    }

    static bool ignoreRemainder(Flags flags)
    {
        return (flags & IGNORE_REMAINDER) != 0;
    }

    static FindFlags_t toFindFlags(Flags flags)
    {
        return isCaseInsensitive(flags)
                ? FindFlags::CASE_INSENSITIVE
                : FindFlags::DEFAULTS;
    }
};

typedef SplitFlags::Flags SplitFlags_t;

}
