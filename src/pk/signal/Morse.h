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

#ifndef PK_MORSE_H
#define PK_MORSE_H

#include <QVector>

class QString;

namespace pk
{
namespace signal
{
namespace morse
{

typedef enum {
    EOW, // End of word (long pause)
    EOS, // End of sign (short pause)
    DOT, // Short signal
    DASH // Long signal
} char_t;

QVector<char_t> FromString(const QString &string);
QString ToString(const char_t *signal);
QString ToString(const QVector<char_t> &signal);

extern const char_t LETTER_A[];
extern const char_t LETTER_B[];
extern const char_t LETTER_C[];
extern const char_t LETTER_D[];
extern const char_t LETTER_E[];
extern const char_t LETTER_F[];
extern const char_t LETTER_G[];
extern const char_t LETTER_H[];
extern const char_t LETTER_I[];
extern const char_t LETTER_J[];
extern const char_t LETTER_K[];
extern const char_t LETTER_L[];
extern const char_t LETTER_M[];
extern const char_t LETTER_N[];
extern const char_t LETTER_O[];
extern const char_t LETTER_P[];
extern const char_t LETTER_Q[];
extern const char_t LETTER_R[];
extern const char_t LETTER_S[];
extern const char_t LETTER_T[];
extern const char_t LETTER_U[];
extern const char_t LETTER_V[];
extern const char_t LETTER_W[];
extern const char_t LETTER_X[];
extern const char_t LETTER_Y[];
extern const char_t LETTER_Z[];
extern const char_t DIGIT_0[];
extern const char_t DIGIT_1[];
extern const char_t DIGIT_2[];
extern const char_t DIGIT_3[];
extern const char_t DIGIT_4[];
extern const char_t DIGIT_5[];
extern const char_t DIGIT_6[];
extern const char_t DIGIT_7[];
extern const char_t DIGIT_8[];
extern const char_t DIGIT_9[];
extern const char_t WORD_DELIMETER;

extern const char_t *const LETTER_TABLE[];
extern const char_t *const DIGIT_TABLE[];

} // namespace morse
} // namespace signal
} // namespace pk

#endif // PK_MORSE_H
