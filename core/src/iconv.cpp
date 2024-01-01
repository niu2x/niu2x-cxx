#include <niu2x/string_utils.h>
#include <niu2x/std_alias.h>
#include "iconv.h"

namespace niu2x::string_utils::iconv {

using UTF32 = uint32_t; /* at least 32 bits */
using UTF16 = uint16_t;
using UTF8 = uint8_t;

/* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
#define UNI_MAX_LEGAL_UTF32  (UTF32)0x0010FFFF

#define UNI_SUR_HIGH_START (UTF32)0xD800
#define UNI_SUR_LOW_END    (UTF32)0xDFFF

template <typename T>
struct ConvertTrait {
    using ArgType = T;
};

template <>
struct ConvertTrait<char> {
    using ArgType = UTF8;
};
template <>
struct ConvertTrait<char16_t> {
    using ArgType = UTF16;
};
template <>
struct ConvertTrait<char32_t> {
    using ArgType = UTF32;
};

enum ConversionResult {
    conversionOK, /* conversion successful */
    sourceExhausted, /* partial character in source, but hit end */
    targetExhausted, /* insuff. room in target for conversion */
    sourceIllegal /* source sequence is illegal/malformed */
};

enum ConversionFlags { strictConversion = 0, lenientConversion };

template <class FromTrait, class ToTrait>
using ConvertFunc = ConversionResult (*)(
    const typename FromTrait::ArgType**,
    const typename FromTrait::ArgType*,
    typename ToTrait::ArgType**,
    typename ToTrait::ArgType*,
    ConversionFlags);

template <
    typename From,
    typename To,
    typename FromTrait = ConvertTrait<From>,
    typename ToTrait = ConvertTrait<To>>

static Maybe<std::basic_string<To>> utf_convert(
    const std::basic_string<From>& from,
    ConvertFunc<FromTrait, ToTrait> cvtfunc)
{
    static_assert(
        sizeof(From) == sizeof(typename FromTrait::ArgType),
        "Error size mismatched");
    static_assert(
        sizeof(To) == sizeof(typename ToTrait::ArgType),
        "Error size mismatched");

    if (from.empty()) {
        char32_t empty[] = { 0 };
        return empty;
    }

    // See: http://unicode.org/faq/utf_bom.html#gen6
    static const int most_bytes_per_character = 4;

    const size_t max_chars = from.length();

    const size_t out_nr = max_chars * most_bytes_per_character / sizeof(To);

    std::basic_string<To> working(out_nr, 0);

    auto inbeg = reinterpret_cast<const typename FromTrait::ArgType*>(&from[0]);
    auto inend = inbeg + from.length();

    auto outbeg = reinterpret_cast<typename ToTrait::ArgType*>(&working[0]);
    auto outend = outbeg + working.length();
    auto r = cvtfunc(&inbeg, inend, &outbeg, outend, strictConversion);
    if (r != conversionOK)
        return null_maybe;

    working.resize(reinterpret_cast<To*>(outbeg) - &working[0]);
    return working;
};

static const char trailingBytesForUTF8[256]
    = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5 };

static const UTF32 offsetsFromUTF8[6]
    = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
        0x03C82080UL, 0xFA082080UL, 0x82082080UL };

/*
 * Once the bits are split out into bytes of UTF-8, this is a mask OR-ed
 * into the first byte, depending on how many bytes follow.  There are
 * as many entries in this table as there are UTF-8 sequence types.
 * (I.e., one byte sequence, two byte... etc.). Remember that sequencs
 * for *legal* UTF-8 will be 4 or fewer bytes total.
 */
static const UTF8 firstByteMark[7]
    = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

static bool isLegalUTF8(const UTF8* source, int length)
{
    UTF8 a;
    const UTF8* srcptr = source + length;
    switch (length) {
        default:
            return false;
            /* Everything else falls through when "true"... */
        case 4:
            if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
                return false;
            [[fallthrough]];
        case 3:
            if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
                return false;
            [[fallthrough]];
        case 2:
            if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
                return false;

            switch (*source) {
                /* no fall-through in this inner switch */
                case 0xE0:
                    if (a < 0xA0)
                        return false;
                    break;
                case 0xED:
                    if (a > 0x9F)
                        return false;
                    break;
                case 0xF0:
                    if (a < 0x90)
                        return false;
                    break;
                case 0xF4:
                    if (a > 0x8F)
                        return false;
                    break;
                default:
                    if (a < 0x80)
                        return false;
            }

            [[fallthrough]];

        case 1:
            if (*source >= 0x80 && *source < 0xC2)
                return false;
    }
    if (*source > 0xF4)
        return false;
    return true;
}

static ConversionResult convert_utf8_to_utf32(
    const UTF8** sourceStart,
    const UTF8* sourceEnd,
    UTF32** targetStart,
    UTF32* targetEnd,
    ConversionFlags flags)
{
    ConversionResult result = conversionOK;
    const UTF8* source = *sourceStart;
    UTF32* target = *targetStart;
    while (source < sourceEnd) {
        UTF32 ch = 0;
        unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
        if (extraBytesToRead >= sourceEnd - source) {
            result = sourceExhausted;
            break;
        }
        /* Do this check whether lenient or strict */
        if (!isLegalUTF8(source, extraBytesToRead + 1)) {
            result = sourceIllegal;
            break;
        }
        /*
         * The cases all fall through. See "Note A" below.
         */
        switch (extraBytesToRead) {
            case 5:
                ch += *source++;
                ch <<= 6;
                [[fallthrough]];
            case 4:
                ch += *source++;
                ch <<= 6;
                [[fallthrough]];
            case 3:
                ch += *source++;
                ch <<= 6;
                [[fallthrough]];
            case 2:
                ch += *source++;
                ch <<= 6;
                [[fallthrough]];
            case 1:
                ch += *source++;
                ch <<= 6;
                [[fallthrough]];
            case 0:
                ch += *source++;
        }
        ch -= offsetsFromUTF8[extraBytesToRead];

        if (target >= targetEnd) {
            source -= (extraBytesToRead + 1); /* Back up the source pointer! */
            result = targetExhausted;
            break;
        }
        if (ch <= UNI_MAX_LEGAL_UTF32) {
            /*
             * UTF-16 surrogate values are illegal in UTF-32, and anything
             * over Plane 17 (> 0x10FFFF) is illegal.
             */
            if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
                if (flags == strictConversion) {
                    source
                        -= (extraBytesToRead
                            + 1); /* return to the illegal value itself */
                    result = sourceIllegal;
                    break;
                } else {
                    *target++ = UNI_REPLACEMENT_CHAR;
                }
            } else {
                *target++ = ch;
            }
        } else { /* i.e., ch > UNI_MAX_LEGAL_UTF32 */
            result = sourceIllegal;
            *target++ = UNI_REPLACEMENT_CHAR;
        }
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}

Maybe<UnicodeString> utf8_to_utf32(const String& utf8)
{
    return utf_convert<char, char32_t>(utf8, &convert_utf8_to_utf32);
}

} // namespace niu2x::string_utils::iconv
