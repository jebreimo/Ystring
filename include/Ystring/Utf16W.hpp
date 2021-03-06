//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-29.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

/** @file
  * @brief Top-level include file for the std::wstring as UTF-16
  *     function library
  */

static_assert(sizeof(wchar_t) == 2,
              "wchar_t isn't 16-bit and isn't suited for UTF-16.");

#include "Utf/Utf16WString.hpp"
