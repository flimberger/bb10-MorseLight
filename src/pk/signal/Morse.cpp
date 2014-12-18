// Copyright (c) 2014, Florian Limberger <flo@snakeoilproductions.net>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "Morse.h"

#include <QString>

namespace pk
{
namespace signal
{
namespace morse
{

QString ToString(const char_t *signal)
{
    QString str;

    while (*signal != EOS && *signal != EOW) {
        if (*signal++ == DOT) {
            str += ".";
        } else {
            str += "-";
        }
    }

    return str;
}

QString ToString(const QVector<char_t> &signal)
{
    auto string = QString {};
    auto end = signal.constEnd();

    for (auto i = signal.constBegin(); i != end; ++i) {
        switch (*i) {
        case DOT:
            string += ".";
            break;
        case DASH:
            string += "-";
            break;
        case EOS:
            string += " ";
            break;
        case EOW:
            string += "   ";
            break;
        }
    }

    return string;
}

const char_t LETTER_A[] = { DOT,  DASH, EOS };
const char_t LETTER_B[] = { DASH, DOT,  DOT,  DOT,  EOS };
const char_t LETTER_C[] = { DASH, DOT,  DASH, DOT,  EOS };
const char_t LETTER_D[] = { DASH, DOT,  DOT,  EOS };
const char_t LETTER_E[] = { DOT,  EOS };
const char_t LETTER_F[] = { DOT,  DOT,  DASH, DOT,  EOS };
const char_t LETTER_G[] = { DASH, DASH, DOT,  EOS };
const char_t LETTER_H[] = { DOT,  DOT,  DOT,  DOT,  EOS };
const char_t LETTER_I[] = { DOT,  DOT,  EOS };
const char_t LETTER_J[] = { DOT,  DASH, DASH, DASH, EOS };
const char_t LETTER_K[] = { DASH, DOT,  DASH, EOS };
const char_t LETTER_L[] = { DOT,  DASH, DOT,  DOT,  EOS };
const char_t LETTER_M[] = { DASH, DASH, EOS };
const char_t LETTER_N[] = { DASH, DOT,  EOS };
const char_t LETTER_O[] = { DASH, DASH, DASH, EOS };
const char_t LETTER_P[] = { DOT,  DASH, DASH, DOT,  EOS };
const char_t LETTER_Q[] = { DASH, DASH, DOT,  DASH, EOS };
const char_t LETTER_R[] = { DOT,  DASH, DOT,  EOS };
const char_t LETTER_S[] = { DOT,  DOT,  DOT,  EOS };
const char_t LETTER_T[] = { DASH, EOS };
const char_t LETTER_U[] = { DOT,  DOT,  DASH, EOS };
const char_t LETTER_V[] = { DOT,  DOT,  DOT,  DASH, EOS };
const char_t LETTER_W[] = { DOT,  DASH, DASH, EOS };
const char_t LETTER_X[] = { DASH, DOT,  DOT,  DASH, EOS };
const char_t LETTER_Y[] = { DASH, DOT,  DASH, DASH, EOS };
const char_t LETTER_Z[] = { DASH, DASH, DOT,  DOT,  EOS };
const char_t DIGIT_0[] = { DASH, DASH, DASH, DASH, DASH, EOS };
const char_t DIGIT_1[] = { DOT,  DASH, DASH, DASH, DASH, EOS };
const char_t DIGIT_2[] = { DOT,  DOT,  DASH, DASH, DASH, EOS };
const char_t DIGIT_3[] = { DOT,  DOT,  DOT,  DASH, DASH, EOS };
const char_t DIGIT_4[] = { DOT,  DOT,  DOT,  DOT,  DASH, EOS };
const char_t DIGIT_5[] = { DOT,  DOT,  DOT,  DOT,  DOT,  EOS };
const char_t DIGIT_6[] = { DASH, DOT,  DOT,  DOT,  DOT,  EOS };
const char_t DIGIT_7[] = { DASH, DASH, DOT,  DOT,  DOT,  EOS };
const char_t DIGIT_8[] = { DASH, DASH, DASH, DOT,  DOT,  EOS };
const char_t DIGIT_9[] = { DASH, DASH, DASH, DASH, DOT,  EOS };
const char_t WORD_DELIMETER = EOW;

const char_t *const LETTER_TABLE[] = {
    LETTER_A,
    LETTER_B,
    LETTER_C,
    LETTER_D,
    LETTER_E,
    LETTER_F,
    LETTER_G,
    LETTER_H,
    LETTER_I,
    LETTER_J,
    LETTER_K,
    LETTER_L,
    LETTER_M,
    LETTER_N,
    LETTER_O,
    LETTER_P,
    LETTER_Q,
    LETTER_R,
    LETTER_S,
    LETTER_T,
    LETTER_U,
    LETTER_V,
    LETTER_W,
    LETTER_X,
    LETTER_Y,
    LETTER_Z
};

const char_t *const DIGIT_TABLE[] = {
    DIGIT_0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9
};

} // namespace morse
} // namespace signal
} // namespace pk
