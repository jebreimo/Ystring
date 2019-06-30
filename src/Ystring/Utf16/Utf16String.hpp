//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-11.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include "Ystring/Encoding.hpp"
#include "Ystring/EscapeType.hpp"
#include "Ystring/FindFlags.hpp"
#include "Ystring/PlatformDetails.hpp"
#include "Ystring/SplitFlags.hpp"
#include "Ystring/YstringException.hpp"

/** @file
  * @brief The function library for u16strings.
  */

namespace Ystring { namespace Utf16
{
    /** @brief The result of certain find-functions that accept mutable
      *     strings or their iterators.
      */
    typedef std::pair<std::u16string::iterator, std::u16string::iterator>
            StringIteratorPair;

    /** @brief The result of certain find-functions that accept immutable
      *     or their strings.
      */
    typedef std::pair<std::u16string::const_iterator,
                      std::u16string::const_iterator>
            StringConstIteratorPair;

    /** @brief The Unicode replacement character.
      *
      * This is a copy of the constant found in UnicodeChars.hpp. It's
      * duplicated here to avoid unnecessary conflicts between constant names
      * in that file and macros defined in Windows.h.
      */
    static const char32_t REPLACEMENT_CHARACTER = 0xFFFDu;

    /** @brief Adds @a codePoint encoded as UTF-16 to the end of @a str.
      */
    YSTRING_API std::u16string& append(std::u16string& str, char32_t chr);

    /** @brief Compares @a str and @a cmp, ignoring any differences in
      *     letter casing.
      *
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters (the decomposed character is
      *     typically the "lesser" one).
      * @returns @arg < 0 if @a str is less than @a cmp
      *          @arg 0 if @a str is equal to @a cmp
      *          @arg > 0 if @a str is greater than @a cmp
      * @throw YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API int32_t caseInsensitiveCompare(const std::u16string& str,
                                               const std::u16string& cmp);

    /** @brief Returns true if the upper case versions of @a str and @a cmp
      *     are equal.
      *
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters (the decomposed character is
      *     typically the "lesser" one).
      * @throw YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API bool caseInsensitiveEqual(const std::u16string& str,
                                          const std::u16string& cmp);

    /** @brief Returns true if the upper case version of @a str is less
      *     than @a cmp.
      *
      * Only a quick comparison of code point values are performed. This
      * function should not be used to sort strings in alphabetical order as
      * what is alphabetical order varies between languages and cultures.
      * @throw YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API bool caseInsensitiveLess(const std::u16string& str,
                                         const std::u16string& cmp);

    /** @brief Returns true if @a str contains code point @a chr.
      * @throw YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API bool contains(const std::u16string& str, char32_t chr);

    /** @brief Returns the number of characters in @a str.
      *
      * @note A composed character can consist of multiple code points.
      * @return the number of characters.
      * @throw YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API size_t countCharacters(const std::u16string& str);

    /** @brief Returns the number of characters between @a first and @a last.
      *
      * @note A composed character can consist of multiple code points.
      * @return the number of characters.
      * @throw YstringException if str contains an invalid UTF-8 code point.
      */
    YSTRING_API size_t countCharacters(std::string::const_iterator first,
                                       std::string::const_iterator last);

