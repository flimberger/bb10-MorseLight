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

#ifndef PK_MORSE_HPP
#define PK_MORSE_HPP

#include <QVector>

class QString;

namespace pk
{
namespace signal
{

class MorseSignal
{
public:
    enum Character {
        EOM, // End of message
        EOW, // End of word (long pause)
        EOS, // End of sign (short pause)
        Dot, // Short signal
        Dash // Long signal
    };

    static MorseSignal fromString(const QString &string);

    MorseSignal();
    MorseSignal(const MorseSignal &other);

    MorseSignal &operator=(const MorseSignal &other);

    QString toString();
    const QVector<Character> &data() const;

private:
    static const Character kA[];
    static const Character kB[];
    static const Character kC[];
    static const Character kD[];
    static const Character kE[];
    static const Character kF[];
    static const Character kG[];
    static const Character kH[];
    static const Character kI[];
    static const Character kJ[];
    static const Character kK[];
    static const Character kL[];
    static const Character kM[];
    static const Character kN[];
    static const Character kO[];
    static const Character kP[];
    static const Character kQ[];
    static const Character kR[];
    static const Character kS[];
    static const Character kT[];
    static const Character kU[];
    static const Character kV[];
    static const Character kW[];
    static const Character kX[];
    static const Character kY[];
    static const Character kZ[];
    static const Character kD0[];
    static const Character kD1[];
    static const Character kD2[];
    static const Character kD3[];
    static const Character kD4[];
    static const Character kD5[];
    static const Character kD6[];
    static const Character kD7[];
    static const Character kD8[];
    static const Character kD9[];

    static const Character *kLetterTable[];
    static const Character *kDigitTable[];

    MorseSignal(const QVector<MorseSignal::Character> &morseChars);

    QVector<Character> m_data;

public:
    // typedef decltype(m_data)::const_iterator const_iterator;
    typedef QVector<Character>::const_iterator const_iterator;

    const_iterator cbegin() const;
    const_iterator cend() const;
};

} // namespace signal
} // namespace pk

#endif // PK_MORSE_HPP