    /** @brief Returns the number of code points in @a str.
      *
      * @note A composed character can consist of multiple code points.
      * @return the number of code points.
      * @throw YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API size_t countCodePoints(const std::u16string& str);

    /** @brief Returns true if @a str ends with @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      */
    YSTRING_API bool endsWith(const std::u16string& str,
                              const std::u16string& cmp,
                              FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns a copy of @a str where control character etc. have
      *     been escaped.
      *
      * When escaping with backslashes the function does not use octal codes,
      * not even \\0 for value 0 as these are too easy to misinterpret.
      */
    YSTRING_API std::u16string escape(
            const std::u16string& str,
            EscapeType_t type = EscapeType::BACKSLASH);

    /** @brief Returns the first substring in @a str that matches @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      */
    YSTRING_API StringIteratorPair findFirst(
            std::u16string& str,
            const std::u16string& cmp,
            FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns the first substring in @a str that matches @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      * @return A pair of iterators where first points to the start and
      *     second points to the end of the substring within @a str.
      *     If the substring can't be found both point to @a str.end().
      */
    YSTRING_API StringConstIteratorPair findFirst(
            const std::u16string& str,
            const std::u16string& cmp,
            FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns the first substring in the range from @a first
      *     to @a last that matches @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      * @return A pair of iterators where first points to the start and
      *     second points to the end of the substring within @a str.
      *     If the substring can't be found both point to @a str.end().
      */
    YSTRING_API StringIteratorPair findFirst(
            std::u16string::iterator first,
            std::u16string::iterator last,
            const std::u16string& cmp,
            FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns the first substring in the range from @a first
      *     to @a last that matches @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      * @return A pair of iterators where first points to the start and
      *     second points to the end of the substring within @a str.
      *     If the substring can't be found both point to @a str.end().
      */
    YSTRING_API StringConstIteratorPair findFirst(
            std::u16string::const_iterator first,
            std::u16string::const_iterator last,
            const std::u16string& cmp,
            FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns the first substring in @a str that constitutes
      *     a newline.
      *
      * The following characters are treated as newline characters:
      *   - \\n Unix
      *   - \\r Old MacOS
      *   - \\r\\n Windows
      *   - \\f Form feed
      *   - \\v Vertical tab
      *   - NEXT LINE (code point 133)
      *   - LINE SEPARATOR (code point 8232)
      *   - PARAGRAPH SEPARATOR (code point 8233)
      */
    YSTRING_API StringIteratorPair findFirstNewline(std::u16string& str);

    /** @brief Returns the first substring in @a str that constitutes
      *     a newline.
      *
      * The following characters are treated as newline characters:
      *   - \\n Unix
      *   - \\r Old MacOS
      *   - \\r\\n Windows
      *   - \\f Form feed
      *   - \\v Vertical tab
      *   - NEXT LINE (code point 133)
      *   - LINE SEPARATOR (code point 8232)
      *   - PARAGRAPH SEPARATOR (code point 8233)
      */
    YSTRING_API StringConstIteratorPair findFirstNewline(
            const std::u16string& str);

    /** @brief Returns the first substring in the range from @a first
      *     to @a last that constitutes a newline.
      *
      * The following characters are treated as newline characters:
      *   - \\n Unix
      *   - \\r Old MacOS
      *   - \\r\\n Windows
      *   - \\f Form feed
      *   - \\v Vertical tab
      *   - NEXT LINE (code point 133)
      *   - LINE SEPARATOR (code point 8232)
      *   - PARAGRAPH SEPARATOR (code point 8233)
      */
    YSTRING_API StringIteratorPair findFirstNewline(
            std::u16string::iterator first,
            std::u16string::iterator last);

    /** @brief Returns the first substring in the range from @a first
      *     to @a last that constitutes a newline.
      *
      * The following characters are treated as newline characters:
      *   - \\n Unix
      *   - \\r Old MacOS
      *   - \\r\\n Windows
      *   - \\f Form feed
      *   - \\v Vertical tab
      *   - NEXT LINE (code point 133)
      *   - LINE SEPARATOR (code point 8232)
      *   - PARAGRAPH SEPARATOR (code point 8233)
      */
    YSTRING_API StringConstIteratorPair findFirstNewline(
            std::u16string::const_iterator first,
            std::u16string::const_iterator last);

    /** @brief Returns the last substring in @a str that matches @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      * @return A pair of iterators where first points to the start and
      *     second points to the end of the substring within @a str.
      *     If the substring can't be found both point to @a str.begin().
      */
    YSTRING_API StringIteratorPair findLast(
            std::wstring& str,
            const std::wstring& cmp,
            FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns the last substring in @a str that matches @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      * @return A pair of iterators where first points to the start and
      *     second points to the end of the substring within @a str.
      *     If the substring can't be found both point to @a str.begin().
      */
    YSTRING_API StringConstIteratorPair findLast(
            const std::u16string& str,
            const std::u16string& cmp,
            FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns the last substring in the range from @a first
      *     to @a last that matches @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      * @return A pair of iterators where first points to the start and
      *     second points to the end of the substring within @a str.
      *     If the substring can't be found both point to @a str.begin().
      */
    YSTRING_API StringIteratorPair findLast(
          std::u16string::iterator first,
          std::u16string::iterator last,
          const std::u16string& cmp,
          FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns the last substring in the range from @a first
      *     to @a last that matches @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      * @return A pair of iterators where first points to the start and
      *     second points to the end of the substring within @a str.
      *     If the substring can't be found both point to @a str.begin().
      */
    YSTRING_API StringConstIteratorPair findLast(
          std::u16string::const_iterator first,
          std::u16string::const_iterator last,
          const std::u16string& cmp,
          FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns the last substring in @a str that constitutes
      *     a newline.
      *
      * The following characters are treated as newline characters:
      *   - \\n Unix
      *   - \\r Old MacOS
      *   - \\r\\n Windows
      *   - \\f Form feed
      *   - \\v Vertical tab
      *   - NEXT LINE (code point 133)
      *   - LINE SEPARATOR (code point 8232)
      *   - PARAGRAPH SEPARATOR (code point 8233)
      */
    YSTRING_API StringIteratorPair findLastNewline(std::u16string& str);

    /** @brief Returns the last substring in @a str that constitutes
      *     a newline.
      *
      * The following characters are treated as newline characters:
      *   - \\n Unix
      *   - \\r Old MacOS
      *   - \\r\\n Windows
      *   - \\f Form feed
      *   - \\v Vertical tab
      *   - NEXT LINE (code point 133)
      *   - LINE SEPARATOR (code point 8232)
      *   - PARAGRAPH SEPARATOR (code point 8233)
      */
    YSTRING_API StringConstIteratorPair findLastNewline(
            const std::u16string& str);

    /** @brief Returns the first substring in the range from @a first
      *     to @a last that constitutes a newline.
      *
      * The following characters are treated as newline characters:
      *   - \\n Unix
      *   - \\r Old MacOS
      *   - \\r\\n Windows
      *   - \\f Form feed
      *   - \\v Vertical tab
      *   - NEXT LINE (code point 133)
      *   - LINE SEPARATOR (code point 8232)
      *   - PARAGRAPH SEPARATOR (code point 8233)
      */
    YSTRING_API StringIteratorPair findLastNewline(
            std::u16string::iterator first,
            std::u16string::iterator last);

    /** @brief Returns the first substring in the range from @a first
      *     to @a last that constitutes a newline.
      *
      * The following characters are treated as newline characters:
      *   - \\n Unix
      *   - \\r Old MacOS
      *   - \\r\\n Windows
      *   - \\f Form feed
      *   - \\v Vertical tab
      *   - NEXT LINE (code point 133)
      *   - LINE SEPARATOR (code point 8232)
      *   - PARAGRAPH SEPARATOR (code point 8233)
      */
    YSTRING_API StringConstIteratorPair findLastNewline(
            std::u16string::const_iterator first,
            std::u16string::const_iterator last);

    /** @brief Return code point at position @a pos in @a str.
      *
      * The first code point has position 0.
      * If @a pos is negative, code points are counted from the end of @a str
      *  where the last character in @a str is at position -1.
      */
    YSTRING_API char32_t getCodePoint(const std::u16string& str,
                                      ptrdiff_t pos);

    /** @brief Returns true if @a str has characters that will be unescaped
      *     if unescape is called with the same parameters.
      */
    YSTRING_API bool hasEscapedCharacters(
            const std::string& str,
            EscapeType_t type = EscapeType::BACKSLASH);

    /** @brief Returns true if @a str has characters that will be escaped
      *     if escape is called with the same parameters.
      */
    YSTRING_API bool hasUnescapedCharacters(
            const std::string& str,
            EscapeType_t type = EscapeType::BACKSLASH);

    /** @brief Inserts string @a sub into @a str at position @a pos.
      *
      * @param pos The insert position in complete characters (i.e. not bytes,
      *     not even code points if the string has decomposed characters) from
      *     the start of the string. If @a pos is negative it's from the end
      *     of the string instead.
      * @throws YstringException if @a str isn't a valid UTF-16 string.
      */
    YSTRING_API std::u16string insert(
            const std::u16string& str,
            ptrdiff_t pos,
            const std::u16string& sub);

    /** @brief Inserts character @a chr into @a str at position @a pos.
      *
      * @param pos The insert position in complete characters (i.e. not bytes,
      *     not even code points if the string has decomposed characters)
      *     from the start of the string. If @a pos is negative it's from the
      *     end of the string instead.
      * @throws YstringException if @a str isn't a valid UTF-16 string.
      */
    YSTRING_API std::u16string insert(
            const std::u16string& str,
            ptrdiff_t pos,
            char32_t chr);

    /** @brief Returns true if all characters in @a str are either
      *     letters or numbers.
      * @throws YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API bool isAlphaNumeric(const std::u16string& str);

    /** @brief Returns true if all characters in the range from @a first
      *     to @a last are either letters or numbers.
      * @throws YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API bool isAlphaNumeric(std::u16string::iterator first,
                                    std::u16string::iterator last);

    /** @brief Returns true if all characters in the range from @a first
      *     to @a last are either letters or numbers.
      * @throws YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API bool isAlphaNumeric(std::u16string::const_iterator first,
                                    std::u16string::const_iterator last);

    /** @brief Returns true if all characters in @a str are valid UTF-16.
      */
    YSTRING_API bool isValidUtf16(const std::u16string& str);

    /** @brief Returns the concatenation of the strings in @a strings
      *     delimited by @a delimiter.
      */
    YSTRING_API std::u16string join(
            const std::vector<std::u16string>& strings,
            const std::u16string& delimiter = std::u16string());

    /** @brief Returns the concatenation of the strings in @a strings
      *     delimited by @a delimiter.
      */
    YSTRING_API std::u16string join(
            const std::u16string* strings,
            size_t count,
            const std::u16string& delimiter = std::u16string());

    /** @brief Returns a lower case copy of @a str.
      */
    YSTRING_API std::u16string lower(const std::u16string& str);

    /** @brief Returns an iterator to the start of character number @a n
      *     starting at @a first.
      */
    YSTRING_API std::u16string::iterator nextCharacter(
            std::u16string::iterator& first,
            std::u16string::iterator& last,
            size_t n = 1);

    /** @brief Returns an iterator to the start of character number @a n
      *     starting at @a first.
      */
    YSTRING_API std::u16string::const_iterator nextCharacter(
            std::u16string::const_iterator& first,
            std::u16string::const_iterator& last,
            size_t n = 1);

    /** @brief Returns an iterator to the start of character number @a n
      *     from the start of string @a str.
      * @param n The number of complete characters (i.e. not bytes, not
      *     even code points if the string has decomposed characters) from the
      *     start of the string. If @a pos is negative it's from the end of
      *     the string instead.
      */
    YSTRING_API std::u16string::iterator nthCharacter(
            std::u16string& str,
            ptrdiff_t n);

    /** @brief Returns an iterator to the start of character number @a n
      *     from the start of string @a str.
      * @param n The number of complete characters (i.e. not bytes, not
      *     even code points if the string has decomposed characters) from the
      *     start of the string. If @a pos is negative it's from the end of
      *     the string instead.
      */
    YSTRING_API std::u16string::const_iterator nthCharacter(
            const std::u16string& str,
            ptrdiff_t n);

    /** @brief Returns an iterator to the start of character number @a n
      *     counting backwards from @a last.
      */
    YSTRING_API std::u16string::iterator prevCharacter(
            std::u16string::iterator& first,
            std::u16string::iterator& last,
            size_t n = 1);

    /** @brief Returns an iterator to the start of character number @a n
      *     counting backwards from @a last.
      */
    YSTRING_API std::u16string::const_iterator prevCharacter(
            std::u16string::const_iterator& first,
            std::u16string::const_iterator& last,
            size_t n = 1);

    /** @brief Returns a copy of @a str where instances of @a from are
      *     replaced with @a to.
      *
      * @param maxReplacements The maximum number of replacements that will be
      *     performed. All instances of @a from are replaced if the
      *     value is 0. If it is negative at most abs(maxReplacements) will be
      *     made, starting at the end of the string.
      */
    YSTRING_API std::u16string replace(
            const std::u16string& str,
            const std::u16string& from,
            const std::u16string& to,
            ptrdiff_t maxReplacements = 0,
            FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns a copy of @a str where the substring between @a start
      *     and @a end has been replaced with @a repl.
      */
    YSTRING_API std::u16string replace(
            const std::u16string& str,
            ptrdiff_t start,
            ptrdiff_t end,
            const std::u16string& repl);

    /** @brief Returns a copy of @a str with instances of @a from replaced
      *     with @a to.
      *
      * @param str The string operated on.
      * @param from The character to replace.
      * @param to The replacement.
      * @param maxReplacements The maximum number of replacements that will be
      *     performed. All instances of @a from are replaced if the
      *     value is 0. If it is negative at most abs(maxReplacements) will be
      *     made, starting at the end of the string.
      */
    YSTRING_API std::u16string replaceCodePoint(
            const std::u16string& s,
            char32_t from,
            char32_t to,
            ptrdiff_t maxReplacements = 0);

    /** @brief Returns a copy of @a str where all invalid code points have
      *     been replaced with @a chr.
      */
    YSTRING_API std::u16string replaceInvalidUtf16(
            const std::u16string& str,
            char32_t chr = REPLACEMENT_CHARACTER);

    /** @brief Replaces all invalid code points in @a str with @a chr.
      */
    YSTRING_API std::u16string& replaceInvalidUtf16InPlace(
            std::u16string& str,
            char16_t chr = REPLACEMENT_CHARACTER);

    /** @brief Returns a reversed copy of @a str.
      *
      * Characters with combining marks are left intact.
      */
    YSTRING_API std::u16string reverse(const std::u16string& str);

    /** @brief Splits @a str where it contains whitespace characters and
      *     returns a list of the parts.
      * @param maxSplits The maximum number of times @a str will be split.
      *     If the value is 0 @a str wil be split at every newline character.
      *     If the value is negative the splitting will start from the end of
      *     @a str, the result will have parts in reverse order (i.e. the last
      *     part is first, the second to last is second and so on).
      */
    YSTRING_API std::vector<std::u16string> split(
            const std::u16string& str,
            ptrdiff_t maxSplits = 0,
            SplitFlags_t flags = SplitFlags::IGNORE_EMPTY);

    /** @brief Splits @a str where it matches @a sep and returns a list of
      *     the parts.
      * @param maxSplits The maximum number of times @a str will be split.
      *     If the value is 0 @a str wil be split at every newline character.
      *     If the value is negative the splitting will start from the end of
      *     @a str, the result will have parts in reverse order (i.e. the last
      *     part is first, the second to last is second and so on).
      */
    YSTRING_API std::vector<std::u16string> split(
            const std::u16string& str,
            const std::u16string& sep,
            ptrdiff_t maxSplits = 0,
            SplitFlags_t flags = SplitFlags::DEFAULTS);

    /** @brief Splits @a str at characters that satisfy predicate and returns
      *     a list of the parts.
      * @param maxSplits The maximum number of times @a str will be split.
      *     If the value is 0 @a str wil be split at every newline character.
      *     If the value is negative the splitting will start from the end of
      *     @a str, the result will have parts in reverse order (i.e. the last
      *     part is first, the second to last is second and so on).
      */
    YSTRING_API std::vector<std::u16string> splitIf(
            const std::u16string& str,
            std::function<bool(char32_t)> predicate,
            ptrdiff_t maxSplits = 0,
            SplitFlags_t flags = SplitFlags::DEFAULTS);

    /** @brief Splits @a str at newline characters and returns a list
      *     of the parts.
      * @param maxSplits The maximum number of times @a str will be split.
      *     If the value is 0 @a str wil be split at every newline character.
      *     If the value is negative the splitting will start from the end of
      *     @a str, the result will have parts in reverse order (i.e. the last
      *     part is first, the second to last is second and so on).
      */
    YSTRING_API std::vector<std::u16string> splitLines(
            const std::u16string& str,
            ptrdiff_t maxSplits = 0,
            SplitFlags_t flags = SplitFlags::DEFAULTS);

    /** @brief Returns true if @a str starts with substring @a cmp.
      * @throw YstringException if @a str or @a cmp contain any invalid UTF-16
      *     code points.
      */
    YSTRING_API bool startsWith(const std::u16string& str,
                                const std::u16string& cmp,
                                FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Returns the substring of of @a str that starts at character
      *     number @a startIndex and ends at character number @a endIndex.
      * @param startIndex The start position in complete characters (i.e. not
      *     bytes, not even code points if the string has decomposed
      *     characters) from the start of the string. If @a startIndex is
      *     negative it's from the end of the string instead.
      * @param endIndex The end position in complete characters (i.e. not
      *     bytes, not even code points if the string has decomposed
      *     characters) from the start of the string. If @a startIndex is
      *     negative it's from the end of the string instead.
      * @throw YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API std::u16string substring(
            const std::u16string& str,
            ptrdiff_t startIndex,
            ptrdiff_t endIndex = PTRDIFF_MAX);

    /** @brief Returns a title-cased copy of @a str.
      */
    YSTRING_API std::u16string title(const std::u16string& str);

    /** @brief Returns a UTF-16 encoded string representing @a chr
      */
    YSTRING_API std::u16string toUtf16(char32_t chr);

    /** @brief Returns an UTF-16 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::u16string toUtf16(
            const std::string& str,
            Encoding_t encoding);

    /** @brief Returns an UTF-16 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::u16string toUtf16(
            const char* str, size_t length,
            Encoding_t encoding);

    /** @brief Returns an UTF-16 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::u16string toUtf16(
            const wchar_t* str, size_t length,
            Encoding_t encoding);

    /** @brief Returns an UTF-16 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::u16string toUtf16(
            const char16_t* str, size_t length,
            Encoding_t encoding);

    /** @brief Returns an UTF-16 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::u16string toUtf16(
            const char32_t* str, size_t length,
            Encoding_t encoding);

    /** @brief Returns an UTF-16 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::u16string toUtf16(
            const std::u16string& str,
            Encoding_t encoding = Encoding::UTF_16);

    /** @brief Returns an UTF-16 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::u16string toUtf16(
            const std::u32string& str,
            Encoding_t encoding = Encoding::UTF_32);

    /** @brief Returns an UTF-16 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::u16string toUtf16(
            const std::wstring& str,
            Encoding_t encoding);

    /** @brief Returns a copy of @a str where all whitespace characters at the
      *     start and end of the string have been removed.
      */
    YSTRING_API std::u16string trim(const std::u16string& str);

    /** @brief Returns a copy of @a str where all characters satisfying
      *     @a predicate at the start and end of the string have been removed.
      */
    YSTRING_API std::u16string trim(
            const std::u16string& str,
            std::function<bool(char32_t)> predicate);

    /** @brief Returns a copy of @a str where all whitespace characters at the
      *     end of the string have been removed.
      */
    YSTRING_API std::u16string trimEnd(const std::u16string& str);

    /** @brief Returns a copy of @a str where all characters satisfying
      *     @a predicate at the end of the string have been removed.
      */
    YSTRING_API std::u16string trimEnd(
            const std::u16string& str,
            std::function<bool(char32_t)> predicate);

    /** @brief Returns a copy of @a str where all whitespace characters at the
      *     start of the string have been removed.
      */
    YSTRING_API std::u16string trimStart(const std::u16string& str);

    /** @brief Returns a copy of @a str where all characters that satisfy
     *      @a predicate at the start of the string have been removed.
      */
    YSTRING_API std::u16string trimStart(
            const std::u16string& str,
            std::function<bool(char32_t)> predicate);

    /** @brief Returns a copy of @a str where all escape sequences have been
      *     translated to the characters they represent.
      * @throws YstringException if @a str contains an invalid
      *     escape sequence.
      */
    YSTRING_API std::u16string unescape(
            const std::u16string& str,
            EscapeType_t type = EscapeType::BACKSLASH);

    /** @brief Returns a upper case copy of @a str.
      */
    YSTRING_API std::u16string upper(const std::u16string& str);
}}
